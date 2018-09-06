FROM tsr1718/centos-zmq
RUN mkdir /zmq
COPY ./mybroker.js /zmq/mybroker.js
WORKDIR /zmq
EXPOSE 8059 8060
CMD node mybroker.js
