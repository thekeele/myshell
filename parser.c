#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Example of parsing with strsep(). */

main(int argc, char *argv[]) {

	int i;
	char **arg;
	int arg_count = 0;
	char **arg_tmp;

  /* This makes space for an array of pointers to strings (char *) that
 *      will contain the parsed arguments  */
	if ((arg = (char **)malloc((arg_count + 1) * sizeof(char *))) == NULL) {
		perror("malloc failed");
	}

	arg_tmp = &argv[1];

	for (i = 0; arg[i] = strsep(arg_tmp, ";"); arg[i] != '\0') {
		printf("%s\n", arg[i]);
		arg_count++;
		i++;
		if ((arg = (char **)realloc(arg, (arg_count + 1)*sizeof(char *)))
			== NULL) {
			perror("realloc failed");
		}
	}

	printf("-----\n");

	for(i=0; arg[i] != NULL; i++) {
		printf("%d:%s\n", i, arg[i]);
	}

}


