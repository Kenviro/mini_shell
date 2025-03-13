/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:19:20 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/13 16:55:42 by ktintim-         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

// minishell.c

// error.c && symt_error.c
void	error(char *message);
void	new_line(char *input);
void	free_2d(char ***str);
void	ft_envclear(t_env **l_env);
int		quote_cnf(char ***splited, int *ms_status);
int		check_synt_error(t_list *list, int *ms_status);
char	*split_redirection(char *input);
char	*get_pwd(void);

// built_in.c
int		check_built_in(char **cmd, char **env);
int		other_builtin(t_list *list, char ***env, int *ms_status);

// echo.c
void	echo(char **cmd);

// pwd.c
void	pwd(void);

// cd.c
void	cd(char *path, char ***env, int *ms_status);

// unset.c
void	unset(t_list *list, char ***env);

// env.c
void	env_builtin(char **cmd, char **env);

// export.c && print_export.c && export_utils.c
void	print_export(char **env);
int		export(t_list *list, char ***env);
char	*get_key(char *str);
char	*get_value(char *str);

// exit.c
void	exit_shell(t_list *list, char ***env);

// signal/setup_signal.c
void	handle_signal(int signal);
void	setup_signal_handler(void);

// signal/signal_child.c
void	handle_signal_child(int signal);
void	signal_handler_child(void);

//holy_split.c && splitonsteroids.c
int		quote(char c, int (*in_quote)[2]);
int		ft_splitonsteroids(char *str, int start, char c);
int		toggle_quote(int (*in_quote)[2], char quote);
char	**holy_split(char *str, char c);

// split_redirect.c
int		found_redirection(char *str, t_list **list);

// check_input.c && expension
char	*found_dollar(char *input, char **env, int ms_status);
char	*expension(char *input, char **env, int ms_status, int i);

//command.c && command2.c && command3.c
void	free_stuff(t_cmds *cmds);
void	next_cmd(t_list **lst);
void	cnf(t_cmds *cmds);
void	conditioning(t_list *lst, char **env, int *ms_status);
void	data_init(t_list *lst);
void	command(t_cmds *cmds, char **env, int *ms_status);
void	close_fds(t_cmds *cmds);
void	pipex_child(t_cmds *cmds, int *end, char **env);
void	execute(char **cmd, char **env);
void	pipex_launcher(t_cmds *cmds, char **env, int *ms_status);
void	wait_all(pid_t *to_wait, int nbcmds, int *ms_status);
char	*filename(char *str);
char	**set_args(t_list *lst, int nbargs);
char	**find_args(t_list *lst);
char	**ft_strdup_2d(char **str);
char	***red_init(void);
int		here_doc(char *limiter, char **env, int ms_status);
int		ft_strcmp(const char *s1, const char *s2);
int		find_nbargs(t_list *lst);
int		red_out(char *red);
int		red_in(char *red);
int		count_cmds(t_list *lst);
int		find_nbcmds(t_cmds *cmds);
pid_t	pipex(t_cmds *cmds, char **env);

#endif