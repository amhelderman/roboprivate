Let's:
* use a dockerfile built to run ros2, 
* Install turtlesim in there
* Run it with display passthrough options from docker --> WSL2 --> WIndows 

The result is turtlesim appearing to run in windows without needing to fuss with docker desktop passing X11 through.
I wasn't able to do that, so this is a better option.

# Build

```
docker compose build
```

# Run
In your first terminal:
```
docker compose up 
```

Then note the directions for what keys work. However, the docker compose isn't able to accept your tty.

So, in a second terminal:
```
docker attach robo_turtlesim_docker-teleop-1
```


# Notes
* Let's confirm this works: `docker run -it --rm  --net=host osrf/ros:humble-desktop-full /bin/bash `
* It's downloading...
* The docker compose options dont work:
    *    stdin_open: true # docker run -i
    *    tty: true        # docker run -t