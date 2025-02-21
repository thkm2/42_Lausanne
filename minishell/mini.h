/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:39:23 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/18 16:13:29 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

// libft
# include "libft/libft.h"

// gnl

# include "gnl/get_next_line.h"

// libc
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <fcntl.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

// processus
# include <sys/wait.h>

// signals
# include <signal.h>

typedef struct s_cmd
{
	int				id;
	int				input;
	int				output;
	char			**tab;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				export;
	struct s_env	*next;
}	t_env;

// externs
void	child_process_for_externs(t_cmd *node, char **envp,
			t_env *env, t_cmd *head);
void	ft_free_split(char **tab);

// EXECUTION

int		redirect_operator(t_cmd *node, char **envp, t_env *env, t_cmd *head);
void	create_pipes(t_cmd *head);
void	close_fd(t_cmd *head);
void	close_fd_except(t_cmd *head, t_cmd *node);
pid_t	fgv_last_pid(pid_t new);

// PARSING

int		parse_input(char *line, t_cmd **groups, t_env *env);
char	*clean_quotes(char *s, int *is_changed);
char	*clean_useless_quotes(char *s);
char	*remove_chars(char *s, char *chars);
char	*expand_vars(char *s, t_env *env, int is_heredoc);
char	*insert_spaces(char *s);

int		handle_pipe(t_cmd **tail);
int		handle_redirection_input(t_cmd **tail, t_cmd **next, t_cmd **last);
int		handle_heredoc(t_cmd **tail, t_env *env, t_cmd **head, t_cmd **next);
int		handle_redirection_output(t_cmd **tail, t_cmd **next);

// HEREDOC
char	**heredoc(char *del, t_env *env, int *sigint_received);
int		red_input_del(char **av);

char	*rem_char(char *s, int t);
char	*remove_useless_quotes(char *s);
char	*remove_lone_quotes(char *s);
char	*remove_lone_quote_specify(char *s, char c, int *is_changed);
char	*clean_input(char *s);
int		end_of_token(char *s, int is_quoted_heredoc);
char	*token_dup(char *s, int is_quoted_heredoc);
char	*quoted_token_dup(char *s);
char	**split_tokens(char *s);
int		count_tokens(char *s);
void	append_node(t_cmd **head, char **tab);
void	a_n_b(t_cmd **tail, char **tab, t_cmd **head);
char	**sub_tab(char **tab, int from, int to);
int		group_tokens(t_cmd **head, char **tab);
t_cmd	*get_input_output(t_cmd **head, t_env *env);
char	*extract_var(char *s, int i);
char	*get_var_value(char *s, t_env *env);
char	*replace_by(char *s, char *value, int index, int length);
int		group_tokens_loop(char **tab, t_cmd **head, int *i, int *group_start);

// PARSING_UTILS

int		which_cmd(char *cmd);
int		is_special(char c);
int		is_separator(char *s);
int		next_separator(char **tab, int i);
int		isquote(char c);
int		get_last_char(char *s, char c);
int		next_char(char *s, char c);
int		count_chars(char *s, char c);
void	print_tab(char **tab);
void	free_tab(char **tab);
void	print_list(t_cmd *head);
void	free_list(t_cmd **head);
void	node_remove(t_cmd *node);
void	reset_id(t_cmd *node);
int		is_quoted(char *s, int i, char c);

// envp
void	add_env_node(t_env **env, char *name, char *value, int export);
void	init_envp(t_env **env, char **envp);
t_env	*get_in_envp(t_env *env, char *key, int size_key);
void	change_value_in_envp(t_env *env,
			char *key, int size_key, char *new_value);
void	delete_export_node(t_env **env, char *key, int size_key);
void	free_envp(t_env **env);

// builtins
int		ft_echo(char **av);
int		ft_env(t_env *env);
int		ft_pwd(void);
int		ft_cd(char **av, t_env *env);
int		ft_export(char **av, t_env *env);
int		ft_unset(char **av, t_env *env);
int		fgv_exit_arg(int new);
int		ft_exit(char **av, t_env *env);

// signals
void	handle_signals(void);
void	reset_signals(void);
int		received_signal(int received);
int		fgv_in_cmd(int new);
int		fgv_sig_nb(int new);
t_env	*fgv_env(t_env *new);

// utils
int		ft_strcmp(char *s1, char *s2);
int		get_exit_status(t_env *env);

# define PROMPT "mini : "
# define HEREDOC_PROMPT "> "
# define UNHANDLED "*[]\\;&`(){}#!"

// define commands
# define ECHO 0
# define CD 1
# define PWD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6
# define EXTERNAL 7

# define PIPE 10
# define RED_INPUT 11
# define RED_OUTPUT 12
# define RED_INPUT_DEL 13
# define RED_OUTPUT_APPEND 14

# define AND 15
# define OR 16
# define PAR_OPEN 17
# define PAR_CLOSE 18

#endif