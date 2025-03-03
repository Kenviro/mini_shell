/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:19:20 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/03 16:07:44 by psoulie          ###   ########.fr       */
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
void	free_2d(char **str);

// built_in.c
int		check_built_in(char **cmd, char **env);
int		other_builtin(t_list *list, char ***env);

// echo.c
void	echo(char **cmd);

// pwd.c
void	pwd(void);

// cd.c
void	cd(char *path, char ***env);

// unset.c
void	unset(t_list *list, char ***env);

// env.c
void	env_builtin(char **cmd, char **env);

// export.c && print_export.c
void	print_export(char **env);
int		export(char **cmd, char **env);

// exit.c
void	exit_shell(t_list *list, char ***env);

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
void	free_stuff(t_cmds *cmds);
void	next_cmd(t_list **lst);
void	cnf(char *cmd);
void	conditioning(t_list *lst, char **env);
void	data_init(t_list *lst);
void	command(t_cmds *cmds, char **env);
void	close_fds(t_cmds *cmds);
void	pipex_child(t_cmds *cmds, int *end, char **env);
void	execute(char **cmd, char **env);
void	pipex_launcher(t_cmds *cmds, char **env);
void	wait_all(pid_t *to_wait, int nbcmds);
char	*filename(char *str);
char	**set_args(t_list *lst, int nbargs);
char	**find_args(t_list *lst);
char	**ft_strdup_2d(char **str);
char	***red_init(void);
int		here_doc(char *limiter);
int		ft_strcmp(const char *s1, const char *s2);
int		find_nbargs(t_list *lst);
int		red_out(char *red);
int		red_in(char *red);
int		count_cmds(t_list *lst);
int		find_nbcmds(t_cmds *cmds);
pid_t	pipex(t_cmds *cmds, char **env);

#endif