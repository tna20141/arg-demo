
/*
 * ARGDEMO - demo program about handling command line arguments
 * The specification for this program can be found on the file specification.txt
 */

/*
 * include files
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * macros
 */

/* macros serving as configuration for the collection argument */
#define DELIM_CHAR '+'					/* delimiter chacracter */
#define LSO_NUM 4						/* number of left sided options */
#define RSO_NUM 4						/* number of right sided options */

/* the buffer length for the string arguments */
#define BUFF_LEN 20

/*
 * struct definitions
 */

/*
 * NOTE: the below holder struct contain a set variable for each of the arguments.
 * The purpose of the set variable is to determined whether the argument associated with it
 * is specified in the commandline call or not, and whether it is required.
 * Specifically, if the argument is required, its set variable is initialized to 0.
 * If after parsing, the set variable is 2 (not 0), we know that it is indeed specified.
 * For non-required argument. We set the set variable to 1. If the argument is specified,
 * we set it to >3. So after parsing, we know that the argument is specified (>3) or not (1).
 * The same applies to the holder struct for cmdb. In fact, this is a usable mechanism
 * for future projects that involve command line arguments.
 */

/* argument holder struct for subcommand cmda's arguments */
struct arguments_cmda {

	int collection[LSO_NUM][RSO_NUM];	/* collection argument (non-prefixed) */
	int set_collection;

	char a_arg[BUFF_LEN];				/* aarg argument (non-prefixed) */
	int set_a_arg;

	char b_arg[BUFF_LEN];				/* barg argument (non-prefixed) */
	int set_b_arg;

	int c_arg;							/* carg argument (flag) */
	int set_c_arg;

	int d_arg;							/* darg argument (flag) */
	int set_d_arg;

	int q_arg;							/* qarg argument (flag) */
	int set_q_arg;

	int e_arg;							/* earg argument (prefixed), type int */
	int set_e_arg;

	char f_arg[BUFF_LEN];				/* farg argument (prefixed) */
	int set_f_arg;

	char g_arg[BUFF_LEN];				/* garg argument (prefixed) */
	int set_g_arg;

	char r_arg[BUFF_LEN];				/* rarg argument (prefixed) */
	int set_r_arg;
};

/* argument holder struct for subcommand cmdb's arguments */
struct arguments_cmdb {

	char** targets;						/* target arguments */
	int set_targets;
	int target_num;						/* number of targets */

	int j_arg;							/* jarg argument (flag) */
	int set_j_arg;

	int k_arg;							/* karg argument (flag) */
	int set_k_arg;

	int l_arg;							/* larg argument (flag) */
	int set_l_arg;

	char m_arg[BUFF_LEN];				/* marg argument (prefixed) */
	int set_m_arg;

	char n_arg[BUFF_LEN];				/* narg argument (prefixed) */
	int set_n_arg;

	char o_arg[BUFF_LEN];				/* oarg argument (prefixed) */
	int set_o_arg;

	char p_arg[BUFF_LEN];				/* parg argument (prefixed) */
	int set_p_arg;

	char s_arg[BUFF_LEN];				/* sarg argument (prefixed) */
	int set_s_arg;
};

/*
 * function prototypes
 */

void init_cmda_arguments(struct arguments_cmda*);
void check_cmda_arguments(struct arguments_cmda);
void init_cmdb_arguments(struct arguments_cmdb*);
void check_cmdb_arguments(struct arguments_cmdb);
void cmda(struct arguments_cmda);
void cmdb(struct arguments_cmdb);
void process_collection(int*, const char*);
void display_collection(const int*);
int  str_in(const char*, const char**, int);
void add_target(const char*, struct arguments_cmdb*);
void display_targets(struct arguments_cmdb);
void usage();
void clean_up();

/*
 * global variables
 */

struct arguments_cmda cmda_args;						/* argument holder for cmda */
struct arguments_cmdb cmdb_args;						/* argument holder for cmdb */

/* global variables serving as configuration for the barg argument */
char* barg_options[3] = {"barg_1", "barg_2", "barg_3"};	/* options for the barg argument */
int barg_options_num = 3;								/* number of barg options */

/* global variables serving as configuration for the narg argument */
char* narg_options[3] = {"narg_1", "narg_2", "narg_3"};	/* options for the narg argument */
int narg_options_num = 3;								/* number of narg options */

/* global variables serving as configuration for the oarg argument */
char* oarg_options[3] = {"oarg_1", "oarg_2"};			/* options for the oarg argument */
int oarg_options_num = 2;								/* number of oarg options */

/* global variables serving as configuration for the parg argument */
char* parg_options[3] = {"parg_1", "parg_2", "parg_3"};	/* options for the parg argument */
int parg_options_num = 3;								/* number of parg options */

/*
 * function definitions
 */

/* main function */
int main(int argc, char** argv) {
	int i, j, k = 0;
	int temp;

	/* if there's no command line argument */
	if (argc == 1) {
		/* print help and exit */
		usage();
		exit(1);
	}

	/* check the first command line argument */
	/* if it's the help option */
	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		/* print help and exit */
		usage();
		exit(0);
	}
	/* if it's the subcommand cmda */
	else if (strcmp(argv[1], "cmda") == 0) {
		/* initialize the argument holder for cmda */
		init_cmda_arguments(&cmda_args);

		/* parse the arguments */
		for (i = 2; i < argc; i++) {

			/* process prefixed arguments */

			/* if we meet the -h/--help option here */
			if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				;									/* ignore it */
			}
			/* carg argument */
			else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--carg") == 0) {
				/* if the flag hasn't been specified yet */
				if (cmda_args.set_c_arg <= 1) {
					cmda_args.c_arg ^= 1;			/* flip the flag */
					cmda_args.set_c_arg += 2;		/* remember that it's specified */
				}
			}
			/* darg argument */
			else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--darg") == 0) {
				/* if the flag hasn't been specified yet */
				if (cmda_args.set_d_arg <= 1) {
					cmda_args.d_arg ^= 1;			/* flip the flag */
					cmda_args.set_d_arg += 2;		/* remember that it's specified */
				}
			}
			/* qarg argument */
			else if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--qarg") == 0) {
				/* if the flag hasn't been specified yet */
				if (cmda_args.set_q_arg <= 1) {
					cmda_args.q_arg ^= 1;			/* flip the flag */
					cmda_args.set_q_arg += 2;		/* remember that it's specified */
				}
			}
			/* earg argument */
			else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--earg") == 0) {
				/* if this argument hasn't been specified yet */
				if (cmda_args.set_e_arg <= 1) {
					/* if there's no more argument, this option is invalid */
					if (i == argc-1) {
						/* print error message and exit */
						fprintf(stderr, "Invalid: %s requires additional input\n", argv[i]);
						exit(1);
					}
					i++;							/* get the next argument */
					sscanf(argv[i], "%d", &temp);	/* convert it to integer for earg option */
					cmda_args.e_arg = temp;
					cmda_args.set_e_arg += 2;		/* remember that it's specified */
				}
				/* else, it's specified more than 1 time and is invalid */
				else {
					/* print an error message an exit */
					fprintf(stderr, "Invalid: the option %s is specified more than once\n",
						argv[i]);
					exit(1);
				}
			}
			/* farg argument */
			else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--farg") == 0) {
				/* if this argument hasn't been specified yet */
				if (cmda_args.set_f_arg <= 1) {
					/* if there's no more argument, this option is invalid */
					if (i == argc-1) {
						/* print error message and exit */
						fprintf(stderr, "Invalid: %s requires additional input\n", argv[i]);
						exit(1);
					}
					i++;								/* get the next argument */
					strcpy(cmda_args.f_arg, argv[i]);
					cmda_args.set_f_arg += 2;			/* remember that it's specified */
				}
				/* else, it's specified more than 1 time and is invalid */
				else {
					/* print an error message an exit */
					fprintf(stderr, "Invalid: the option %s is specified more than once\n",
						argv[i]);
					exit(1);
				}
			}
			/* garg argument */
			else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--garg") == 0) {
				/* if this argument hasn't been specified yet */
				if (cmda_args.set_g_arg <= 1) {
					/* if there's no more argument, this option is invalid */
					if (i == argc-1) {
						/* print error message and exit */
						fprintf(stderr, "Invalid: %s requires additional input\n", argv[i]);
						exit(1);
					}
					i++;								/* get the next argument */
					strcpy(cmda_args.g_arg, argv[i]);
					cmda_args.set_g_arg += 2;			/* remember that it's specified */
				}
				/* else, it's specified more than 1 time and is invalid */
				else {
					/* print an error message an exit */
					fprintf(stderr, "Invalid: the option %s is specified more than once\n",
						argv[i]);
					exit(1);
				}
			}
			/* rarg argument */
			else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--rarg") == 0) {
				/* if this argument hasn't been specified yet */
				if (cmda_args.set_r_arg <= 1) {
					/* if there's still more arguments and the next argument isn't a prefixed */
					if (i < argc-1 && strchr(argv[i+1], '-') != argv[i+1]) {
						/* then it's the additional input, get it */
						i++;
						strcpy(cmda_args.r_arg, argv[i]);
					}
					cmda_args.set_r_arg += 2;				/* remember that it's specified */
				}
				/* else, it's specified more than 1 time and is invalid */
				else {
					/* print an error message an exit */
					fprintf(stderr, "Invalid: the option %s is specified more than once\n",
						argv[i]);
					exit(1);
				}
			}
			/* process flag arguments that are glued together as one */
			else if (strchr(argv[i], '-') == argv[i]) {
				/* each character that follows the hyphen indicates a flag */
				for (j = 1; j < strlen(argv[i]); j++) {
					switch (argv[i][j]) {
						/* carg flag */
						case 'c':
							/* if the flag hasn't been specified yet */
							if (cmda_args.set_c_arg <= 1) {
								cmda_args.c_arg ^= 1;			/* flip the flag */
								cmda_args.set_c_arg += 2;		/* remember that it's specified */
							};
							break;

						/* darg flag */
						case 'd':
							/* if the flag hasn't been specified yet */
							if (cmda_args.set_d_arg <= 1) {
								cmda_args.d_arg ^= 1;			/* flip the flag */
								cmda_args.set_d_arg += 2;		/* remember that it's specified */
							};
							break;

						/* qarg flag */
						case 'q':
							/* if the flag hasn't been specified yet */
							if (cmda_args.set_q_arg <= 1) {
								cmda_args.q_arg ^= 1;			/* flip the flag */
								cmda_args.set_q_arg += 2;		/* remember that it's specified */
							};
							break;

						/* none of the above, meaning the flag is invalid */
						default:
							/* print an error message an exit */
							fprintf(stderr, "Invalid option -%c\n", argv[i][j]);
							exit(1);
							break;
					}
				}
			}

			/* process non-prefixed arguments */
			/* subcommand cmda has 3 non-prefixed arguments */

			else {
				/* first one */
				if (k == 0) {
					/* this is the collection argument, process it in another function */
					process_collection((int*)cmda_args.collection, argv[i]);
					cmda_args.set_collection += 2;				/* remember that it's specified */
					k++;
				}
				/* second one */
				else if (k == 1) {
					strcpy(cmda_args.a_arg, argv[i]);			/* get the argument */
					cmda_args.set_a_arg += 2;					/* remember that it's specified */
					k++;
				}
				/* third one */
				else if (k == 2) {
					strcpy(cmda_args.b_arg, argv[i]);			/* get the argument */
					cmda_args.set_b_arg += 2;					/* remember that it's specified */
					k++;
				}
				/* if there's still more, it's invalid */
				else {
					/* print an error message and exit */
					fprintf(stderr, "Invalid argument %s: either the option is wrong \
or you entered too many positional arguments\n", argv[i]);
					exit(1);
				}
			}
		}

		/* done parsing, now we check (or validate) the arguments */
		check_cmda_arguments(cmda_args);

		/* done checking, let's execute the function for the command */
		cmda(cmda_args);
	}

	/* if it's the subcommand cmdb */
	else if (strcmp(argv[1], "cmdb") == 0) {
		/* initialize argument holder for cmdb */
		init_cmdb_arguments(&cmdb_args);

		/* parse the arguments */
		for (i = 2; i < argc; i++) {

			/* process the prefixed arguments */

			/* if we meet the -h/--help option here */
			if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				;									/* ignore it */
			}
			/* jarg argument */
			else if (strcmp(argv[i], "-j") == 0 || strcmp(argv[i], "--jarg") == 0) {
				/* if the flag hasn't been specified yet */
				if (cmdb_args.set_j_arg <= 1) {
					cmdb_args.j_arg ^= 1;			/* flip the flag */
					cmdb_args.set_j_arg += 2;		/* remember that it's specified */
				}
			}
			/* karg argument */
			else if (strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--karg") == 0) {
				/* if the flag hasn't been specified yet */
				if (cmdb_args.set_k_arg <= 1) {
					cmdb_args.k_arg ^= 1;			/* flip the flag */
					cmdb_args.set_k_arg += 2;		/* remember that it's specified */
				}
			}
			/* larg argument */
			else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--larg") == 0) {
				/* if the flag hasn't been specified yet */
				if (cmdb_args.set_l_arg <= 1) {
					cmdb_args.l_arg ^= 1;			/* flip the flag */
					cmdb_args.set_l_arg += 2;		/* remember that it's specified */
				}
			}
			/* marg argument */
			else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--marg") == 0) {
				/* if this argument hasn't been specified yet */
				if (cmdb_args.set_m_arg <= 1) {
					/* if there's no more argument, this option is invalid */
					if (i == argc-1) {
						/* print error message and exit */
						fprintf(stderr, "Invalid: %s requires additional input\n", argv[i]);
						exit(1);
					}
					i++;							/* get the next argument */
					strcpy(cmdb_args.m_arg, argv[i]);
					cmdb_args.set_m_arg += 2;		/* remember that it's specified */
				}
				/* else, it's specified more than 1 time and is invalid */
				else {
					/* print an error message an exit */
					fprintf(stderr, "Invalid: the option %s is specified more than once\n",
						argv[i]);
					exit(1);
				}
			}
			/* narg argument */
			else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--narg") == 0) {
				/* if this argument hasn't been specified yet */
				if (cmdb_args.set_n_arg <= 1) {
					/* if there's no more argument, this option is invalid */
					if (i == argc-1) {
						/* print error message and exit */
						fprintf(stderr, "Invalid: %s requires additional input\n", argv[i]);
						exit(1);
					}
					i++;								/* get the next argument */
					strcpy(cmdb_args.n_arg, argv[i]);
					cmdb_args.set_n_arg += 2;			/* remember that it's specified */
				}
				/* else, it's specified more than 1 time and is invalid */
				else {
					/* print an error message an exit */
					fprintf(stderr, "Invalid: the option %s is specified more than once\n",
						argv[i]);
					exit(1);
				}
			}
			/* oarg argument */
			else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--oarg") == 0) {
				/* if this argument hasn't been specified yet */
				if (cmdb_args.set_o_arg <= 1) {
					/* if there's no more argument, this option is invalid */
					if (i == argc-1) {
						/* print error message and exit */
						fprintf(stderr, "Invalid: %s requires additional input\n", argv[i]);
						exit(1);
					}
					i++;								/* get the next argument */
					strcpy(cmdb_args.o_arg, argv[i]);
					cmdb_args.set_o_arg += 2;			/* remember that it's specified */
				}
				/* else, it's specified more than 1 time and is invalid */
				else {
					/* print an error message an exit */
					fprintf(stderr, "Invalid: the option %s is specified more than once\n",
						argv[i]);
					exit(1);
				}
			}
			/* parg argument */
			else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--parg") == 0) {
				/* if this argument hasn't been specified yet */
				if (cmdb_args.set_p_arg <= 1) {
					/* if there's still more arguments and the next argument isn't a prefixed */
					if (i < argc-1 && strchr(argv[i+1], '-') != argv[i+1]) {
						/* then it's the additional input, get it */
						i++;
						strcpy(cmdb_args.p_arg, argv[i]);
					}
					cmdb_args.set_p_arg += 2;				/* remember that it's specified */
				}
				/* else, it's specified more than 1 time and is invalid */
				else {
					/* print an error message an exit */
					fprintf(stderr, "Invalid: the option %s is specified more than once\n",
						argv[i]);
					exit(1);
				}
			}
			/* sarg argument */
			else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--sarg") == 0) {
				/* if this argument hasn't been specified yet */
				if (cmdb_args.set_s_arg <= 1) {
					/* if there's no more argument, this option is invalid */
					if (i == argc-1) {
						/* print error message and exit */
						fprintf(stderr, "Invalid: %s requires additional input\n", argv[i]);
						exit(1);
					}
					i++;								/* get the next argument */
					strcpy(cmdb_args.s_arg, argv[i]);
					cmdb_args.set_s_arg += 2;			/* remember that it's specified */
				}
				/* else, it's specified more than 1 time and is invalid */
				else {
					/* print an error message an exit */
					fprintf(stderr, "Invalid: the option %s is specified more than once\n",
						argv[i]);
					exit(1);
				}
			}
			/* process flag arguments that are glued together as one */
			else if (strchr(argv[i], '-') == argv[i]) {
				/* each character that follows the hyphen indicates a flag */
				for (j = 1; j < strlen(argv[i]); j++) {
					switch (argv[i][j]) {
						/* jarg flag */
						case 'j':
							/* if the flag hasn't been specified yet */
							if (cmdb_args.set_j_arg <= 1) {
								cmdb_args.j_arg ^= 1;			/* flip the flag */
								cmdb_args.set_j_arg += 2;		/* remember that it's specified */
							};
							break;

						/* karg flag */
						case 'k':
							/* if the flag hasn't been specified yet */
							if (cmdb_args.set_k_arg <= 1) {
								cmdb_args.k_arg ^= 1;			/* flip the flag */
								cmdb_args.set_k_arg += 2;		/* remember that it's specified */
							};
							break;

						/* larg flag */
						case 'l':
							/* if the flag hasn't been specified yet */
							if (cmdb_args.set_l_arg <= 1) {
								cmdb_args.l_arg ^= 1;			/* flip the flag */
								cmdb_args.set_l_arg += 2;		/* remember that it's specified */
							};
							break;

						/* none of the above, meaning the flag is invalid */
						default:
							/* print an error message an exit */
							fprintf(stderr, "Invalid option -%c\n", argv[i][j]);
							exit(1);
							break;
					}
				}
			}
			/* if none of the above, we've finished processing prefixed arguments */
			else {
				/* get out of this loop and get to processing targets arguments */
				break;
			}
		}

		/* process targets arguments */

		/* continue from the last parsed argument */
		for ( ; i < argc; i++) {
			/* add the target to the cmdb argument holder's target list */
			add_target(argv[i], &cmdb_args);
			/* remember that a target is specified */
			cmdb_args.set_targets += 2;
		}

		/* done parsing, now we check (or validate) the arguments */
		check_cmdb_arguments(cmdb_args);

		/* done checking, let's execute the function for the command */
		cmdb(cmdb_args);
	}

	/* if none of the above */
	else {
		/* the argument is invalid, notify then exit */
		fprintf(stderr, "Invalid option or subcommand %s\n", argv[1]);
		exit(1);
	}

	/* clean up and exit the program */
	clean_up();

	return 0;
}

/* 
 * this function initializes the argument holder for subcommand cmda
 * in:
 *		reference to cmda argument holder
 * out:
 *		none
 */
void init_cmda_arguments(struct arguments_cmda* holder) {
	/* initialize the collection */
	memset(holder->collection, 0, sizeof(holder->collection));	/* all to 0 */
	holder->set_collection = 0;									/* required */

	/* initialize the aarg option */
	memset(holder->a_arg, 0, sizeof(holder->a_arg));			/* all to 0 */
	holder->set_a_arg = 0;										/* required */

	/* initialize the barg option */
	memset(holder->b_arg, 0, sizeof(holder->b_arg));			/* all to 0 */
	holder->set_b_arg = 0;										/* required */

	/* initialize the carg option */
	holder->c_arg = 1;			/* default to true */
	holder->set_c_arg = 1;		/* not required */

	/* initialize the darg option */
	holder->d_arg = 0;			/* default to false */
	holder->set_d_arg = 1;		/* not required */

	/* initialize the qarg option */
	holder->q_arg = 0;			/* default to false */
	holder->set_q_arg = 1;		/* not required */

	/* initialize the earg option */
	holder->e_arg = 0;			/* set to 0 */
	holder->set_e_arg = 0;		/* required */

	/* initialize the farg option */
	memset(holder->f_arg, 0, sizeof(holder->f_arg));			/* all to 0 */
	holder->set_f_arg = 1;										/* not required */

	/* initialize the garg option */
	strcpy(holder->g_arg, "default_garg");						/* set default garg option */
	holder->set_g_arg = 1;										/* not required */

	/* initialize the rarg option */
	strcpy(holder->r_arg, "default_rarg");						/* set default rarg option */
	holder->set_r_arg = 1;										/* not required */
}

/* 
 * this function initializes the argument holder for subcommand cmdb
 * in:
 *		reference to cmdb argument holder
 * out:
 *		none
 */
void init_cmdb_arguments(struct arguments_cmdb* holder) {
	/* initialize the targets */
	holder->targets = NULL;										/* points to NULL */
	holder->set_targets = 0;									/* required at least 1 */
	holder->target_num = 0;

	/* initialize the jarg option */
	holder->j_arg = 0;			/* default to false */
	holder->set_j_arg = 1;		/* not required */

	/* initialize the karg option */
	holder->k_arg = 0;			/* default to false */
	holder->set_k_arg = 1;		/* not required */

	/* initialize the larg option */
	holder->l_arg  = 0;			/* default to false */
	holder->set_l_arg = 1;		/* not required */

	/* initialize the marg option */
	memset(holder->m_arg, 0, sizeof(holder->m_arg));			/* all to 0 */
	holder->set_m_arg = 0;										/* required */

	/* initialize the narg option */
	memset(holder->n_arg, 0, sizeof(holder->n_arg));			/* all to 0 */
	holder->set_n_arg = 1;										/* not required */

	/* initialize the oarg option */
	strcpy(holder->o_arg, "oarg_2");						/* set default oarg option */
	holder->set_o_arg = 1;										/* not required */

	/* initialize the parg option */
	strcpy(holder->p_arg, "parg_3");						/* set default parg option */
	holder->set_p_arg = 1;										/* not required */

	/* initialize the sarg option */
	memset(holder->s_arg, 0, sizeof(holder->s_arg));			/* all to 0 */
	holder->set_s_arg = 1;										/* not required */
}

/*
 * this function checks the argument holder (after the arguments are parsed) of cmda
 * if any of the criteria isn't satisfied, the function will terminate the program
 * in:
 *		the cmda argument holder
 * out:
 *		none
 */
void check_cmda_arguments(struct arguments_cmda holder) {
	int i;				/* an integer for any necessary looping */

	/* if there's any (required) argument that hasn't been set */
	if (holder.set_collection == 0 || holder.set_a_arg == 0 || holder.set_b_arg == 0 ||
		holder.set_c_arg == 0 || holder.set_d_arg == 0 || holder.set_q_arg == 0 ||
		holder.set_e_arg == 0 || holder.set_f_arg == 0 || holder.set_g_arg == 0 ||
		holder.set_r_arg == 0) {

		/* print an error message and exit */
		fprintf(stderr, "Invalid: you didn't specified enough arguments\n");
		exit(1);
	}

	/* if barg argument isn't an element of the predefined subset */
	if (str_in(holder.b_arg, (const char**)barg_options, barg_options_num) == 0) {
		/* print an error message and exit */
		fprintf(stderr, "Invalid argument %s. Must be 1 of the following options:",
			holder.b_arg);
		for (i = 0; i < barg_options_num; i++)
			fprintf(stderr, " %s", barg_options[i]);
		fprintf(stderr, "\n");
		exit(1);
	}

	/* if the -c and the -q flags are both set, it's invalid */
	if (holder.set_c_arg >= 2 && holder.set_q_arg >= 2) {
		/* print an error message and exit */
		fprintf(stderr, "The -c/--carg option and the -q/--qarg option can't be specified \
at the same time\n");
		exit(1);
	}
}

/*
 * this function checks the argument holder (after the arguments are parsed) of cmdb
 * if any of the criteria isn't satisfied, the function will terminate the program
 * in:
 *		the cmdb argument holder
 * out:
 *		none
 */
void check_cmdb_arguments(struct arguments_cmdb holder) {
	int i;

	/* if there's any (required) argument that hasn't been set */
	if (holder.set_targets == 0 || holder.set_j_arg == 0 || holder.set_k_arg == 0 ||
		holder.set_l_arg == 0 || holder.set_m_arg == 0 || holder.set_n_arg == 0 ||
		holder.set_o_arg == 0 || holder.set_p_arg == 0 || holder.set_s_arg == 0) {

		/* print an error message and exit */
		fprintf(stderr, "Invalid: you didn't specified enough arguments\n");
		exit(1);
	}

	/* if narg is specified */
	if (holder.set_n_arg >= 2) {
		/* if narg argument isn't an element of the predefined subset */
		if (str_in(holder.n_arg, (const char**)narg_options, narg_options_num) == 0) {
			/* print an error message and exit */
			fprintf(stderr, "Invalid argument %s. Must be 1 of the following options:",
				holder.n_arg);
			for (i = 0; i < narg_options_num; i++)
				fprintf(stderr, " %s", narg_options[i]);
			fprintf(stderr, "\n");
			exit(1);
		}
	}

	/* NOTE: oarg doesn't need to be checked if it's specified because it's not a flag-like */
	/* if oarg argument isn't an element of the predefined subset */
	if (str_in(holder.o_arg, (const char**)oarg_options, oarg_options_num) == 0) {
		/* print an error message and exit */
		fprintf(stderr, "Invalid argument %s. Must be 1 of the following options:",
			holder.o_arg);
		for (i = 0; i < oarg_options_num; i++)
			fprintf(stderr, " %s", oarg_options[i]);
		fprintf(stderr, "\n");
		exit(1);
	}

	/* if parg is specified */
	if (holder.set_p_arg >= 2) {
	/* if parg argument isn't an element of the predefined subset */
		if (str_in(holder.p_arg, (const char**)parg_options, parg_options_num) == 0) {
			/* print an error message and exit */
			fprintf(stderr, "Invalid argument %s. Must be 1 of the following options:",
				holder.p_arg);
			for (i = 0; i < parg_options_num; i++)
				fprintf(stderr, " %s", parg_options[i]);
			fprintf(stderr, "\n");
			exit(1);
		}
	}

	/* if the parg and the sarg option are both set, it's invalid */
	if (holder.set_p_arg >= 2 && holder.set_s_arg >= 2) {
		/* print an error message and exit */
		fprintf(stderr, "The -p/--parg option and the -s/--sarg option can't be specified \
at the same time\n");
		exit(1);
	}
}

/*
 * this is the function of the subcommand cmda (all it does now is print out information)
 * in:
 *		the cmda argument holder
 * out:
 *		none
 */
void cmda(struct arguments_cmda holder) {
	/* just print out the information */
	/* note that for farg and rarg, we need to check if they were specified by the user */
	printf("CMDA is called!\n");
	display_collection((int*)holder.collection);
	printf("aarg: %s\n", holder.a_arg);
	printf("barg: %s\n", holder.b_arg);
	printf("carg: %d\n", holder.c_arg);
	printf("darg: %d\n", holder.d_arg);
	printf("qarg: %d\n", holder.q_arg);
	printf("earg: %d\n", holder.e_arg);
	if (holder.set_f_arg <= 1) {
		printf("farg not set\n");
	}
	else {
		printf("farg: %s\n", holder.f_arg);
	}
	printf("garg: %s\n", holder.g_arg);
	if (holder.set_r_arg <= 1) {
		printf("rarg not set\n");
	}
	else {
		printf("rarg: %s\n", holder.r_arg);
	}
}

/*
 * this is the function of the subcommand cmdb (all it does now is print out information)
 * in:
 *		the cmdb argument holder
 * out:
 *		none
 */
void cmdb(struct arguments_cmdb holder) {
	/* just print out the information */
	/* note that for narg, parg and sarg, we need to check if they were specified by the user */
	printf("CMDB is called!\n");
	printf("jarg: %d\n", holder.j_arg);
	printf("karg: %d\n", holder.k_arg);
	printf("larg: %d\n", holder.j_arg);
	printf("marg: %s\n", holder.m_arg);
	if (holder.set_n_arg <= 1) {
		printf("narg not set\n");
	}
	else {
		printf("narg: %s\n", holder.n_arg);
	}
	printf("oarg: %s\n", holder.o_arg);
	if (holder.set_p_arg <= 1) {
		printf("parg not set\n");
	}
	else {
		printf("parg: %s\n", holder.p_arg);
	}
	if (holder.set_s_arg <= 1) {
		printf("sarg not set\n");
	}
	else {
		printf("sarg: %s\n", holder.s_arg);
	}
	display_targets(holder);
}

/*
 * this function processes the collection argument string and stores the result
 * in the collection holder inside the argument holder
 * in:
 *		the collection holder
 *		the argument string
 * out:
 *		none
 */
void process_collection(int* holder, const char* arg) {
	char left_side[BUFF_LEN];		/* stores the left part (before the delimiter) */
	char right_side[BUFF_LEN];		/* stores the right part (after the delimiter) */
	char* pos;						/* postion of the delimiter in the argument string */
	int arg_len;					/* length of the argument string */
	char left_sided_option;			/* the left sided option to be processed */
	int i, j;

	arg_len = strlen(arg);

	/* split the argument string into two parts */
	pos = strchr(arg, DELIM_CHAR);
	/* if the delimiter is not found, at the beginning or at the end of the argument string */
	if (pos == NULL || pos == arg || pos == arg+arg_len-1) {
		/* then the format is invalid, print an error message and exit */
		fprintf(stderr, "Invalid collection argument format\n");
		exit(1);
	}
	strncpy(left_side, arg, pos-arg);
	left_side[pos-arg] = 0;
	strncpy(right_side, pos+1, arg_len-(pos-arg));

	/* process every character of the left part */
	for(i = 0; i < strlen(left_side); i++) {
		switch(left_side[i]) {
			/* first left sided option, option a */
			case 'a':
				left_sided_option = 0;			/* set the left sided option to be processed */
				break;

			/* second left sided option, option b */
			case 'b':
				left_sided_option = 1;			/* set the left sided option to be processed */
				break;

			/* third left sided option, option c */
			case 'c':
				left_sided_option = 2;			/* set the left sided option to be processed */
				break;

			/* fourth left sided option, option d */
			case 'd':
				left_sided_option = 3;			/* set the left sided option to be processed */
				break;

			/* invalid option */
			default:
				/* print error message and exit */
				fprintf(stderr, "Invalid left side collection option %c\n", left_side[i]);
				exit(1);
				break;
		}

		/* for the left sided option above, process every character of the right part */
		for(j = 0; j < strlen(right_side); j++) {
			switch(right_side[j]) {
			/* first right sided option, option e */
				case 'e':
					holder[left_sided_option*RSO_NUM] = 1;		/* set */
					break;

				/* first right sided option, option f */
				case 'f':
					holder[left_sided_option*RSO_NUM+1] = 1;	/* set */
					break;

				/* first right sided option, option g */
				case 'g':
					holder[left_sided_option*RSO_NUM+2] = 1;	/* set */
					break;

				/* first right sided option, option h */
				case 'h':
					holder[left_sided_option*RSO_NUM+3] = 1;	/* set */
					break;

					/* invalid option */
				default:
					/* print error message and exit */
					fprintf(stderr, "Invalid right side collection option %c\n", right_side[j]);
					exit(1);
					break;
			}
		}
	}
}

/*
 * this function displays the collection argument processed
 * in:
 *		the collection holder
 * out:
 *		none
 */
void display_collection(const int* holder) {
	int i, j;
	char left_sided_option;

	printf("Collection argument:");
	/* for each left sided option */
	for (i = 0; i < LSO_NUM; i++) {
		/* determine which left sided option we're working with */
		switch(i) {
			case 0:
				left_sided_option = 'a';
				break;
			case 1:
				left_sided_option = 'b';
				break;
			case 2:
				left_sided_option = 'c';
				break;
			case 3:
				left_sided_option = 'd';
				break;
		}
		printf(" %c->", left_sided_option);
		/* for each right sided option, if it is set, print it out */
		if (holder[i*RSO_NUM] == 1)
			printf("%c", 'e');
		if (holder[i*RSO_NUM+1] == 1)
			printf("%c", 'f');
		if (holder[i*RSO_NUM+2] == 1)
			printf("%c", 'g');
		if (holder[i*RSO_NUM+3] == 1)
			printf("%c", 'h');
	}
	printf("\n");
}

/*
 * this function adds the target argument (string) to the target list in the cmdb argument holder
 * in:
 *		the target argument string
 *		reference to the cmdb argument holder
 * out:
 *		none
 */
void add_target(const char* target, struct arguments_cmdb* holder) {
	char** temp;
	char* new_target;
	int i;

	/* allocate memory for the new string pointer list */
	temp = (char**)calloc(holder->target_num+1, sizeof(char*));

	/* copy the old list to the new one */
	for (i = 0; i < holder->target_num; i++)
		temp[i] = holder->targets[i];

	/* allocate memory for the new target */
	new_target = malloc(strlen(target)+1);

	/* add the new target to the new list */
	temp[i] = new_target;
	strcpy(new_target, target);

	/* remove the old target lsit */
	free(holder->targets);

	/* update the holder's target list */
	holder->targets = temp;
	/* update the number of targets */
	holder->target_num++;
}

/*
 * this function displays the target arguments processed
 * in:
 *		the pointer to the targets
 * out:
 *		none
 */
void display_targets(struct arguments_cmdb holder) {
	int i;

	printf("Targets:");
	/* print each target out */
	for (i = 0; i < holder.target_num; i++) {
		printf(" %s", holder.targets[i]);
	}
	printf("\n");
}

/*
 * this function checks if a string is in a predefined set or not
 * in:
 *		the string to be checked
 *		the predefined set
 *		the number of elements in the predefined set
 * out:
 *		1 if the string is in the set, 0 if not
 */
int str_in(const char* str, const char** set, int num) {
	int i;

	/* check every element of the set */
	for (i = 0; i < num; i++) {
		/* if we find a match */
		if (strcmp(str, set[i]) == 0)
			/* return 1 */
			return 1;
	}

	/* if there's no match, return 0 */
	return 0;
}

/*
 * this function is a simple help printing function
 * in:
 *		none
 * out:
 *		none
 */
void usage() {
	/* display a very simple help message */
	printf("This is a simple help message. The purpose of it is for testing only.\n");
	printf("For further information and a proper usage, please see the file specification.txt\n");
}

/*
 * this function cleans things up (mostly deallocate dynamic memory) before the program terminates
 * in:
 *		none
 * out:
 *		none
 */
void clean_up() {
	int i;

	/* deallocate cmdb argument holder's targets list memory */
	for (i = 0; i < cmdb_args.target_num; i++) {
		free(cmdb_args.targets[i]);
	}
	free(cmdb_args.targets);
}
