FROM ros:indigo-ros-core

RUN apt update \
        && apt install -y --no-install-recommends ros-indigo-hrpsys ros-indigo-openrtm-aist-python \
        && apt install -y --no-install-recommends libgl1-mesa-glx libgl1-mesa-dri libglew-dev \
        && apt install -y --no-install-recommends byobu screen \
        && apt install -y --no-install-recommends python-catkin-tools g++ \
        && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/fkanehiro/hrpsys-base.git --depth=1 /root/catkin_ws/src/hrpsys-base \
        && cd /root/catkin_ws \
        && . /opt/ros/indigo/setup.sh \
        && catkin build --cmake-args -DENABLE_DOXYGEN=OFF

WORKDIR /root/catkin_ws
