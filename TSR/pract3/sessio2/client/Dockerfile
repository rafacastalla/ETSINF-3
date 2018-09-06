FROM tsr1718/centos-zmq
RUN mkdir /zmq
COPY ./my10client.js /zmq/myclient.js
WORKDIR /zmq
# We assume that each client is linked to the broker
# container.
CMD node my10client.js $BROKER_URL C1 M1 A $LOGGER_URL