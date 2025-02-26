#ifndef MINISHELL_H
# define MINISHELL_H

// include
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include "../includes/libft/libft.h"
# include "../includes/libft/get_next_line_bonus.h"

// global

extern int g_signal_c;

// define
# define PROMPT "\e[0;36m└─(\e[1;32mSegfault\e[0;36m)──\e[1;36m> \033[0m"
# define HEREDOC 4
# define HERE 6
# define FILE 3
# define REDIRECT 5
# define COMMAND 1
# define PIPE 2
# define RESET   "\001\033[0m\002"
# define BOLD    "\001\033[1m\002"
# define RED     "\001\033[31m\002"
# define GREEN   "\001\033[32m\002"
# define YELLOW  "\001\033[33m\002"
# define BLUE    "\001\033[34m\002"
# define MAGENTA "\001\033[35m\002"
# define CYAN    "\001\033[36m\002"

// structs
typedef struct s_duet
{
	int	single_quote;
	int	double_quote;
}	t_duet;

typedef struct s_iterate
{
	int	i;
	int	j;
}	t_iterate;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_texts
{
	char	*line;
	char	*final;
	t_env	*env;
}	t_texts;

// functions

typedef int	(*t_builtin)(t_list *, t_env **);

int		strings(char *input, char *command);

char	**get_paths(char *env);

char	*does_exist(char *cmd, char **paths);

char	**get_envp(t_env **env);

char	*find_env(char *name, t_env **env);

void	init(t_list **lst, t_env **env);

t_builtin	get_builtin(t_list *lst);

int		*get_pid_list(t_list *lst);

void	wait_all(int *pids, char *line, t_env **env);

int		open_file(t_list *node, int *infile, int *outfile, int *next);

void	close_node(t_list *lst);

void	add_pid_back(int *fds, int fd);

int		exec_builtin(t_list *c, int (*exe)
			(t_list *l, t_env **e), int n, t_env **e);

int		is_pipe(t_list *cmd);

int		echo(t_list *lst, t_env **env);

int		cd(t_list *lst, t_env **env);

int		aff_env(t_list *lst, t_env **env);

int		export(t_list *lst, t_env **env);

int		unset(t_list *lst, t_env **env);

int		pwd(t_list *lst, t_env **env);

void	close_node(t_list *lst);

void	init_node(t_list *lst, t_env **env);

void	*destroy_node(t_env *node);

void	*destroy(t_env *env);

void	add_back(t_env **env, t_env *node, int append_mode);

t_env	*sort_env(t_env **env);

int		quote_parsing(char *command);

int		is_operator(char ch, char c);

t_list	*check_until(char *line, int *j, char ch, char op);

t_list	*ft_split_skip_quotes(char *line, char ch);

t_list	*find_operator(int *i, char *line, char ch);

int		quote_parsing(char *command);

int		len_quotes(t_duet duet, char *line);

void	remove_quote(char *line, t_list *cmds);

t_list	*get_correct_commands(t_list *cmds, t_env *env);

t_list	*get_commands(char *line, t_env *env);

int		cpy_without_quote(char *final, char *original);

char	*ft_charjoin(char *str, char ch);

void	skip_spaces(char *line, int *i);

int		split_len(char **spl);

char	**split_realloc(char **old, char **cpy, int	*index);

void	modify_flags(t_list **cmds);

void	print_split(char **split);

void	cpy_text(char *to_cpy, char *final, t_iterate *iter);

void	fill_word(t_iterate *iter, char *final, char *word, t_env *env);

int		replace_dollars(t_env *env, char *line, char *final);

int		parse_quote(char *line);

void	fill_word_quote(t_iterate *iter, char *final, char *word, t_env *env);

char	reverse_quote(char quote);

void	cpy_text_add_quote(char *to_cpy, char *final, t_iterate *iter);

char	*expand(char *line, t_env *env, t_list **cmd);

char	**split_flags(char **flags);

void	file_flags(t_list **cmds);

int		exit_builtin(t_list *cmd, t_env **env);

void	update_code(int code, t_env	**env);

char	**ft_realloc(char **split, char *to_add);

void	inthandler(int sig);

char	**heredoc(char *final, int len);

char	*check_dollars(char *line, t_iterate *iter);

void	heredoc_expand(char **flags, t_env *env);

void	make_heredoc(t_list **cmds, t_env *env);

void	error_handler(int code, int sub, char *command);

t_list	*get_next(t_list *cmds);

char	*get_prompt(t_env **env);

int		run(t_list **lst, t_env **env, int **pids);

t_env	*get_env(char **envp);

void	handle_sigint(int sig);

int		exit_code(int code, t_env **env, int sub, t_list *cmd);

int		handle_ambigous(t_env *env, t_list **cmds);

#endif
