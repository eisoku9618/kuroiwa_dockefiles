ARG DISTRO=kinetic
FROM ros:${DISTRO}-ros-core
ARG DISTRO=kinetic

RUN apt update \
        && apt install -y --no-install-recommends python-catkin-tools python-wstools \
        && mkdir -p /root/catkin_ws/src \
        && wstool init /root/catkin_ws/src \
        && wstool set -y -t /root/catkin_ws/src --git https://github.com/PR2/pr2_common.git PR2/pr2_common \
        && wstool update -t /root/catkin_ws/src \
        && rosdep install --from-paths /root/catkin_ws/src --ignore-src -y \
        && . /opt/ros/${DISTRO}/setup.sh \
        && catkin build -w /root/catkin_ws/ \
        && rm -rf /root/catkin_ws/build /root/catkin_ws/logs \
        && apt install -y --no-install-recommends ros-${DISTRO}-rviz ros-${DISTRO}-joint-state-publisher ros-${DISTRO}-robot-state-publisher \
        && apt install -y --no-install-recommends ros-${DISTRO}-urdf-tutorial ros-${DISTRO}-collada-urdf ros-${DISTRO}-roseus ros-${DISTRO}-euscollada ros-${DISTRO}-eus-assimp \
        && rm -rf /var/lib/apt/lists/*

WORKDIR /root/catkin_ws/

# RUN apt update \
#         && apt install -y --no-install-recommends pkg-config libxau-dev libxdmcp-dev libxcb1-dev libxext-dev libx11-dev \
#         && rm -rf /var/lib/apt/lists/*

# replace with other Ubuntu version if desired
# see: https://hub.docker.com/r/nvidia/opengl/
COPY --from=nvidia/opengl:1.0-glvnd-runtime-ubuntu16.04 /usr/local/lib/x86_64-linux-gnu /usr/local/lib/x86_64-linux-gnu

# replace with other Ubuntu version if desired
# see: https://hub.docker.com/r/nvidia/opengl/
COPY --from=nvidia/opengl:1.0-glvnd-runtime-ubuntu16.04 /usr/local/share/glvnd/egl_vendor.d/10_nvidia.json /usr/local/share/glvnd/egl_vendor.d/10_nvidia.json

RUN echo '/usr/local/lib/x86_64-linux-gnu' >> /etc/ld.so.conf.d/glvnd.conf \
        && ldconfig \
        && echo '/usr/local/$LIB/libGL.so.1' >> /etc/ld.so.preload \
        && echo '/usr/local/$LIB/libEGL.so.1' >> /etc/ld.so.preload

# nvidia-container-runtime
ENV NVIDIA_VISIBLE_DEVICES ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics
