FROM python:3.10.5-slim-bullseye@sha256:b208c71e1d72864460394cc648c6b5c1ddac6f8587af4a3a54b7be575353f5d0

ADD requirements.txt /tmp/flask-requirements.txt
RUN pip3 install -qr /tmp/flask-requirements.txt
RUN mkdir /code

ENTRYPOINT ["python3", "/code/service.py"]
