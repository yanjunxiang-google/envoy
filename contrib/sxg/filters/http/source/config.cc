#include "contrib/sxg/filters/http/source/config.h"

#include <memory>
#include <string>

#include "envoy/registry/registry.h"
#include "envoy/secret/secret_manager.h"
#include "envoy/secret/secret_provider.h"

#include "source/common/protobuf/utility.h"

#include "contrib/envoy/extensions/filters/http/sxg/v3alpha/sxg.pb.h"
#include "contrib/envoy/extensions/filters/http/sxg/v3alpha/sxg.pb.validate.h"
#include "contrib/sxg/filters/http/source/encoder.h"
#include "contrib/sxg/filters/http/source/filter.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace SXG {

namespace {
Secret::GenericSecretConfigProviderSharedPtr
secretsProvider(const envoy::extensions::transport_sockets::tls::v3::SdsSecretConfig& config,
                Server::Configuration::ServerFactoryContext& server_context,
                Init::Manager& init_manager) {
  if (config.has_sds_config()) {
    return server_context.secretManager().findOrCreateGenericSecretProvider(
        config.sds_config(), config.name(), server_context, init_manager);
  } else {
    return server_context.secretManager().findStaticGenericSecretProvider(config.name());
  }
}
} // namespace

Http::FilterFactoryCb FilterFactory::createFilterFactoryFromProtoTyped(
    const envoy::extensions::filters::http::sxg::v3alpha::SXG& proto_config,
    const std::string& stat_prefix, Server::Configuration::FactoryContext& context) {
  const auto& certificate = proto_config.certificate();
  const auto& private_key = proto_config.private_key();

  auto& server_context = context.serverFactoryContext();

  auto secret_provider_certificate =
      secretsProvider(certificate, server_context, context.initManager());
  if (secret_provider_certificate == nullptr) {
    throw EnvoyException("invalid certificate secret configuration");
  }
  auto secret_provider_private_key =
      secretsProvider(private_key, server_context, context.initManager());
  if (secret_provider_private_key == nullptr) {
    throw EnvoyException("invalid private_key secret configuration");
  }

  auto secret_reader = std::make_shared<SDSSecretReader>(
      std::move(secret_provider_certificate), std::move(secret_provider_private_key),
      server_context.threadLocal(), server_context.api());
  auto config = std::make_shared<FilterConfig>(proto_config, server_context.timeSource(),
                                               secret_reader, stat_prefix, context.scope());
  return [config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    const EncoderPtr encoder = std::make_unique<EncoderImpl>(config);
    callbacks.addStreamFilter(std::make_shared<Filter>(config, encoder));
  };
}

REGISTER_FACTORY(FilterFactory, Server::Configuration::NamedHttpFilterConfigFactory);

} // namespace SXG
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
