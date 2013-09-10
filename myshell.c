#include <stdio.h>    //Standard Input/Output
#include <signal.h>   //Signal Handler
#include <string.h>   //String Functions
#include <unistd.h>   //Process Manipulation
#include <stdlib.h>   //Standard Library
#include <sys/wait.h> //Wait for Process

#define MAX 1024      //input buffer size

/*	Helper	*/
/* This function is invoked if the user
 * supplies an invalid prompt	*/
int help(char *argv[]) 
{
	printf("Specifying a different prompt name is optional:\n");
	printf("Usage: %s [newprompt]\n", argv[0]);
    	printf("Keep it under 20 chars\n");
    	return EXIT_FAILURE;
}

/*	Signal Handler	*/
void signal_handler(int signal)
{ 
	printf("Caught Signal: %d\n", signal); 
	exit(signal); 
}

/*	Execute		*/
/* Attempt to create a new process
 * by using fork(). A child process
 * will be created and send the 
 * parent process to the background.
 * This child process will execute
 * system functions based on the
 * shell prompt input.	*/
void execute(char *line)
{
	pid_t pid;	
	int status;

	//printf("Entering Execute Function\n");
	//sleep(1);	

	switch(pid = fork())
	{
		case -1: 
			perror("Can't Fork It\n\n");
			exit(-1);
		case 0:
			//printf("Child PID: %d\n", (int)pid);

			//execvp(line, &line); //randomly doesn't work wtf?!
			execlp(line, line, NULL); //exits case with success execute
			printf("Can't excute Command\n");
			exit(-1);
		default:
			//printf("Parent PID: %d\n", (int)pid);
			while(waitpid(pid, &status, WNOHANG) >= 0) //this should be exactly what we need
			{
			; //call out exit status
			}
			//wait4( no hang option )
			//exit(0);  //no needed?
	}
}

/*	Prompt	*/
/* Displays the shell prompt and
 * gathers a line of input from
 * stdin.	*/
void prompt(char *line, char *option)
{
	//printf("Entering Prompt Function\n\n");
	//sleep(1);

	if (option == NULL)
	{
		printf("myshell: ");	
	}
	else
	{
		printf("%s ", option);	
	}	
	
	fgets(line, MAX, stdin);
}

/*	Parse	*/
/* Prompt input is passed to this 
 * function for formatting. With
 * fgets we need to remove the
 * newline character.	*/
void parse(char *line)
{	
	//printf("Entering Parse Function\n\n");
	//sleep(1);

	//replace newline character with null character	
	if (line[strlen(line)-1] == '\n')
	{	
		line[strlen(line)-1] = '\0';
	}
}

/*	Simple Shell	*/
/* - Compile by running "make" in 
 *   the current directory 
 * - Run this program by typing
 *   "./myshell" 
 * - Shell prompt, "myshell:"
 * - Type stuff, It should be cool	*/
int main(int argc, char *argv[])
{
	char line[MAX];	//shell input line
	char *option = NULL;  //optional prompt name

	// Too many arguments, string too long, check for only alphas? 
	if (argc > 2 || strlen(argv[argc-1]) > 20 ) 
	{
		int fail = help(argv);
		exit(fail);
	}

	//if arguments were supplied use the last one	
	if (argc == 2)
	{
		option = argv[argc-1];
	}

	system("clear");	//clear screen
	prompt(line, option);
	parse(line);
	
	while (!feof(stdin) && strcmp(line, "exit") != 0)
	{
		signal(SIGINT, signal_handler);	
		execute(line);	
		prompt(line, option);
		parse(line);	
	}

	return 0;
error:
	return -1;
}
