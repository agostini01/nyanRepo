#!/bin/bash

../../../bin/m2s --net-config net.ini --net-sim mynet --net-msg-size 4096 \
  --net-max-cycles 100000 --net-injection-rate 0.001 \
  --net-report net.report --net-debug net.debug
 
