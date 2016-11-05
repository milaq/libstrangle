#!/bin/sh

if [ "$#" -eq 0 ]; then
  echo "ERROR: No arguments"
  echo
  echo "strangle.sh <fps-limit> <program-to-strangle>"
  echo
  echo "The fps-limit argument is required, and is expected to be an"
  echo "integer value. If it is not provided, libstrangle will assume"
  echo "there is no FPS limit"
  exit
fi

if [ "$1" -eq "$1" ] 2>/dev/null; then
  # Check if the first command line argument is a valid number
  FPS="$1"
  shift
else
  if ! [ "$FPS" -eq "$FPS" ] 2>/dev/null; then
    # Check if the environmental variable FPS is a valid number
    FPS=0
  fi
fi

# Execute the strangled program under a clean environment
# pass through the FPS and overriden LD_PRELOAD environment variables
exec env FPS="${FPS}" LD_PRELOAD="libstrangle.so:${LD_PRELOAD}" "$@"
