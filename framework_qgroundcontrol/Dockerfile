FROM ubuntu:latest 


ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt install -y wget \
        net-tools \
        curl 
RUN wget https://github.com/mavlink/qgroundcontrol/releases/download/v4.2.0/QGroundControl.AppImage
RUN chmod +x QGroundControl.AppImage

# # RUN usermod -a -G dialout $USER
RUN  apt-get remove modemmanager -y
RUN  apt install gstreamer1.0-plugins-bad gstreamer1.0-libav gstreamer1.0-gl -y
RUN  apt install libqt5gui5 -y
RUN  apt install libfuse2 -y
RUN  apt install libnss3 -y
# RUN  apt install libx11-xcb1 -y
# RUN  apt install libxcb-dri3-0 -y
# RUN  apt install libxcomposite1 -y
# RUN  apt install libxcursor1 -y
# RUN  apt install libxi6 -y
# RUN  apt install libxtst6 -y
# RUN  apt install libxss1 -y
# RUN  apt install libxrandr2 -y
# RUN  apt install libasound2 -y


# RUN  usermod -a -G dialout $USER
RUN  apt-get remove modemmanager -y
RUN apt install gstreamer1.0-plugins-bad gstreamer1.0-libav gstreamer1.0-gl -y
RUN  apt install libqt5gui5 -y
RUN apt install libfuse2 -y


# myqgroundcontrol-1  | /tmp/.mount_qgcKxPw7x/QGroundControl: error while loading shared libraries: libpulse-mainloop-glib.so.0: cannot open shared object file: No such file or directory
RUN apt install libpulse-mainloop-glib0 -y
RUN apt install -y fuse
RUN apt install -y fuse3 libfuse2

# Cant run it as root so make a user
RUN useradd -ms /bin/bash qgroundcontroluser
RUN  usermod -a -G dialout qgroundcontroluser

RUN apt install -y xauth

# CMD ./QGroundControl.AppImage --appimage-extract-and-run
RUN mv QGroundControl.AppImage /home/qgroundcontroluser/qgc
RUN chown qgroundcontroluser:qgroundcontroluser /home/qgroundcontroluser/qgc

USER qgroundcontroluser
WORKDIR /home/qgroundcontroluser

# CMD newgrp dialout && ./qgc 
# CMD ./qgc --appimage-extract-and-run
CMD /bin/bash -c "whoami && pwd && ls -la && echo $DISPLAY && xauth list && ./qgc --appimage-extract-and-run"