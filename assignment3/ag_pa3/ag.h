#include <ctype.h>
// change lines 6-19 to update the following:
//  1. program name (mentioned in the Makefile),
//  2. # of test-cases
//  3. stdin of each test-case
//  4. and command-line arguments of each test-case
static char DEFAULT_PROGRAM_NAME[] = "convert";
#define NUM_TEST_CASES 6
static char *TESTCASES[] = {
	"12\t-12.3\tHello World!\n   Sentence  \n23.\t-23" // TC#1
	,
	"12\t-12.3\tHello World!\n  Sentence  \n23.\t-23" // TC#2
	,
	"12,-12.3,Hello World!\nSentence  \n23.,-23" // TC#3
	,
	"12\t   -12.3  \tHello World!\n  Sentence  \n23.\t-23" // TC#4
	,
	"1234v5\t12e3\t-12.34\n86r543\tr12345\n.1e7\t-123" // TC#5
	,
	"\t1\t\t2\t    3.123e3 \t\t\n12\thello\t\t  123g  \t\t" // TC#6: 15% extra credit
};
static const char **TEST_ARGS[] = {
	"",									 // TC#1
	"-exs", "",							 // TC#2
	"-i", "csv", "-o", "txt", "",		 // TC#3
	"-i", "txt", "-o", "csv", "-cs", "", // TC#4
	"-es", "-x", "",					 // TC#5
	"-xcse", "",						 // TC#6
};
// ------------------------------NO Change After this line ------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/wait.h>
#include <dirent.h>
#define MAX_STUDENTS 150
#define MAX_INPUT_SIZE 2000
#define MAX_PROGRAM_NAME_LEN 100
#define MAX_BUF 200
#define die(e)                      \
	do                              \
	{                               \
		fprintf(stderr, "%s\n", e); \
		exit(EXIT_FAILURE);         \
	} while (0);
typedef enum
{
	LIST_FILES,
	UNZIP,
	CLEAN,
	MOSS,
	MAKE,
	RUN
} phase;
static char *CLA_ERROR_MESSAGE = "Fatal error. proper usage: ag [-xu] [-xm] [-xs] [-xc] [-s nn mm... or -s nn-mm] where nn, mm, etc are the submissions that you do not want to test";
char **submissions;
char **submissions_zipped;
int sub_count;
int test_case = 0;
static char *PROGRAM_NAME;
void update_name(char *dir);
void compile_h_c_files(char *dir_path);
int DONT_GRADE[MAX_STUDENTS];
char **get_args(char *file_name, int test_case);
char *str_args(char *file_name, int test_case);