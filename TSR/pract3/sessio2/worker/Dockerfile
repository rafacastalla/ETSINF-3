FROM tsr1718/centos-zmq
RUN mkdir /zmq
COPY ./myworker.js /zmq/myworker.js
WORKDIR /zmq
# We assume that each worker is linked to the broker
# container.
CMD node myworker $BROKER_URL W1 ready T1 A $LOGGER_URL
