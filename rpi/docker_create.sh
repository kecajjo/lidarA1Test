#!/bin/bash
scriptDir=$(dirname $0 | xargs -i readlink -f {})
container_name="lidar/rpi"
version="0.3"
does_exist=$(docker image ls $container_name:$version | grep -ci1 $container_name)
if [ $does_exist == "0" ] ; then
	docker build -t $container_name:$version $scriptDir/
fi
docker run --rm \
    --privileged \
    --name "lidar_rpi" \
    --env DISPLAY \
    -v $HOME/.Xauthority:/root/.Xauthority \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v "$scriptDir/src:/home/developer/src" \
    -v "$scriptDir/../protobuf:/home/developer/protobuf" \
    -it $container_name:$version /bin/bash
