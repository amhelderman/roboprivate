FROM ubuntu:22.04 


# Install dependencies
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    "linux-headers-$(uname -r)" \
    "linux-modules-extra-$(uname -r)"

RUN apt install -y wget 

RUN wget https://repo.radeon.com/amdgpu-install/6.0.2/ubuntu/jammy/amdgpu-install_6.0.60002-1_all.deb
RUN apt install  -y  ./amdgpu-install_6.0.60002-1_all.deb
RUN apt update
RUN apt install -y amdgpu-dkms rocm


# Install opencl, mesa and clinfo
RUN apt-get install -y ocl-icd-opencl-dev clinfo mesa-opencl-icd

# Make a user 1000 to match the host user 
RUN useradd -m -u 1000 -s /bin/bash exampleuser
RUN /bin/bash -c 'usermod -a -G render,video exampleuser'
USER exampleuser