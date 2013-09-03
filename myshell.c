#include <stdio.h>    //Standard Input/Output
#include <string.h>   //String Functions
#include <unistd.h>   //Process Manipulation
#include <stdlib.h>   //Standard Library
#include <sys/wait.h> //Wait for Process

#define MAX 1024      //input buffer size

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

	switch(pid = fork())
	{
		case -1: 
			fprintf(stderr, "Can't Fork It\n");
			//add perror(), gives actual reason for failure
			exit(-1);
		case 0: 
			//execvp, use this one
			//exece, parent command?
			if (execlp(line, line, NULL) < 0)
			{
				printf("Can't excute Command\n");
				exit(-1);
			}
		default:
			//while(wait(&status) != pid);
			//while(wait(NULL) > 0);
			waitpid(pid, &status, 0);

			//wait4( no hang option )

			//wait(NULL);
			//wait(&status);
			//exit(0);
	}
}

/*	Prompt	*/
/* Displays the shell prompt and
 * gathers a line of input from
 * stdin.	*/
void prompt(char *line)
{
	printf("myshell: ");	
	fgets(line, MAX, stdin);	
}

/*	Parse	*/
/* Prompt input is passed to this 
 * function for formatting. With
 * fgets we need to remove the
 * newline character.	*/
void parse(char *line)
{
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
int main()
{
	char line[MAX];	//shell input line

	system("clear");
	prompt(line);
	parse(line);

	while (strcmp(line, "exit") != 0)
	{	
		execute(line);
		prompt(line);	
		parse(line);	
	}

	return 0;
error:
	return -1;
}
