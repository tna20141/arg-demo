
#
# ARGDEMO - demo program about handling command line arguments
# The specification for this program can be found on the file specification.txt
#

#
# include modules
#
import argparse
import sys

#
# class definitions
#

# custom action class for collection arguments
class CollectionAction(argparse.Action):
	def __call__(self, parser, namespace, values, option_string=None):
		# process the argument to get the collection
		collection = process_collection(values)

		# if the returned collection is actually an error indicator
		if (isinstance(collection, (list))):
			# print it out and exit
			print('Invalid argument: ' + collection[1])
			sys.exit(0)

		# else, process normally
		setattr(namespace, self.dest, collection)


# custom action class for storing value in a flag-like argument (with a default value)
class CustomStoreAction(argparse.Action):
	def __call__(self, parser, namespace, values, option_string=None):
		# default value for this argument
		default_value = 'rarg_default'

		# if no additional input is provided when this option is specified
		if (values == None):
			# use the the fault value
			values = default_value
		setattr(namespace, self.dest, values)


# custom action class for storing choice in a flag-like argument (with a default choice)
class CustomChoiceAction(argparse.Action):
	def __call__(self, parser, namespace, values, option_string=None):
		# default value for this argument
		default_value = 'parg_1'

		# if no additional input is provided when this option is specified
		if (values == None):
			# use the the fault value
			values = default_value
		setattr(namespace, self.dest, values)

#
# function definitions
#

# function for subcommand cmda
def cmda_func(args):
	print('cmda is called')
	print(args)


# function for subcommand cmdb
def cmdb_func(args):
	print('cmdb is called')
	print(args)


# this function processes the collection argument string and produce the collection
def process_collection(string):
	delim = '+'									# the argument's delimiter between the 2 sides
	collection = {								# place to hold the collection's options
		'a': {'e':0, 'f':0, 'g':0, 'h':0},
		'b': {'e':0, 'f':0, 'g':0, 'h':0},
		'c': {'e':0, 'f':0, 'g':0, 'h':0},
		'd': {'e':0, 'f':0, 'g':0, 'h':0}
	}
	left_processed = [] 						# holds the left side options already processed

	# split the argument into two parts, by a delimiter
	sub_strings = string.split('+')
	# if the number of parts isn't 2, we have an error
	if (len(sub_strings) != 2):
		return ['error', 'please separate your argument with a plus sign']
	left_side = sub_strings[0]					# left part of the argument (before the delimiter)
	right_side = sub_strings[1]					# right part of the argument (after the delimiter)

	# process each character in the argument
	# for every character of the left part, process the right part
	for lchar in left_side:
		# if the option is valid
		if (lchar in collection.keys()):

			# if we already met the option (or character), return error message
			if (lchar in left_processed):
				return ['error', 'the option \'' + lchar + '\' is specified more than once']

			# put the option in the processed list
			left_processed += [lchar]
			# process the right part of the argument for this left sided option
			right_processed = []				# holds the right side options already processed
			for rchar in right_side:

				# if the right sided option is valid
				if (rchar in collection[lchar].keys()):

					# if we already met the option (or character), return error message
					if (rchar in right_processed):
						return ['error', 'the option \'' + rchar + '\' is specified more than once']

					# put the option in the processed list
					right_processed += [rchar]
					# store the options that are specified
					collection[lchar][rchar] = 1

				# if not
				else:
					# then the right part contains an invalid character, return error message
					return ['error', 'unregconized option \'' + rchar + '\'']
		else:
			# if the left part contains an invalid character, return error message
			return ['error', 'unregconized option \'' + lchar + '\'']

	# after processing, return the result collection
	return collection


# main function
def main():
	# main parser
	main_parser = argparse.ArgumentParser(
		prog='argdemo.py',
		description='demo program about handling command line arguments'
	)

	# sub parsers for subcommands
	sub_parsers = main_parser.add_subparsers(help='subcommands help')
	cmda = sub_parsers.add_parser('cmda', help='cmda help')		# cmda
	cmdb = sub_parsers.add_parser('cmdb', help='cmdb help')		# cmdb

	#
	# arguments for subcommand cmda
	#

	# non-prefixed arguments
	cmda.add_argument('collection', action=CollectionAction)
	cmda.add_argument('nparga')
	npargb_choices = ['argb_1', 'argb_2', 'argb_3']		# choices for npargb argument
	cmda.add_argument('npargb', choices=npargb_choices)

	# prefixed arguments
	# mutually exclusive group for -c and -q
	me_group = cmda.add_mutually_exclusive_group(required=True)
	me_group.add_argument('-c', '--carg', action='store_false')
	me_group.add_argument('-q', '--qarg', action='store_true')

	cmda.add_argument('-d', '--darg', action='store_true')

	cmda.add_argument('-e', '--earg', required=True)
	cmda.add_argument('-f', '--farg')
	cmda.add_argument('-g', '--garg', type=int, default=1)
	cmda.add_argument('-r', '--rarg', action=CustomStoreAction, nargs='?')

	# default function
	cmda.set_defaults(func=cmda_func)

	#
	# arguments for subcommand cmdb
	#

	# non-prefixed arguments
	cmdb.add_argument('targets', nargs='+')

	# prefixed arguments
	cmdb.add_argument('-j', '--jarg', action='store_true')
	cmdb.add_argument('-k', '--karg', action='store_true')
	cmdb.add_argument('-l', '--larg', action='store_true')

	cmdb.add_argument('-m', '--marg', required=True)
	narg_choices = ['narg_1', 'narg_2', 'narg_3']		# choices for marg argument
	cmdb.add_argument('-n', '--narg', choices=narg_choices)
	oarg_choices = ['oarg_1', 'oarg_2', 'oarg_3']		# choices for oarg argument
	cmdb.add_argument('-o', '--oarg', choices=oarg_choices, default='oarg_2')
	
	# NOTE!!: in the below scenario, when -p is specified with no additional input, it will not
	# be mutually exclusive with -s anymore. I think it's because of the way
	# add_mutually_exclusive_group() works

	# mutually exclusive group for -p and -r
	me_group2 = cmdb.add_mutually_exclusive_group()
	parg_choices = ['parg_1', 'parg_2', 'parg_3']
	me_group2.add_argument(
		'-p', '--parg', choices=parg_choices, action=CustomChoiceAction, nargs='?'
	)
	me_group2.add_argument('-s', '--sarg')

	# default function
	cmdb.set_defaults(func=cmdb_func)

	# parse command line arguments
	args = main_parser.parse_args()

	# call the appropriate function for the subcommand called
	args.func(args)


# entry point
if __name__ == '__main__':
	main()
