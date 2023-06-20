FROM jaegertracing/all-in-one@sha256:7a53d97437a9e234e2c39165a8bd6551d057b8635f44cd7c914cc5d158da066d
HEALTHCHECK \
    --interval=1s \
    --timeout=1s \
    --start-period=1s \
    --retries=60 \
    CMD wget -q --header='Content-Type:application/json' -O - http://localhost:14269/health | grep "Server available"
