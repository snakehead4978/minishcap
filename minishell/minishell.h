/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:37:54 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/25 19:10:54 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define PIPE_SIZE 65336
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>


extern int g_bigsignal;

typedef enum e_lex
{
	LEX_START = 0,
	LEX_WORD = 1,
	LEX_REDIROUT = 2,
	LEX_REDIRIN = 3,
	LEX_AND = 4,
	LEX_PIPE = 5,
	LEX_OPEN = 6,
	LEX_CLOSE = 7,
	LEX_OR = 8,
	LEX_HERE = 9,
	LEX_APPEND = 10,
	LEX_END = 11
} t_lex;

typedef enum e_type
{
	SHELL,
	EXEC,
	REDIR,
	PIPE,
	SUB,
	AND,
	OR,
	HERE,
	EMPTY
} t_type;

typedef enum e_filedesc
{
	FD_FILEIN,
	FD_FILEOUT,
} t_filedesc;

// Structs

typedef struct s_cmd
{
	int type;
} t_cmd;

typedef struct s_sub
{
	int type;
	t_cmd *cmd;
} t_sub;

typedef struct s_herepipe
{
	char *str;
	int stored;
	int quote;
	struct s_herepipe *next;
} t_herepipe;

typedef struct s_shell
{
	int type;
	t_cmd *tree;
	char **env;
	t_herepipe *pipe;
} t_shell;

typedef struct s_execcmd
{
	int type;
	char **args;
} t_execcmd;

typedef struct s_pipecmd
{
	int type;
	t_cmd *left;
	t_cmd *right;
} t_pipecmd;

typedef struct s_redircmd
{
	int type;
	t_cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
	int quote;
	char *heredoc;
} t_redircmd;

typedef struct s_andcmd
{
	int type;
	t_cmd *left;
	t_cmd *right;
} t_andcmd;

typedef struct s_orcmd
{
	int type;
	t_cmd *left;
	t_cmd *right;
} t_orcmd;

typedef struct s_doublecmd
{
	int type;
	t_cmd *left;
	t_cmd *right;
} t_doublecmd;

typedef struct s_lexer
{
	int type;
	char *heredoc;
	struct s_lexer *next;
	struct s_lexer *prev;
} t_lexer;

typedef struct s_subquote
{
	char *str;
	int check;
} t_subquote;

typedef struct s_list
{
	void *data;
	struct s_list *next;
} t_list;

typedef struct s_file
{
	char *filename;
	char *search;
} t_file;

typedef struct s_fds
{
	int fd;
	int type;
} t_fds;

typedef struct s_execs
{
	t_list *fds;
	t_shell *shell;
	int ret;
	t_cmd *cmd;
	int stdcopies[2];
	char	*buff;
} t_execs;

//	Lib and Useful Funcs
char *ft_substr(char const *s, unsigned int start,
				size_t len);
int nodeadder(t_list **lst, char *str1, char **str2,
			  int check);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strtrim(char *s1, char const *set);
int iswhite(char c);
char *ft_strcatter(char *str1, char *str2);
char *ft_strdup(char *str);
char *ft_strstr(char *haystack, char *needle);
char *ft_itoa(int num);
int arrayfree(char ***array);
char **ft_pathsplit(char const *s, char c, char *bonus);
char *ft_itoul(unsigned long num);
int ft_strncmp(const char *s1, const char *s2, size_t n);
void *ft_memset(void *s, int c, size_t n);
int ft_strcmp(const char *s1, const char *s2);
void *ft_calloc(size_t nmemb, size_t size);
char *ft_strchr(char *s, char c);
char *ft_strchr2(char *s, char c);
// void					ft_bzero(void *s, size_t n);
int ft_strlen(const char *s);
char **ft_split(char const *str, char c);
void *ft_calloc(size_t nmemb, size_t size);
int lfsymbol(char **ptr, char *c);
int	lfsymbol2(char **ptr, char *c);
char *ft_filecpy(char *file, char *efile);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
char *ft_strcat(char *str1, char *str2);
int ft_isalpha(int c);
char *get_env(char *name, char **env);
int	ft_write(int fd, char *str, int size);

// Moded LIBFT
char **args_malloc(int argc, char *ptr_arg, char *ptr_earg,
				   char **args);
char *empty_string(void);
void ft_strcpy_quoteless(char **dest, char *src);
int ft_strcmp2(const char *s1, const char *s2);
int size_pwd(char **env);
void print_env(char **env);

//  List Funcs
t_list *listnew(void *data, void (*f)());
t_list *listaddback(t_list **lst, t_list *new, void (*f)());
int ft_listfree(t_list **lst, void (*f)());
int listsize(t_list *list);
t_lexer *ft_lstlast(t_lexer *lst);
void ft_lstadd_back(t_lexer **lst, t_lexer **new);

//	Struct Funcs
t_subquote *subquotenew(char *data, int check);
void subquotefree(t_subquote *data);
t_file *filenew(char *data);
void filefree(t_file *data);
t_fds *fdsnew(int fd, int type);
void fdsfree(t_fds *fds);
int execfree(t_execs *exec);
void free_array(char **s);
void free_args(t_execcmd *ex);
void free_exec(t_execcmd *ex);
void free_sub(t_sub *sub);
void free_redir(t_redircmd *re);
void free_double(t_doublecmd *db);
void tree_free(t_cmd **tree);
void free_herepipe(t_shell **shell);
t_cmd *redircmd_out(t_cmd *cmd, char *file, char *efile,
					int fd);
t_cmd *redircmd_in(t_cmd *cmd, char *file, char *efile,
				   int fd);
t_cmd *redircmd_append(t_cmd *cmd, char *file, char *efile,
					   int fd);
t_cmd *redircmd_in2(t_cmd *cmd, char *file, char *efile,
					int fd);
t_cmd *redircmd_out2(t_cmd *cmd, char *file, char *efile,
					 int fd);
t_cmd *redircmd_append2(t_cmd *cmd, char *file, char *efile,
						int fd);
t_cmd *redircmd_here(t_herepipe **pipe, t_cmd *cmd);
t_cmd *redircmd_here2(t_herepipe **pipe, t_cmd *cmd);
t_cmd *execcmd(void);
t_cmd *pipecmd(t_cmd *left, t_cmd *right);
t_cmd *andcmd(t_cmd *left, t_cmd *right);
t_cmd *orcmd(t_cmd *left, t_cmd *right);
void ft_removefd(t_list *fds);
int	exit_execfree(t_execs *exec, int err);

//	Expansion
t_list *expansion(char *str);

// 	Substitution
char *dollar(char *str, int final, t_execs *exec);
char *dollarquote(char *str, t_execs *exec);

// Wildcard and Dequote
t_list *resplitter(t_list *lst);
t_list *star(t_list *lst);

//  File Funcs
t_list *filer(int check);
void filecheck(t_list *files, t_list *node, int mode);
t_list *filelist(t_list *files, t_list *list);

//  Printer Funcs
void subquoteprint(t_subquote *data);
void strprint(char *data);
void fileprint(t_file *data);
void printlist(t_list *list, void (*print)());
void intprint(int *data);
void print_indent(int indent);
void print_redircmd(t_redircmd *redir, int indent);
void print_execcmd(t_execcmd *exec, int indent);
void print_pipecmd(t_pipecmd *pipe, int indent);
void print_andcmd(t_andcmd *and, int indent);
void print_orcmd(t_orcmd * or, int indent);
void print_doublecmd(t_doublecmd *dbl, int indent);
void print_subcmd(t_sub *sub, int indent);
void print_cmd(t_cmd *cmd, int indent);
void ft_printerror(char *str, char *name, char *str2);

// Signal Funcs
void signals(void);
void signals_heredoc(void);

// Argument Func
char **args(char **arguments, t_execs *exec);
int ft_expandcmd(t_execs *exec, t_cmd *cmd);
char	*argument_heredoc(char *arg);

// fds
int	ft_setfds(t_execs *exec);
int	ft_closeallfds(t_execs *exec);

// Command and Path
char **ft_pathsplit(char const *s, char c, char *bonus);
int ft_command(t_execs *exec, t_execcmd *cmd);

// Exec Main Func
int executer(t_shell *shell, int err, char *buff);

// Exec Funcs
int ft_sorter(t_execs *exec, t_cmd *cmd);
int ft_pipe(t_execs *exec);
int ft_redir(t_execs *exec);
int ft_and(t_execs *exec);
int ft_or(t_execs *exec);
int ft_sub(t_execs *exec);
int ft_exec(t_execs *exec);
int ft_here(t_execs *exec);

// Parsing

void parseredirs_primo(t_herepipe **pipes, t_cmd **cmd,
					   char **ps, int *check);
t_cmd *parseredirs_er(t_herepipe **pipes, t_cmd *cmd,
					  char **ps);
int gettoken(char **ptr, char **ptr_token,
			 char **ptr_endtoken);
t_cmd *parseexec(t_shell *shell, char **ps, int check,
				 int argc);
t_cmd *parse_double_node(t_shell *shell, char **ptr);
t_cmd *parse_and(t_shell *shell, char **ptr);
t_cmd *parse_or(t_shell *shell, char **ptr);
t_cmd *parseline(t_shell *shell, char **ptr);
int	parsecmd(t_shell **shell, char *str, int err);
int quote_check(char *str);
void saver(int in);
void saver2(int *in, char **buf);

// Lexer
int	add_lex_node(t_lexer **lex, char *str, int *i);
int lexer(t_shell **shell, char *str);
int sub_lexer(t_lexer **lex, char *str, int *i);
int prev_check(t_lexer *lex, char *str);
int next_check(t_lexer *lex, char *str);
int first_type_check(t_lexer *lex);
char *heredoc_filler(char *end);
int init_heredoc(t_lexer *lex, t_shell **shell);
int lexing_check(t_shell **shell, t_lexer *lexer);
void free_lexer(t_lexer *lexer);
int	and_return(t_lexer **new, char *str, int *i);

int add_quote_node(t_lexer **lex, char *str, int *i,
				   char c);
void skip_quotes(char *str, int *i, int *size);
void ft_pipeaddback(t_shell **shell, t_herepipe *new);

// Printer

void printer(t_cmd *cmd, int s, int level);
void print_indent(int indent);
void print_redircmd(t_redircmd *redir, int indent);
void print_execcmd(t_execcmd *exec, int indent);
void print_pipecmd(t_pipecmd *pipe, int indent);
void print_andcmd(t_andcmd *and, int indent);
void print_doublecmd(t_doublecmd *dbl, int indent);
void print_orcmd(t_orcmd * or, int indent);
void print_subcmd(t_sub *sub, int indent);
void print_cmd(t_cmd *cmd, int indent);

// Built-in

int	isbuiltin(char *cmd);
int	builtin(t_execs *exec);
int ft_cd(t_execs *execs);
int ft_echo(t_execs *execs);
int ft_env(t_execs *execs);
int ft_exit(t_execs *ex);
int ft_export(t_execs *execs);
int ft_pwd(t_execs *execs);
int ft_unset(t_execs *execs);
char	**new_env(char ***env, char *cmd);
char	*minisplit(char *s, int c);
char	**new_env(char ***env, char *cmd);
char	*get_env_mine(char *name, char **env);
void	ft_getcwd(char **pwd);
int	move_back(char **env);
int	ft_move(char **cmd, char **env);
char	*ft_strjoin_free(char *s1, char const *s2);
#endif