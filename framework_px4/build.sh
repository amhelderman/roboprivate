# This isn't as organized as my usual scripts. This leaves it in your home folder.

pushd ~ 
git clone git@github.com:PX4/PX4-Autopilot.git 
cd PX4-Autopilot
git submodule update --init --recursive

# Run a sitl with Gazebo
make px4_sitl gazebo

cd ..

