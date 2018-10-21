FROM eisoku9618/kuroiwa_dockefiles_for_jsk_ros_pkg:parent

ARG ROS_INSTALLDIR=/root/catkin_ws/indigo
ARG ROS_INSTALLDIR_SRC=${ROS_INSTALLDIR}/src/
ARG ROS_INSTALLDIR_PARENT_SRC=${ROS_INSTALLDIR}_parent/src/

# build non-ros packages and then build ros packages (chain)
SHELL ["/bin/bash", "-c"]
RUN source ${ROS_INSTALLDIR_PARENT_SRC}/../devel/setup.bash \
&& cd ${ROS_INSTALLDIR_SRC}/../ \
&& catkin build \
&& echo "source '/root/catkin_ws/indigo/devel/setup.bash'" >> /root/.bashrc

CMD ["bash"]
