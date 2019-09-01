FROM ros:indigo-ros-core

RUN apt update \
        && apt install -y --no-install-recommends ros-indigo-hrpsys ros-indigo-openrtm-aist-python \
        && apt install -y --no-install-recommends libgl1-mesa-glx libgl1-mesa-dri \
        && apt install -y --no-install-recommends byobu screen \
        && rm -rf /var/lib/apt/lists/*
