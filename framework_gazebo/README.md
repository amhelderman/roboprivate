https://gazebosim.org/docs/fortress/tutorials


```




```





# OLD INSTRUCTIONS

My ros2 preference is to use ros2 humble since we have a docker image for that.
According to https://staging.gazebosim.org/docs/latest/ros_installation we should 
use gazebo fortress (LTS). (GZ is gazebo).


# First set up vnc using vnc_setup2

sudo apt-get update
sudo apt-get install lsb-release wget gnupg

# WAS GOING TO RUN THIS BUT hold on the versions are probably off.
sudo wget https://packages.osrfoundation.org/gazebo.gpg -O /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] http://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/gazebo-stable.list > /dev/null
sudo apt-get update
sudo apt-get install gz-harmonic