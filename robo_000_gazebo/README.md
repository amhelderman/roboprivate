
# Run gazebo simulation, teleop, and rviz.
# Accomplishes part of https://docs.ros.org/en/humble/Tutorials/Advanced/Simulators/Gazebo/Gazebo.html
```
docker compose build
docker compose up  -d  --remove-orphans
sleep 30 

NEXTCOMMAND='ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r /cmd_vel:=/model/vehicle_blue/cmd_vel'

docker exec -it robo_sim_rviz-teleop-1 /bin/bash -c "source /opt/ros/humble/setup.bash && $NEXTCOMMAND"
```

Close the windows and run `docker compose down` should turn it off.


ros2 run ros_gz_bridge parameter_bridge /lidar2@sensor_msgs/msg/LaserScan[ignition.msgs.LaserScan --ros-args -r /lidar2:=/laser_scan