#!/usr/bin/python

import sys
import re

def getKimTraffic(folder):
  lines = tuple(open(folder + '/si-net-l2-gm_kimnet.report', 'r'))

  rule = re.compile(r"bus_bp_[0-9]+.TransferredBytes = ([0-9]+)")

  transferedBytes = 0;
  for line in lines:
    match = rule.match(line)
    if not match == None:
      transferedBytes += int(match.group(1))
  print folder + " transfered bytes : " + str(transferedBytes);

def main():
  folder = sys.argv[1]
  getKimTraffic(folder)


if __name__ == "__main__":
  main();
