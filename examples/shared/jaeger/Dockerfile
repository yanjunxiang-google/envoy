FROM jaegertracing/all-in-one@sha256:11bd06fc2b5c3b2b2e575bb8993b3bca9deb41e5b4318339d6ce44a2d08be370
HEALTHCHECK \
    --interval=1s \
    --timeout=1s \
    --start-period=1s \
    --retries=60 \
    CMD wget -q --header='Content-Type:application/json' -O - http://localhost:14269/health | grep "Server available"
