FROM tsr/fedora-node-devel
COPY ./client.js client.js
# We assume that each worker is linked to the broker
# container. 
CMD node client $BROKER_URL
