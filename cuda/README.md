
# Before starting, check that you have an nvidia GPU.

# For ubuntu 22 x86_64

1. Install CUDA toolkit from https://developer.nvidia.com/cuda-toolkit - this should cover the base installer:
```
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-keyring_1.1-1_all.deb
sudo dpkg -i cuda-keyring_1.1-1_all.deb
sudo apt-get update
sudo apt-get -y install cuda-toolkit-12-3
```

Note - I felt i needed to double check this toolkit version for my ubuntu 23.10.
https://docs.nvidia.com/cuda/cuda-installation-guide-linux/#meta-packages
I think to be sure, I'm just going to use `cuda`.

```
sudo apt-get -y install cuda
```
Note - I got the error from apt.
```
 nsight-systems-2023.3.3 : Depends: libtinfo5 but it is not installable
```
Of course Ubuntu 23.10 just doesn't have this library binary yet, but this answer explains how to fix:
```
https://askubuntu.com/questions/1491254/installing-cuda-on-ubuntu-23-10-libt5info-not-installable
```

2. And the driver install:
```
sudo apt-get install -y cuda-drivers
```
3. Open kernel module flavor:
```
sudo apt-get install -y nvidia-kernel-open-545sudo apt-get install -y cuda-drivers-545
```

```
sudo apt install gcc-9 g++-9

# Replace `HOST_COMPILER ?= g++-9` with `HOST_COMPILER ?= g++-9` in the lower-level makefiles

```

# Alternative install 
https://docs.nvidia.com/cuda/cuda-quick-start-guide/index.html#ubuntu
