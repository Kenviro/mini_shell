/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:19:20 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/12 10:30:35 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../Libft/libft.h"
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# define _GNU_SOURCE
# include <signal.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>

// minishell.c

// error.c
void	error(char *message);
void	new_line(char *input);

// parse.c
void	parse(t_list *list);

// semi_parse.c
int		semi_parse(char **splited);

// built_in.c
int		check_built_in(t_list *list);

// echo.c
void	echo(t_list *list);

// pwd.c
void	pwd(void);

// cd.c
void	cd(char *path);

// exit.c
void	exit_shell(t_list *list);

// signal/setup_signal.c
void	handle_signal(int signal);
void	setup_signal_handler(void);

//holy_split.c && splitonsteroids.c
int		quote(char c, int *in_quote);
int		ft_splitonsteroids(char *str, int start, char c);
void	toggle_quote(int *in_quote);
char	**holy_split(char *str, char c);

// split_redirect.c
int		found_redirection(char *str, t_list **list);

#endif 