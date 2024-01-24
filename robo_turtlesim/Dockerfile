FROM osrf/ros:humble-desktop-full 

# Debian is noninteractive 
ENV DEBIAN_FRONTEND noninteractive

RUN sudo apt install -y ros-humble-turtlesim

# Run ros2 run turtlesim turtlesim_node 
CMD ["ros2", "run", "turtlesim", "turtlesim_node"]