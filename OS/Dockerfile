FROM osrf/ros:melodic-desktop-full

ARG USERNAME=kweontakju

RUN apt-get update \
 && apt-get install -y sudo \
 && useradd -m -s /bin/bash ${USERNAME} \
 && echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER ${USERNAME}
WORKDIR /home/${USERNAME}

ENTRYPOINT ["/bin/bash"]
