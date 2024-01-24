# Robo 001 - runs a turtlesim 

```
docker compose up
```

Then in another window:
```
docker attach robo_001_turtlesim_teleop-teleop-1 

# Now you can use the usual ROS2 teleop commands to drive the turtle:
#   Use arrow keys to move the turtle.
#   Use G|B|V|C|D|E|R|T keys to rotate to absolute orientations. 'F' to cancel a rotation.
#   'Q' to quit.
```