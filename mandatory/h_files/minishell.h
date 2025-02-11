
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
# include "../includes/libft/libft.h"


// structs

typedef	struct s_duet
{
	int	single_quote;
	int	double_quote;
}	t_duet;

typedef	struct s_iterate
{
	int	i;
	int	j;
}	t_iterate;

typedef struct s_env {
	char			*name;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_texts
{
	char	*line;
	char	*final;
	char	**env;
}	t_texts;
// functions

void	pwd(void);

int		strings(char *input, char *command);

char	**get_paths(char *env);

char	*does_exist(char *cmd, char **paths);

void	clear(char **path);

int		quote_parsing(char *command);

int		is_operator(char ch, char c);

t_list	*check_until(char *line, int *j, char ch);

t_list	*ft_split_skip_quotes(char *line, char ch);

t_list	*find_operator(int *i, char *line, char ch);

int		quote_parsing(char *command);

int		len_quotes(t_duet duet, char *line);

void	remove_quote(char *line, t_list *cmds);

t_list	*get_correct_commands(t_list *cmds, char **env);

t_list	*get_commands(char *line, char **env);

int		cpy_without_quote(char *final, char *original);

char	*ft_charjoin(char *str, char ch);

void	skip_spaces(char *line, int *i);

int		split_len(char **spl);

char	**split_realloc(char **old, char **cpy, int	*index);

void	modify_flags(t_list **cmds);

void	print_split(char **split);

void	cpy_text(char *to_cpy, char *final, t_iterate *iter);

void	fill_word(t_iterate *iter, char *final, char *word, char **env);

int		replace_dollars(char **env, char *line, char *final);

int		parse_quotes(char *line);

void	fill_word_quote(t_iterate *iter, char *final, char *word, char **env);

char	reverse_quote(char quote);

void	cpy_text_add_quote(char *to_cpy, char *final, t_iterate *iter);

void	cpy_text_add_quote(char *to_cpy, char *final, t_iterate *iter);

char	*expand(char *line, char **env);

char	**split_flags(char **flags);

void	file_flags(t_list **cmds);

#endif
