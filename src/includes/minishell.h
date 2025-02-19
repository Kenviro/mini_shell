/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:19:20 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/19 15:53:54 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
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

// built_in.c
int		check_built_in(char **cmd);

// echo.c
void	echo(char **cmd);

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

//command.c && command2.c
void	cnf(char *cmd);
void	here_doc(char *limiter);
void	conditioning(t_list *lst, char **env);
char	*filename(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		command(char ***cmds, char **red, char **env);
int		find_nbargs(t_list *lst, int icmd);
int		red_out(char *red);
int		red_in(char *red);
char	**red_init(void);
char	**set_args(t_list *lst, int nbargs, int icmd);

#endif 