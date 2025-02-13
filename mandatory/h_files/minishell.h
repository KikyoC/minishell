/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:36:35 by cmorel            #+#    #+#             */
/*   Updated: 2025/02/13 15:16:04 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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


// structs

typedef struct s_env {
	char			*name;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// functions

int		strings(char *input, char *command);

char	**get_paths(char *env);

char	*does_exist(char *cmd, char **paths);

char	**get_envp(t_env **env);

char	*find_env(char *name, t_env **env);

void	init(t_list **lst, t_env **env);

int (*get_builtin(t_list	*lst))(t_list *lst, t_env **env);

int		*get_pid_list(t_list *lst);

int		wait_all(int *pids);

int		open_file(t_list *node, int *infile, int *outfile, int *next);

void	close_node(t_list *lst);

void	add_pid_back(int *fds, int fd);

int	exec_builtin(t_list *c, int (*exe)(t_list *l, t_env **e), int n, t_env **e);

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


#endif
