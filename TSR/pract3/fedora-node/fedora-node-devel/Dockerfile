# Take the latest Fedora distribution as a base.
# Currently (November 22, 2016), it is Fedora 24.
FROM fedora:24
# Install the latest Node.js on that distribution.
# It is Node.js v4.6.1.
# We may use the dnf Fedora command to this end.
RUN dnf install -y nodejs
# Next step: Install the zeromq library.
# Its package is called "zeromq-devel" in the Fedora
# distribution.
RUN dnf install -y zeromq-devel
# We still need the standard "make" command in order
# to run "npm".
RUN dnf install -y make
# There are other "tools" needed for compiling the
# "zmq" module. They are: python and gcc-c++
RUN dnf install -y python gcc-c++
# Install the ImageMagick library. It is needed for
# developing the server described in Section 3.
RUN dnf install -y ImageMagick ImageMagick-devel
# Finally, let us run the npm command for installing
# our nodejs modules.
RUN npm install zmq md5 imagemagick
