FROM ubuntu:20.04 as docker-private-repos

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update

RUN  apt-get install -y locales && \
    localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG=en_US.utf8

RUN apt-get -y install \
    build-essential \
    git \
    gosu \
    perl \
    python3 \
    sudo

RUN echo "builder ALL=NOPASSWD: ALL" > /etc/sudoers.d/builder-nopasswd && \
    chmod 660 /etc/sudoers.d/builder-nopasswd

RUN echo "Defaults env_keep += \"ftp_proxy http_proxy https_proxy no_proxy\"" \
    > /etc/sudoers.d/env_keep && chmod 660 /etc/sudoers.d/env_keep

WORKDIR /home/builder

COPY container-entrypoint /home/builder

ENTRYPOINT ["/home/builder/container-entrypoint"]

