# Note: comments in Dockerfiles (comment character is #) must be on their own line

# Add base image using FROM command
# This base image from DockerHub is an image to base ours off of.
# We'll build off a gcc:10.1 image
FROM gcc:10.1

# Set up a tools dev directory
WORKDIR /home/dev

# The COPY command allows us to copy files from our host OS into our container.
COPY gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2 .

# Next, we’ll use the RUN command to install other packages we need for our image.
# The “\” allows us to extend our command across multiple lines

RUN apt-get update \
    && apt-get -y install git scons lib32z1 libncurses5 \
    && tar xf gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2 \
    && rm gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2 \
    && rm -rf /home/dev/gcc-arm-none-eabi-9-2020-q2-update/share/doc

# Set up compiler path
ENV PATH="/home/dev/gcc-arm-none-eabi-9-2020-q2-update/bin:${PATH}"

# Set up project directory
WORKDIR /usr/project