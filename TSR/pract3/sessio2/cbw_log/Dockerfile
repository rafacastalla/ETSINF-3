FROM tsr1718/centos-zmq
RUN mkdir /zmq
COPY ./logger.js /zmq/logger.js
WORKDIR /zmq
EXPOSE 8066
CMD node logger 8066