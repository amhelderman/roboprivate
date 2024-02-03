FROM ubuntu:24.04

# sudo apt install libopencv-dev python3-opencv 
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    python3-opencv \
    libopencv-dev \
    && rm -rf /var/lib/apt/lists/*



CMD /bin/bash -c 'python3 -c "import cv2; print(cv2.__version__)"'