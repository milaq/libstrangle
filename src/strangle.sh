#!/bin/sh

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

if [ "$#" -eq 0 ]; then
  programname=`basename "$0"`
  echo "ERROR: No program supplied"
  echo
  echo "Usage: $programname [fps-limit] <program-to-strangle>"
  echo
  echo "  fps-limit"
  echo "        an integer describing the desired maximum frame rate"
  echo "        If missing: the environment variable \"FPS\" will be used."
  echo "        If neither is set no limit will be applied"
  exit 1
fi

# Execute the strangled program under a clean environment
# pass through the FPS and overriden LD_PRELOAD environment variables
exec env FPS="${FPS}" LD_PRELOAD="${LD_PRELOAD}:libstrangle.so" "$@"
