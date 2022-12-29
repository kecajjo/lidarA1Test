FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN ln -snf /usr/share/zoneinfo/Europe/Warsaw /etc/localtime && echo Europe/Warsaw > /etc/timezone
USER root
    RUN useradd -m developer && \
        echo "developer:123" | chpasswd && \
        adduser developer sudo
    RUN apt-get update && apt-get install -y \
        tzdata \
        cmake \
        git \
        libtool \
        pkg-config \
        build-essential \
        autoconf \
        automake && \
        rm -rf /var/lib/apt/lists/*
    RUN apt-get update && apt-get install -y \
        libzmq3-dev \
        sudo && \
        rm -rf /var/lib/apt/lists/*
    RUN git clone -b v3.21.8 --single-branch https://github.com/protocolbuffers/protobuf.git&& \
        cd protobuf && \
        git submodule update --init --recursive && \ 
        ./autogen.sh && \
        ./configure && \
        make -j15 && \
        make install && \
        ldconfig
    RUN git clone https://github.com/Slamtec/rplidar_sdk.git && \
    cd rplidar_sdk && \
    git checkout babe753f39f16f4c6a6dec2c33b4ed541ca0e502 && \
	cd sdk && \
	make -j15 && \
    ln -s /rplidar_sdk/sdk/include/ /usr/include/rplidar_sdk && \
    ln -s /rplidar_sdk/sdk/src/hal/ /usr/include/rplidar_sdk/hal && \
    ln -s /rplidar_sdk/output/Linux/Release/ /usr/lib/rplidar_sdk
    
USER developer
    RUN mkdir -p /home/developer/src
    WORKDIR /home/developer/src

ENTRYPOINT ["/bin/bash", "-c"]
