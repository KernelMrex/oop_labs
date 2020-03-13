#!/usr/bin/env bash

#
#  Auto tests by KernelMrex
#

EXEC_NAME="vector"

cp ../cmake-build-debug/$EXEC_NAME .

for entry in *.test.args; do
  prefix="${entry:0:-10}"
  args=($(cat "$entry"))

  testType=${args[0]} || ""
  inputFile=${args[1]} || ""
  outputFile=${args[2]} || ""

  fileToCompare=""
  if [ "$testType" == "bad" ]; then
    ./$EXEC_NAME $inputFile $outputFile >program_result.tmp
    fileToCompare="program_result.tmp"
  elif [ "$testType" == "good" ]; then
    ./$EXEC_NAME "$inputFile" "$outputFile"
    fileToCompare="$outputFile"
  elif [ "$testType" == "std_input" ]; then
    ./$EXEC_NAME < "$prefix.test.input" > program_result.tmp
    fileToCompare="program_result.tmp"
  elif [ "$testType" == "not_implemented" ]; then
    printf "Skipping '%s' test... Reason: Not implemented yet!\n" "$prefix"
    continue
  fi

  if cmp "$fileToCompare" "$prefix".test.expected; then
    printf "Test %s done!\n" "$prefix"
  else
    printf "\n"
    printf "Test %s has failed\n" "$prefix"
    printf "Arguments: %s %s\n" "${args[1]}" "${args[2]}"
    printf "Output: %s\n" "$(cat "$fileToCompare")"
    printf "Expected: %s\n" "$(cat "$prefix".test.expected)"
    printf "\n"
  fi
  rm "$fileToCompare"
done

rm $EXEC_NAME
