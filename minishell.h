/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plertsir <plertsir@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:05:57 by plertsir          #+#    #+#             */
/*   Updated: 2023/11/15 18:55:17 by plertsir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define FALSE 0
# define TRUE  1

typedef struct sigaction	t_sigaction;
int							g_signal;

typedef enum e_token_mark
{
	m_undefined,
	m_heredoc,
	m_out_append,
	m_out_trunc,
	m_infile,
	m_cmd,
	m_pipe
}			t_token_mark;

typedef struct s_token_node
{
	t_token_mark		mark;
	char				*type;
	char				*value;
	int					here_doc_fd;
	struct s_token_node	*next;
}						t_token_node;

typedef struct s_token_ptr
{
	t_token_node		*head;
	t_token_node		*tail;
}						t_token_ptr;

typedef struct s_group_ptr
{
	t_token_ptr		infile;
	t_token_ptr		outfile;
	t_token_ptr		cmd;
}						t_group_ptr;

typedef struct s_list_node
{
	int					is_pipe;
	t_token_node		*infile;
	t_token_node		*outfile;
	t_token_node		*cmd;
	struct s_list_node	*next;
}						t_list_node;

typedef struct s_data
{
	size_t				env_row_max;
	t_token_ptr			lst_token;
	t_list_node			*grouped_token;
	char				**env;
	char				*path_exec;
	int					in_dbq;
	int					errnum;
	int					stdin_copy;
	int					stdout_copy;
	int					*pid;
	int					fd_in;
	int					fd_out;
	int					num_child;
	int					index;
	int					len_path;
	int					builtin_parent;
	int					child_born;
}						t_data;

int		first_execute(t_data *data);
void	path_cpy(char *dst, const char *src);
int		make_infile(t_list_node *token_center);
int		make_outfile(t_list_node *token_center);
int		make_cmd(t_list_node *token_center);
int		make_token_center(t_data *data);
int		end_doc(char *hay_stack, char *needle);
int		check_infile(t_token_node *curr_token, t_data *data);
int		check_outfile(t_token_node *curr_token, t_data *data);
char	*get_next_line(int fd);
int		check_here_doc(t_list_node *curr_list);
int		ft_strcmp(const char *s1, const char *s2);
void	free_everything(t_data *data);
void	rl_clear_history(void);
void	rl_replace_line(const char *text, int clear_undo);
void	fork_child(t_data *data, t_list_node *curr_list, int *pipe_w, \
		int *pipe_r);

int		find_path(const char *s1);
void	get_path(t_list_node *curr_list, t_data *data);
void	path_error(t_data *data, t_token_node *curr_token);
void	go_exec(t_data *data, t_list_node *curr_list);
//Error executor
void	file_error(t_data *data, char *file);
void	path_error(t_data *data, t_token_node *curr_token);
void	cmd_error(t_data *data, t_token_node *curr_token);
//Built in
int		check_builtin_parent(t_data *data, t_list_node *curr_list);
int		check_builtin_child(t_data *data, t_list_node *curr_list);
void	change_dir(t_data *data, t_list_node *curr_list);
int		get_curr_dir(t_data *data);
void	go_exit(t_data *data, t_list_node *curr_list);
int		check_status(t_token_node *curr_token, unsigned char *status);
int		before_child_exe(t_data *data, t_list_node *curr_list);
int		export_new_env(t_data *data, t_token_node *curr_token);
int		declare_env(t_data *data);
int		is_valid_ident(t_data *data, t_token_node *curr_token);
long	ft_atol(char *str, int *status);
int		check_inout_file(t_data *data, t_list_node *curr_list);
void	free_env(char **env_copy);
char	*join_quote(char *env_copy);
void	sort_env(t_data *data, char **env_copy);
void	call_env(t_data *data, t_token_node *curr_token);
void	echo_words(t_data *data, t_token_node *curr_token);
int		is_directory(const char *path);
void	cd_path_error(t_data *data, t_token_node *curr_token);
void	export_err(t_data *data, t_token_node *curr_token);
void	unset_err(t_data *data, t_token_node *curr_token);
int		unset_env(t_data *data, t_token_node *curr_token);
int		is_duplicate(char *s1, char *s2);
int		is_valid_unset(t_data *data, t_token_node *curr_token);
size_t	len_env(char *str);
void	free_grouped_token(t_list_node *curr_list);
void	free_everything(t_data *data);
void	check_cd_err(t_data *data, t_list_node *curr_list);
void	execeve_fail(t_data *data, t_token_node *curr_token);
void	cd_update(t_data *data, char *old_pwd);
void	cd_err(t_data *data, t_list_node *curr_list, int errno_nb);
void	cd_old(t_data *data);
void	cd_update_old(t_data *data, char *old_pwd);
char	*find_home(t_data *data);

#endif