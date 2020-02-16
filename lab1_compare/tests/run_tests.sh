#!/usr/bin/env bash

#
#  Auto tests by KernelMrex
#

EXEC_NAME="compare"

cp ../cmake-build-debug/$EXEC_NAME .

for entry in *.test
do
  ./$EXEC_NAME "$entry" "$entry.toCompare"

  if cmp -s "$entry" "$entry.out"; then
    printf "Test '%s' done!\n" "$entry"
  else
    printf "Test '%s' has failed\n" "$entry"
    printf "Results in file %s\n" "$entry.out"
    break;
  fi
done

rm $EXEC_NAME