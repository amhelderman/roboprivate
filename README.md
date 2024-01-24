# Robo - A collection of robotics demos set up to run automatically using docker compose.

This is all experimental - no warranty.

# Prerequisites:
* A modern ubuntu system
* Docker
* Docker Compose v2

# How to Install Docker and Docker Compose:
```
sudo apt install -y docker.io 
sudo usermod -aG docker $USER 
```

Then log out and back into your computer before we install docker compose:
```
docker run hello-world # Verify docker installation and permissions.

DOCKER_CONFIG=${DOCKER_CONFIG:-$HOME/.docker}
mkdir -p $DOCKER_CONFIG/cli-plugins
curl -SL https://github.com/docker/compose/releases/download/v2.23.3/docker-compose-linux-x86_64 -o $DOCKER_CONFIG/cli-plugins/docker-compose
sudo chmod +x $DOCKER_CONFIG/cli-plugins/docker-compose
docker compose version
```

# How to Run:
Go into a subdirectory and follow the README.md instructions.

***I recommend you try robo_003_turtlesim_spiral first.***
