#!/bin/bash

node myworker_vp.js tcp://localhost:8060 Worker0 ready DONE0 verbose &
node myworker_vp.js tcp://localhost:8060 Worker1 ready DONE1 verbose &
node myworker_vp.js tcp://localhost:8060 Worker2 ready DONE2 verbose &
