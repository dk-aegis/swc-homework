FROM ubuntu AS app

RUN apt-get update && rm -rf /var/lib/apt/lists/*
FROM pwn.red/jail

ENV JAIL_TIME=1000

COPY --from=app / /srv
COPY flag /srv/app/
COPY chall /srv/app/run