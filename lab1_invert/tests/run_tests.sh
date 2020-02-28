#!/usr/bin/env bash

#
#  Auto tests by KernelMrex
#

EXEC_NAME="invert"

cp ../cmake-build-debug/$EXEC_NAME .

for entry in *.test
do
  args=$entry
  result=$(./$EXEC_NAME "$args")

  prefix="${entry:0:-5}"

  if [ "$result" == "$(cat "$prefix".test.expected)" ]; then
    printf "Test %s done!\n" "${entry:0:-5}"
  else
    printf "\n"
    printf "Test %s has failed\n" "${entry:0:-5}"
    printf "Arguments: %s\n" "$args"
    printf "Output: %s\n" "$result"
    printf "Expected: %s\n" "$(cat "$prefix".test.expected)"
    printf "\n"
  fi
done

rm $EXEC_NAME