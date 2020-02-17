#!/usr/bin/env bash

#
#  Auto tests by KernelMrex
#

EXEC_NAME="compare"

cp ../cmake-build-debug/$EXEC_NAME .

for entry in *_1.test
do
  result=$(./$EXEC_NAME "$entry" "${entry:0:-7}_2.test")

  if [ "$result" == "$(cat ${entry:0:-7}_expected.test)" ]; then
    printf "Test %s done!\n" "${entry:0:-7}"
  else
    printf "Test %s has failed\n" "${entry:0:-7}"
    break;
  fi
done

rm $EXEC_NAME