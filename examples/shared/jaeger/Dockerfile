FROM jaegertracing/all-in-one@sha256:9ebb7a2608dbd65ee18e11987e87f74c88aca93345f458f3b546095bdbf240de
HEALTHCHECK \
    --interval=1s \
    --timeout=1s \
    --start-period=1s \
    --retries=60 \
    CMD wget -q --header='Content-Type:application/json' -O - http://localhost:14269/health | grep "Server available"
