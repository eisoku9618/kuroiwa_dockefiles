FROM ros:indigo-robot

ARG ROS_INSTALLDIR=~/catkin_ws/indigo
ARG ROS_INSTALLDIR_SRC=${ROS_INSTALLDIR}/src/
ARG ROS_INSTALLDIR_PARENT_SRC=${ROS_INSTALLDIR}_parent/src/

# install necessary packages
RUN apt update \
&& apt install --no-install-recommends -y python-pip wget \
&& rm -rf /var/lib/apt/lists/*

# packages in /tmp/jsk.rosinstall will be downloaded and compiled
COPY jsk.rosinstall /tmp/jsk.rosinstall
RUN mkdir -p ${ROS_INSTALLDIR_SRC} \
&& wstool init ${ROS_INSTALLDIR_SRC} /tmp/jsk.rosinstall -j4

# download non-ros packages
RUN mkdir -p ${ROS_INSTALLDIR_PARENT_SRC} \
&& wstool init ${ROS_INSTALLDIR_PARENT_SRC} \
&& apt update \
&& ${ROS_INSTALLDIR_SRC}/jsk-ros-pkg/jsk_roseus/setup_upstream.sh -w ${ROS_INSTALLDIR_PARENT_SRC}/../ \
&& ${ROS_INSTALLDIR_SRC}/rtm-ros-robotics/rtmros_common/setup_upstream.sh -w ${ROS_INSTALLDIR_PARENT_SRC}/../ \
&& rm -rf /var/lib/apt/lists/*

# install dependent packages by apt, pip, etc.
RUN apt update \
&& rosdep install -y -n -r --ignore-src --from-paths ${ROS_INSTALLDIR_SRC} ${ROS_INSTALLDIR_PARENT_SRC} \
&& apt install --no-install-recommends -y python-catkin-tools \
&& rm -rf /var/lib/apt/lists/*

# build non-ros packages and then build ros packages (chain)
RUN . /opt/ros/indigo/setup.sh \
&& cd {ROS_INSTALLDIR_PARENT_SRC}/../ \
&& catkin build \
&& . {ROS_INSTALLDIR_PARENT_SRC}/../devel/setup.sh \
&& cd {ROS_INSTALLDIR_SRC}/../ \
&& catkin build

# setup entrypoint
COPY ./ros_entrypoint.sh /
ENTRYPOINT ["/ros_entrypoint.sh"]
CMD ["/bin/bash"]
