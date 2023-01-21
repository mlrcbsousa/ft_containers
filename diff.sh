#!/bin/bash

# run each binary and save output to file
if [ $# -eq 0 ]; then
  ./containers_ft > containers_ft.log
  ./containers_stl > containers_stl.log
elif [ $# -eq 1 ]; then
  ./containers_ft "$1" > containers_ft.log
  ./containers_stl "$1" > containers_stl.log
else
  ./containers_ft "$1" "$2" > containers_ft.log
  ./containers_stl "$1" "$2" > containers_stl.log
fi

# compare both ft and stl output files
diff containers_ft.log containers_stl.log