#!/bin/bash
if [ $# -eq 0 ]; then
	echo "No arguments"
	exit
fi

# Check if the FPS= argument is given
c=0
for i in "$@"; do
	case $i in
		fps=*|FPS=*)
			f="${i#*=}"
			args=( "$@" )
			unset args[c]
			((c--))
			set -- "${args[@]}"
			;;
		*)
			;;
	esac
((c++))
done

if [ "$1" -eq "$1" ] 2>/dev/null; then
	# Check if the first command line argument is a valid number
	FPS=$1
	shift
elif [ "$f" -eq "$f" ] 2>/dev/null; then
	FPS=$f
else
	if ! [ "$FPS" -eq "$FPS" ] 2>/dev/null; then
		# Check if the environmental variable FPS is a valid number
		FPS=0
	fi
fi
export "FPS=${FPS}"
LD_PRELOAD="libstrangle.so:${LD_PRELOAD}" "$@"
