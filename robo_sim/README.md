# Run gazebo and confirm ROS
# Accomplishes part of https://docs.ros.org/en/humble/Tutorials/Advanced/Simulators/Gazebo/Gazebo.html

# Build and Run Option 1 - Confirm that nodes are there

```
docker compose build
docker compose up  -d 
sleep 30 
NEXTCOMMAND='ros2 node list'
docker exec -it robo_sim-gazebo-ros-bridge-1 /bin/bash -c "source /opt/ros/humble/setup.bash  && $NEXTCOMMAND"

```


It should say "/ros_gz_bridge", indicating that the node is up. 

Close the windows and run `docker compose down` should turn it off.

# Build and Run Option 2 - command a velocity.
IF starting from new:
```
docker compose build
docker compose up  -d 
sleep 30 
NEXTCOMMAND='ros2 topic pub /model/vehicle_blue/cmd_vel geometry_msgs/Twist "linear: { x: 0.1 }"'
docker exec -it robo_sim-gazebo-ros-bridge-1 /bin/bash -c "source /opt/ros/humble/setup.bash  && $NEXTCOMMAND"

```
Close the windows and run `docker compose down` should turn it off.