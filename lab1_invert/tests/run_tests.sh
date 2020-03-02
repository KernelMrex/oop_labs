#!/usr/bin/env bash

#
#  Auto tests by KernelMrex
#

EXEC_NAME="invert"

cp ../cmake-build-debug/$EXEC_NAME .

for entry in *.test
do
  args=$entry
  ./$EXEC_NAME "$args" > test_1.tmp
  prefix="${entry:0:-5}"

  diff=$(cmp "test_1.tmp" "$prefix".test.expected)

  if [ "$diff" == "" ]; then
    printf "Test %s done!\n" "${entry:0:-5}"
  else
    printf "\n"
    printf "Test %s has failed\n" "${entry:0:-5}"
    printf "Arguments: %s\n" "$args"
    printf "Output: %s\n" "$(cat test_1.tmp)"
    printf "Expected: %s\n" "$(cat "$prefix".test.expected)"
    printf "Comment: %s\n" "$diff"
    printf "\n"
  fi
done

rm test_1.tmp
rm $EXEC_NAME