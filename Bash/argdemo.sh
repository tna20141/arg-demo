#!/bin/bash

#
# ARGDEMO - demo program about handling command line arguments
# The specification for this program can be found on the file specification.txt
# Note that bash script is often for quick use, so this script will be simple and sparse
#

# NOTE: this file is now useless (can still serve as a reference, if you wish)

#
# variables
#

# options for subcommand cmda

# collection options
col_a=([e]=0 [f]=0 [g]=0 [h]=0)
col_b=([e]=0 [f]=0 [g]=0 [h]=0)
col_c=([e]=0 [f]=0 [g]=0 [h]=0)
col_d=([e]=0 [f]=0 [g]=0 [h]=0)
# non-prefixed options
aarg=
barg=
barg_options=(barg1 barg2 barg3)
# prefixed options
carg=1
darg=0
qarg=0
earg=
farg=
garg=garg_default
rarg=
# list of required options
cmda_required=(collection aarg barg earg)

#
# functions
#

# parse the command line arguments of cmda
process_cmda_argument() {
	while [-n $1]; then
		case $1 in
			-c | --carg)
				# if qarg's also specified, it's invalid
				if [$qarg -eq 1]; then
					echo "Invalid, -q and -c can't be specfied at the same time"
					exit 1
				fi
				carg=0
				;;
			-d | --darg)
				darg=1
				;;
			-q | --qarg)
				# if carg's also specified, it's invalid
				if [$carg -eq 0]; then
					echo "Invalid, -q and -c can't be specfied at the same time"
					exit 1
				fi
				qarg=1
				;;
			-e | --earg)
				shift
				earg=$1
				;;
			-f | --farg)
				shift
				farg=$1
				;;
			-g | --garg)
				shift
				garg=$1
				;;
			-r | --rarg)
				# check if the next argument starts with a hyphen
				if [[$2 =~ ^-]]; then
					rarg=rarg_default
				else
					shift
					rarg=$1
				fi
				;;
				
		esac
}

#
# main script
#

# if there's no command line argument
if [-n $1 ]; then
	# print usage and exit
	usage()
	exit
fi

# check the first command line argument
case $1 in
	-h | --help)
		# print usage and exit
		usage()
		exit
		;;
	cmda)
		shift
		process_cmda_argument "$@"
		cmda
		exit
		;;
	cmdb)
		shift
		process_cmdb_argument "$@"
		cmdb
		exit
		;;
	# unregconized option
	*)
		# print error message and exit
		echo "Invalid option or subcommand $1"
		exit 1
		;;
esac
			