/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:19:20 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/04 14:19:42 by ktintim-         ###   ########.fr       */
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
void	exit_shell(char **splited);

// parse.c
void	parse(t_list *list);

// semi_parse.c
int		semi_parse(char **splited);
void	new_line(char *input);

// signal/setup_signal.c
void	handle_signal(int signal);
void	setup_signal_handler(void);

//holy_split.c && splitonsteroids.c
int		quote(char c, int *in_quote);
int		ft_splitonsteroids(char *str, int start, char c);
void	toggle_quote(int *in_quote);
char	**holy_split(char *str, char c);

#endif 