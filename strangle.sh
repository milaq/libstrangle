#!/bin/sh

if [ $# -eq 0 ]; then
  echo "ERROR: No arguments"
  echo
  echo "strangle.sh <fps-limit> <program-to-strangle>"
  echo
  echo "The fps-limit argument is required, and is expected to be an"
  echo "integer value"
  exit
fi

if [ "$1" -eq "$1" ] 2>/dev/null; then
  # Check if the first command line argument is a valid number
  FPS=$1
  shift
else
  if ! [ "$FPS" -eq "$FPS" ] 2>/dev/null; then
    # Check if the environmental variable FPS is a valid number
    FPS=0
  fi
fi

export FPS="${FPS}"
LD_PRELOAD="libstrangle.so:${LD_PRELOAD}" "$@"
