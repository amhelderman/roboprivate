FROM osrf/ros:humble-desktop-full 

# Debian is noninteractive 
ENV DEBIAN_FRONTEND noninteractive

RUN sudo apt update && sudo apt install -y ros-humble-turtlesim \
    ~nros-humble-rqt* \
    ros-humble-ros-gz \
    wget

RUN wget https://raw.githubusercontent.com/gazebosim/gz-sim/main/examples/worlds/visualize_lidar.sdf 
RUN sudo chmod +x visualize_lidar.sdf

# Run ros2 run turtlesim turtlesim_node 
# CMD ["ros2", "run", "turtlesim", "turtlesim_node"]
# Run ign gazebo -v 4 -r visualize_lidar.sdf 
CMD ["ign", "gazebo", "-v", "4", "-r", "visualize_lidar.sdf"]