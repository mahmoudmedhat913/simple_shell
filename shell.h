#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define buffer_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0
#define HISTORY ".simple_shell_history"
#define MAXHISTORY 4096

#define info_init {NULL, NULL, NULL, 0, 0, 0, 0, \
	NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

extern char **environ;

/**
 * struct liststr - list
 * @num: no. field
 * @str: string
 * @next: point to next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - structure
 * @arg: string
 * @argv: array
 * @path: string path
 * @argc: argument counter
 * @linecount: error counter
 * @errornum: error code for exit
 * @linecountflag: flag
 * @filename: program file name
 * @env: copy of environ
 * @environ: custom modified copy of environ
 * @history: old node
 * @alias: alias node
 * @changedenv: flag
 * @status: return status of last executable command
 * @cmdbuffer: address of pointer to cmdbuffer
 * @cmdbuffertype: types of cmd
 * @fdread: read line input in fd
 * @historycount: history line no. count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int linecount;
	int errornum;
	int linecountflag;
	char *filename;
	list_t *env;
	char **environ;
	list_t *history;
	list_t *alias;
	int changedenv;
	int status;
	char **cmdbuffer;
	int cmdbuffertype;
	int fdread;
	int historycount;
} info_t;

/**
 * struct builtin - contain builtin string and related function
 * @builtintype: builtin
 * @func: function
 */

typedef struct builtin
{
	char *builtintype;
	int (*func)(info_t *);
} builtin_group;

int hsh(info_t *, char **);
int searchbuiltin(info_t *);
void searchcmd(info_t *);
void forkcmd(info_t *);

int iscmd(info_t *, char *);
char *dupchar(char *, int, int);
char *searchpath(info_t *, char *, char *);
int hshloop(char **);
void _errorputs(char *);
int _errorputchar(char);
int _fdput(char c, int fd);
int _fdputs(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *startwith(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_stringcpy(char *, char *, int);
char *_stringcat(char *, char *, int);
char *_stringchr(char *, char);
char **strtow(char *, char *);
char **strtow_2(char *, char);

char *__memset(char *, char, unsigned int);
void ffree(char **);
void *__realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int active(info_t *);
int isdelim(char, char *);
int isalpha(int);
int _atoi(char *);

int erroratoi(char *);
void printerror(info_t *, char *);
int printd(int, int);
char *convertnum(long int, int, int);
void removecomment(char *);

int __exit(info_t *);
int __cd(info_t *);
int __help(info_t *);
int __history(info_t *);
int __alias(info_t *);

ssize_t __getinput(info_t *);
int _get_line(info_t *, char **, size_t *);
void handler(int);
void clearinfo(info_t *);
void setinfo(info_t *, char **);
void freeinfo(info_t *, int);

char *_getenv(info_t *, const char *);
int env(info_t *);
int _set_env(info_t *);
int _unset_env(info_t *);
int populateenv(info_t *);
char **getenviron(info_t *);
int setenviron(info_t *, char *, char *);
int unsetenviron(info_t *, char *);

char *gethistoryfile(info_t *info);
int writeinhistory(info_t *info);
int readfromhistory(info_t *info);
int buildhistory(info_t *info, char *buffer, int count);
int renumhistory(info_t *info);

list_t *addnode(list_t **, const char *, int);
list_t *addendnode(list_t **, const char *, int);
size_t printstringlist(const list_t *);
int deletenode(list_t **, unsigned int);
void freelist(list_t **);

size_t listlength(const list_t *);
char **listtostring(list_t *);
size_t printlist(const list_t *);
list_t *nodestart(list_t *, char *, char);
ssize_t nodeindex(list_t *, list_t *);
int ischain(info_t *, char *, size_t *);
void checkchain(info_t *, char *, size_t *, size_t, size_t);
int changealias(info_t *);
int changevars(info_t *);
int changestring(char **, char *);

#endif
