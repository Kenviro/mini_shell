/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:19:20 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/24 10:16:27 by ktintim-         ###   ########.fr       */
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

typedef struct s_cmds
{
	char			**cmd;
	int				fds[2];
	char			*limiter;
	struct s_cmds	*next;
}				t_cmds;

// minishell.c

// error.c
void	error(char *message);
void	new_line(char *input);

// built_in.c
int		check_built_in(char **cmd, char **env);

// echo.c
void	echo(char **cmd);

// pwd.c
void	pwd(void);

// cd.c
void	cd(char *path);

// unset.c
void	unset(char **cmd, char **env);

// env.c
void	env_builtin(char **cmd, char **env);

// export.c
void	export(char **cmd, char **env);

// exit.c
void	exit_shell(t_list *list);

// signal/setup_signal.c
void	handle_signal(int signal);
void	setup_signal_handler(void);

// signal/signal_child.c
void	handle_signal_child(int signal);
void	signal_handler_child(void);

//holy_split.c && splitonsteroids.c
int		quote(char c, int *in_quote);
int		ft_splitonsteroids(char *str, int start, char c);
void	toggle_quote(int *in_quote);
char	**holy_split(char *str, char c);

// split_redirect.c
int		found_redirection(char *str, t_list **list);

// check_input.c
char	*found_dollar(char *input);

//command.c && command2.c
void	cnf(char *cmd);
void	conditioning(t_list *lst, char **env);
void	data_init(t_list *lst);
void	command(t_cmds *cmds, char **env);
char	*filename(char *str);
char	**set_args(t_list *lst, int nbargs);
char	**find_args(t_list *lst);
char	***red_init(void);
int		here_doc(char *limiter);
int		ft_strcmp(const char *s1, const char *s2);
int		find_nbargs(t_list *lst);
int		red_out(char *red);
int		red_in(char *red);
int		count_cmds(t_list *lst);
int		find_nbcmds(t_cmds *cmds);

#endif 