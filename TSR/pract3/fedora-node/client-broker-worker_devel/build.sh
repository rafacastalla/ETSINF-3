#!/bin/bash
for i in broker worker client
do
  cd $i
  docker build  -t $i .
  cd ..
done

