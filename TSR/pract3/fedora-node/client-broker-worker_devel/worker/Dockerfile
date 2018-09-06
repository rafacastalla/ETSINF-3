FROM tsr/fedora-node-devel
COPY ./worker.js worker.js
# We assume that each worker is linked to the broker
# container. 
CMD node worker $BROKER_URL
