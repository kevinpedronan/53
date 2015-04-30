/* $begin shellmain */

#include "csapp.h"

#define MAXARGS   128



/* function prototypes */

void eval(char *cmdline);

int parseline(char *buf, char **argv);

int builtin_command(char **argv); 



int main() 

{

    char cmdline[MAXLINE]; /* Command line */



    while (1) {

	/* Read */

	printf("> ");                   

	Fgets(cmdline, MAXLINE, stdin); 

	if (feof(stdin))

	    exit(0);



	/* Evaluate */

	eval(cmdline);

    } 

}

/* $end shellmain */

  

/* $begin eval */

/* eval - Evaluate a command line */

void eval(char *cmdline) 

{

    char *argv[MAXARGS]; /* Argument list execve() */

    char buf[MAXLINE];   /* Holds modified command line */

    int bg;              /* Should the job run in bg or fg? */

    pid_t pid;           /* Process id */

    

    strcpy(buf, cmdline);

    bg = parseline(buf, argv); 

    if (argv[0] == NULL)  

    	return;   /* Ignore empty lines */



    if (!builtin_command(argv)) { 

    	if ((pid = Fork()) == 0) {   /* Child runs user job */

 	       char *temp;

    	   int index = 0;

    	   while(strcmp(argv[index],NULL)){

              if(strcmp(argv[index],"<")){

                   File in = open(argv[++index], O_RDONLY);

                   dup2(in, 0);

                   close(in);                   

              }else if(strcmp(argv[index], ">")){

                    if(strcmp(argv[--index][0], '2')){

                       

                    }else if(

                    

                    if(strcmp(argv[++index], ">"){

                        File out = open(argv

                    }

                                           

              ++index;

           }

 	

    	   switch(argv[0][0]){

              case '0':

                   

              case '2':

                   out = 

              case '&':

                   

              default:

                      

                                 

            }

    	 //  1<filename > asdf

    	    if (execve(argv[0], argv, environ) < 0) {

        		printf("%s: Command not found.\n", argv[0]);

        		exit(0);

    	    }

	}



	/* Parent waits for foreground job to terminate */

	if (!bg) {

	    int status;

	    if (waitpid(pid, &status, 0) < 0)

	    	unix_error("waitfg: waitpid error");

	}

	else

	    printf("%d %s", pid, cmdline);

    }

    return;

}



/* If first arg is a builtin command, run it and return true */

int builtin_command(char **argv) 

{

    if (!strcmp(argv[0], "quit")) /* quit command */

    	exit(0);  

    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */

    	return 1;

    return 0;                     /* Not a builtin command */

}

/* $end eval */



/* $begin parseline */

/* parseline - Parse the command line and build the argv array */

int parseline(char *buf, char **argv) 

{

    char *delim;         /* Points to first space delimiter */

    int argc;            /* Number of args */

    int bg;              /* Background job? */



    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */

    while (*buf && (*buf == ' ')) /* Ignore leading spaces */

	buf++;



    //Copy entire string into new string add whitespace around '>', '<' if necessary

    char temp;

    char* strTemp = malloc(MAXARGS);

    

    while(temp != '\0')

    {

                

    }

    

    /* Build the argv list */

    argc = 0;

    while ((delim = strchr(buf, ' '))) {

    	argv[argc++] = buf;

    	*delim = '\0';

    	buf = delim + 1;

    	while (*buf && (*buf == ' ')) /* Ignore spaces */

    	       buf++;

        }

    argv[argc] = NULL;

    

    if (argc == 0)  /* Ignore blank line */

    	return 1;



    /* Should the job run in the background? */

    if ((bg = (*argv[argc-1] == '&')) != 0)

	argv[--argc] = NULL;



    return bg;

}

/* $end parseline */


