/*
* hw2.x
*
*/

const MAXCOMMANDLEN = 10; /* maximum length of command is 9 */
const MAXFILENAME = 20;   /* maximum length of file name is 19 */
const MAXSTRLEN = 1000;

const CAT = "cat";
const RM = "rm";
const LS = "ls";
const FIND = "find";
const WRITE = "write";

/*linked list to be returned by ls command*/
typedef struct file *filelist; /* link in the listing */
struct file {
   	string name<MAXFILENAME>; /* name of file in directory */
   	filelist next; /* next file if exists */
};

struct inparams {
	string cmd<MAXCOMMANDLEN>;
	string infile<MAXFILENAME>;
	int len;
	string str<MAXSTRLEN>;
};

struct outparams {
	long outfsize;
	string outdata<MAXSTRLEN>;
	struct file outlst;
	int errcode;
};

/* The directory program definition */

program HWPROG {
   version HWVERS {
    outparams FILEPROG(inparams) = 1;
   } = 1;
} = 0x25510961;
