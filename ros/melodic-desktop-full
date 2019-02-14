FROM osrf/ros:melodic-desktop-full

RUN apt update \
    && apt install -y python-catkin-tools clang clang-tidy-6.0 \
    && rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash"]
