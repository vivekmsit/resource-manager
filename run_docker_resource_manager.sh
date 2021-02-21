docker run --rm -it  \
    --device /dev/net/tun:/dev/net/tun \
    --network host \
    -v `pwd`:`pwd` \
    --workdir=`pwd` \
    resource-manager:v0 bash
