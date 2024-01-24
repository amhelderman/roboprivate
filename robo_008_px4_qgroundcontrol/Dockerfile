FROM osrf/ros:humble-desktop-full 

# Debian is noninteractive 
ENV DEBIAN_FRONTEND noninteractive

RUN sudo apt update && sudo apt install -y ros-humble-turtlesim \
    ~nros-humble-rqt* \
    ros-humble-ros-gz \
    ros-humble-ros-ign-bridge \
    ros-humble-rviz2 \
    ros-humble-navigation2 \
    ros-humble-nav2-bringup \
    ros-humble-nav2-bringup \
    ros-humble-turtlebot3-gazebo \
    wget

COPY ./PX4-Autopilot /PX4-Autopilot
RUN ./PX4-Autopilot/Tools/setup/ubuntu.sh --no-nuttx --no-sim-tools
# Lets install all gstreamer stuff 
RUN sudo apt install -y gstreamer1.0-plugins-bad gstreamer1.0-libav gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
RUN sudo apt install  -y libgstreamer*

RUN cd /PX4-Autopilot && DONT_RUN=1 make px4_sitl gazebo

# Run ros2 run turtlesim turtlesim_node 
# CMD ["ros2", "run", "turtlesim", "turtlesim_node"]
# Run ign gazebo -v 4 -r visualize_lidar.sdf 
CMD ["ign", "gazebo", "-v", "4", "-r", "visualize_lidar.sdf"]
