/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:36:35 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/16 17:08:42 by cmorel           ###   ########.fr       */
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
# include "../includes/libft/libft.h"


// structs



// functions

void	pwd(void);

int		strings(char *input, char *command);

char	**get_paths(char *env);

char	*does_exist(char *cmd, char **paths);

void	clear(char **path);

int		quote_parsing(char *command);

int		is_operator(char str, int op);

int		reset(int *before, int *sign);

#endif
