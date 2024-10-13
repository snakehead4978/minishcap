/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:37:54 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/13 15:41:32 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE_SIZE 65336
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define MAXLINE 1500001

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
	LEX_APPEND = 10
}						t_lex;

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
}						t_type;

typedef enum e_filedesc
{
	FD_FILEIN,
	FD_FILEOUT,
}						t_filedesc;

// Structs

typedef struct s_cmd
{
    int type;
}   t_cmd;

typedef struct s_env
{
    char **env;
}   t_env;

typedef struct s_sub
{
    int type;
    t_cmd *cmd;
}   t_sub;

typedef struct s_var
{
    char *alias;
    char *value;
    struct s_var *next;
}   t_var;

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
    t_var *var;
    t_env *env;
    t_herepipe *pipe;
}   t_shell;

typedef struct s_execcmd
{
    int type;
    char **args;
}   t_execcmd;

typedef struct s_pipecmd
{
    int type;
    t_cmd *left;
    t_cmd *right;
}   t_pipecmd;

typedef struct s_redircmd
{
    int type;
    t_cmd *cmd;
    char *file;
    char *efile;
    int mode;
    int fd;
    char *heredoc;
}   t_redircmd;



typedef struct s_andcmd
{
    int type;
    t_cmd *left;
    t_cmd *right;
}   t_andcmd;

typedef struct s_orcmd
{
    int type;
    t_cmd *left;
    t_cmd *right;
}   t_orcmd;

typedef struct s_doublecmd
{
    int type;
    t_cmd *left;
    t_cmd *right;
}   t_doublecmd;

typedef struct s_lexer
{
    int type;
    char *heredoc;
    struct s_lexer *next;
    struct s_lexer *prev;
}   t_lexer;

typedef struct s_subquote
{
	char				*str;
	int					check;
}						t_subquote;

typedef struct s_list
{
	void				*data;
	struct s_list		*next;
}						t_list;

typedef struct s_file
{
	char				*filename;
	char				*search;
}						t_file;

typedef struct s_fds
{
	int					fd;
	int					type;
}						t_fds;

typedef struct s_execs
{
	t_fds				*fds;
	t_shell				*shell;
	int					ret;
	t_cmd				*cmd;
}						t_execs;

//	Lib and Useful Funcs
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
int						nodeadder(t_list **lst, char *str1, char **str2,
							int check);
char					*ft_strtrim(char *s1, char const *set);
int						iswhite(char c);
char					*ft_strcatter(char *str1, char *str2);
char					*ft_strdup(char *str);
char					*ft_strstr(char *haystack, char *needle);
char					*ft_itoa(int num);
int						arrayfree(char **array);
char					**ft_pathsplit(char const *s, char c, char *bonus);
char	*ft_itoul(unsigned long num);


//  List Funcs
t_list					*listnew(void *data, void (*f)());
t_list					*listaddback(t_list **lst, t_list *new, void (*f)());
int						ft_listfree(t_list **lst, void (*f)());
int						listsize(t_list *list);

//	Struct Funcs
t_subquote				*subquotenew(char *data, int check);
void					subquotefree(t_subquote *data);
t_file					*filenew(char *data);
void					filefree(t_file *data);
t_fds					*fdsnew(int fd, int type);
void					fdsfree(t_fds *fds);
int						execfree(t_execs *exec);

//	Expansion
t_list					*expansion(char *str);

// 	Substitution
char					*dollar(char *str, int final, t_execs *exec);
char					*dollarquote(char *str, t_execs *exec);

// Wildcard and Dequote
t_list					*resplitter(t_list *lst);
t_list					*star(t_list *lst);

//  File Funcs
t_list					*filer(int check);
void					filecheck(t_list *files, t_list *node, int mode);
t_list					*filelist(t_list *files, t_list *list);

//  Printer Funcs
void					subquoteprint(t_subquote *data);
void					strprint(char *data);
void					fileprint(t_file *data);
void					printlist(t_list *list, void (*print)());
void					intprint(int *data);

// Argument Func
char					**args(char **arguments, t_execs *exec);
int						ft_expandcmd(t_execs *exec, t_cmd *cmd);

// Command
int						ft_command(t_execs *exec, t_execcmd *cmd);

#endif