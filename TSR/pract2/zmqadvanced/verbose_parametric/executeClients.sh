#!/bin/bash

#number=1
#while [ $number -lt $1 ]; do
#
#	node myclientclass.js tcp://localhost:8059 Client$number WORK$number R verbose &
#	echo "Client$number on execution..."
#
#	number=$((number + 1))
#done

	node myclient_vp.js tcp://localhost:8059 Client0 WORK0 verbose &
	node myclient_vp.js tcp://localhost:8059 Client1 WORK1 verbose &
	node myclient_vp.js tcp://localhost:8059 Client2 WORK2 verbose &
	node myclient_vp.js tcp://localhost:8059 Client3 WORK3 verbose &
