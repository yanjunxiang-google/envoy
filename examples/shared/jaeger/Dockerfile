FROM jaegertracing/all-in-one@sha256:183f13304325552336a582e3b1082a2d0d9477c7249e3606a711e62fcb1bd6aa
HEALTHCHECK \
    --interval=1s \
    --timeout=1s \
    --start-period=1s \
    --retries=60 \
    CMD wget -q --header='Content-Type:application/json' -O - http://localhost:14269/health | grep "Server available"
