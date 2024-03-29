/*
 * This is sample code generated by rpcgen and Modifiied by Palak Shah
 * This code has borrowed some functions and code from hw2.c for local FS given along with hw2.pdf
 * This code is submitted as hw2 for Distributed Computing
 */

#include "hw2.h"

int main (int argc, char *argv[]) {
	char *host;
	
	CLIENT *clnt;
	outparams  *result_1;
	inparams  in_1;
	inparams  fileprog_1_arg;
	
	char operation[MAXCOMMANDLEN + 1];
	char file_name[MAXFILENAME + 1];
	char string[MAXSTRLEN + 1];
	int len = -100;
	file* lst_final;
	char *data;
	long fsize;
	int res;	 

	/*initialisation*/
	in_1.cmd = "no-op";
	in_1.infile = "what";
	in_1.len = -100;
	in_1.str = "nothing here";
	
	//check if user has entered a valid command and save it into the variable len	
	if(argc < 3) {
		printf ("usage: %s [host] operation [filename] [string | length]\n", argv[0]);
		exit(1);
	} else {
		host = argv[1];
		strcpy (operation, argv[2]);
		if(argc > 3) {
			strcpy (file_name, argv[3]);
		} else {
			if ((strcmp(operation, CAT) 	== 0) 	|| 
			    (strcmp(operation, WRITE) 	== 0) 	||	 
			    (strcmp(operation, FIND)   	== 0) 	||
			    (strcmp(operation, RM) 	== 0) ) {
				printf ("usage: %s operation [host] [filename] [string | length]\n", argv[0]);
				exit(1);
			}
		}
		if (argc > 4) {
			strcpy (string, argv[4]);
			len = atoi (string);

			int i = 5;
			while (i < argc) {
				strcat(string, " ");
				strcat(string, argv[i]);
				i ++;
			}
		}
	
	}//else ends here

	in_1.cmd = operation;
	in_1.infile = file_name;
	in_1.len = len;
	in_1.str = string;
	
	//create client, make rpc call	
#ifndef	DEBUG
	clnt = clnt_create (host, HWPROG, HWVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	//call server function
	result_1 = fileprog_1(&in_1, clnt);

	//logic to print results
	if (result_1 == (outparams *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	//for operation = cat
	else if ((result_1 != (outparams *) NULL)&&(strcmp(operation, CAT) == 0)) {
		if (result_1->errcode == 0) {
			if (len <= 0) {
				printf("please speficy the number of bytes to read from file %s\n", file_name);
				exit(1);
			}
			if (result_1->outfsize < 0) {
				printf("Error in opening:\n");
			} else {
				printf("%s\n", result_1->outdata);
			}
		} else if(result_1->errcode == -1) {
			printf("Error in opening %s\n", file_name);
		} else {
			printf("File %s has been created \n", file_name);
		}//inner loop ends here
	}
	
	//for operation = find
	else if ((result_1 != (outparams *) NULL)&&(strcmp(operation, FIND) == 0)) {		
		if (result_1->outfsize < 0) {
			printf("Could not find %s\n", file_name);
		} else {
			printf("File %s has %ld bytes\n", file_name, result_1->outfsize);
		}
	}

	//for operation = rm
	else if ((result_1 != (outparams *) NULL)&&(strcmp(operation, RM) == 0)) {
		if (result_1->errcode == 0) { 
			printf("File %s has been deleted\n", file_name);
		} else if (result_1->errcode == -2) {
			printf("File %s does not exist\n", file_name);
		} else {
			printf("Error in deleting %s\n", file_name);
		}
	}

	//for operation = ls
	else if ((result_1 != (outparams *) NULL)&&(strcmp(operation, LS) == 0)) {	
		while(result_1->outlst.name != NULL){
			printf("%s\n", result_1->outlst.name);
			if(result_1->outlst.next!=NULL)			
			result_1->outlst = *result_1->outlst.next;
			else result_1->outlst.name = NULL;
		}
		result_1->outlst.name = "uff";
	}

	//for operation = write
	else if ((result_1 != (outparams *) NULL)&&(strcmp(operation, WRITE) == 0)) {		
		if (result_1->outfsize < 0) {
                       	printf("Error in writing:\n");
               	} else {
			printf("%ld bytes of data were written to file %s\n", result_1->outfsize, file_name);
               	}
	}
	
	//for operation = exit
	else if ((result_1 != (outparams *) NULL)&&(strcmp(operation, "exit") == 0)) {
		printf("exiting...\n");
		//exit(0);
	}//printing logic ends

	// destroy client and exit
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */

exit (0);

}//main function ends
