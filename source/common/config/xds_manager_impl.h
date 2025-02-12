#pragma once

#include "envoy/config/xds_manager.h"

#include "source/common/common/thread.h"

namespace Envoy {
namespace Config {

class XdsManagerImpl : public XdsManager {
public:
  XdsManagerImpl(ProtobufMessage::ValidationContext& validation_context)
      : validation_context_(validation_context) {}

  // Config::ConfigSourceProvider
  absl::Status initialize(Upstream::ClusterManager* cm) override;
  void shutdown() override {}
  absl::Status
  setAdsConfigSource(const envoy::config::core::v3::ApiConfigSource& config_source) override;

private:
  // Validates (syntactically) the config_source by doing the PGV validation.
  absl::Status validateAdsConfig(const envoy::config::core::v3::ApiConfigSource& config_source);

  ProtobufMessage::ValidationContext& validation_context_;
  // The cm_ will only be valid after the cluster-manager is initialized.
  // Note that this implies that the xDS-manager must be shut down properly
  // prior to the cluster-manager deletion.
  Upstream::ClusterManager* cm_;
};

} // namespace Config
} // namespace Envoy
