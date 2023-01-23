FROM ros:noetic-ros-base

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
        automake \
        gcc-10 \
        g++-10 \
        cpp-10 && \
        rm -rf /var/lib/apt/lists/* && \
        update-alternatives --install \
        /usr/bin/gcc gcc /usr/bin/gcc-10 100 \
        --slave /usr/bin/g++ g++ /usr/bin/g++-10 \
        --slave /usr/bin/gcov gcov /usr/bin/gcov-10
    RUN apt-get update && apt-get install -y \
        clang-format \
        flake8 \
        vim \
        python3-catkin-tools \
        python3-osrf-pycommon && \
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
        make -j4 && \
        make install && \
        ldconfig
    RUN apt-get update && apt-get install -y \
        rviz \
        ros-noetic-rviz && \
        rm -rf /var/lib/apt/lists/*

USER developer
    RUN mkdir -p /home/developer/src
    RUN echo "source /opt/ros/noetic/setup.bash" >> /home/developer/.bashrc
    WORKDIR /home/developer

ENTRYPOINT ["/bin/bash", "-c"]