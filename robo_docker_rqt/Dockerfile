FROM osrf/ros:humble-desktop-full 

# Debian is noninteractive 
ENV DEBIAN_FRONTEND noninteractive

RUN sudo apt install -y ros-humble-turtlesim ~nros-humble-rqt*

# Run ros2 run turtlesim turtlesim_node 
CMD ["ros2", "run", "turtlesim", "turtlesim_node"]