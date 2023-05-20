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


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM         0
#define CMD_OR           1
#define CMD_AND          2
#define CMD_CHAIN        3


#define CONVERT_LOWERCASE        1
#define CONVERT_UNSIGNED         2


#define USE_GETLINE   0
#define USE_STRTOK    0

#define HIST_FILE     ".simple_shell_history"
#define HIST_MAX      4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a funtion,
 * 		allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was chaged
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @hiscount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a biultin string and ralated function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



int hsh(info_t *in, char **argv);
int find_builtin(info_t *in);
void find_cmd(info_t *in);
void fork_cmd(info_t *in);


int is_cmd(info_t *in, char *pa);
char *dup_chars(char *pastr, int stat, int stp);
char *find_path(info_t *in, char *pastr, char *cd);


int loophsh(char **);


/* toem_errors.c */
void _eputs(char *text);
int _eputchar(char);
int putfd(char c, int fd);
int putsfd(char *text, int fd);


int _strlen(char *m);
int _strcmp(char *m1, char *m2);
char *starts_with(const char *stack, const char *good);
char *_strcat(char *st, char *sr);


char *_strcpy(char *st, char *sr);
char *_strdup(const char *std);
void _puts(char *stp);
int _putchar(char a);


char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);


char **strtow(char *st, char *e);
char **strtow2(char *st, char e);


char *_memset(char *a, char z, unsigned int c);
void ffree(char **zz);
void *_realloc(void *pt, unsigned int old_size, unsigned int new_size);


int bfree(void **pt);


int main(int argc, char **argv);

int interactive(info_t *in);
int is_delim(char a, char *deli);
int _isalpha(int a);
int _atoi(char *b);


int _erratoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);


int _myexit(info_t *in);
int _mycd(info_t *in);
int _myhelp(info_t *in);


int _myhistory(info_t *info);
int _myalias(info_t *info);
int print_alias(list_t *node);
int set_alias(info_t *info, char *str);
int unset_alias(info_t *info, char *str);


ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);


void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
void free_list(list_t **);


char *_getenv(info_t *in, const char *use);
int _myenv(info_t *in);
int _mysetenv(info_t *in);
int _myunsetenv(info_t *in);
int populate_env_list(info_t *in);


char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);


char *get_history_file(info_t *in);
int write_history(info_t *in);
int read_history(info_t *in);
int build_history_list(info_t *in, char *bf, int linecount);
int renumber_history(info_t *in);


list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **ptr_head);


size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);


int is_chain(info_t *in, char *buff, size_t *z);
void check_chain(info_t *in, char *buff, size_t *z, size_t k, size_t nel);
int replace_alias(info_t *in);
int replace_vars(info_t *in);
int replace_string(char **oldr, char *newr);

int shell_env(info_t *shell_info);
char *shell_getenv(info_t *shell_info, const char *env_var_name);
int shell_setenv(info_t *shell_info);
int shell_unsetenv(info_t *shell_info);
int populate_env_list(info_t *shell_info);


ssize_t input_buf(info_t *in, char **bf, size_t *len);
ssize_t get_input(info_t *in);
ssize_t read_buf(info_t *in, char *bf, size_t *k);
int _getline(info_t *in, char **pr, size_t *lenth);
void sigintHandler(__attribute__((unused))int sig_num);


#endif
