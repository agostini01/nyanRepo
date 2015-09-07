#!/bin/bash

../../../bin/m2s --net-config net.ini --net-sim mynet --net-msg-size 4096 \
  --net-max-cycles 100000 --net-injection-rate 0.001 \
  --net-report serialized.report --net-debug serialized.debug

../../../bin/m2s --net-config net.ini --net-sim mynet --net-msg-size 4096 \
  --net-max-cycles 100000 --net-injection-rate 0.001 \
  --net-report parallel.report --net-debug parallel.debug \
  --net-ignore-buffer-busy
 
 
