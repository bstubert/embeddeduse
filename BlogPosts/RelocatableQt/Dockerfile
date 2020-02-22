# Copyright 2020, Burkhard Stubert (DBA Embedded Use)

FROM ubuntu:18.04

RUN apt-get -y update

RUN apt-get -y install build-essential perl python git \
    '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev '^libxkbcommon.*' \    
    libssl-dev libxcursor-dev libxcomposite-dev libxdamage-dev libxrandr-dev libdbus-1-dev \
    libfontconfig1-dev libcap-dev libxtst-dev libpulse-dev libudev-dev libpci-dev libnss3-dev \
    libasound2-dev libxss-dev libegl1-mesa-dev gperf bison \
    libasound2-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev \
    flex libicu-dev dpkg cmake zip unzip

RUN apt-get -y purge libxcb-xinerama0-dev libxcb-xinerama0

# Don't use dash on Ubuntu
RUN which dash &> /dev/null && (\
    echo "dash dash/sh boolean false" | debconf-set-selections && \
    DEBIAN_FRONTEND=noninteractive dpkg-reconfigure dash) || \
    echo "Skipping dash reconfigure (not applicable)"

RUN apt-get -y install locales
RUN locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8

ENV USER_NAME benutzer

ARG host_uid=1001
ARG host_gid=1001
RUN groupadd -g $host_gid $USER_NAME && useradd -g $host_gid -m -s /bin/bash -u $host_uid $USER_NAME

USER $USER_NAME
WORKDIR /RelocatableQt


