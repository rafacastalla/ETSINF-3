#!/bin/bash
# Script that removes the broker client and worker images.
# We may need it in case we adapt the node programs being
# installed in each image.
for i in worker broker client
do
  docker rmi -f $i 2> /dev/null
done
