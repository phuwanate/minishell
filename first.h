#ifndef FIRST_H
# define FIRST_H


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <errno.h>
#include <string.h>
#include "get_next_line_bonus.h"

# define FALSE 0
# define TRUE  1

typedef enum e_token_mark
{
    m_undefined,
    m_heredoc,
    m_out_append,
    m_out_trunc,
    m_infile,
    m_cmd,
    m_arg,
    m_pipe
}            t_token_mark;

//token link list
typedef struct s_token_node
{

    t_token_mark        mark;
    char                *type;
    char                *value;
    int                 here_doc_fd;
    struct s_token_node *next;
} t_token_node;

//token center
typedef struct s_list_node
{
    t_token_node        *infile;
    t_token_node        *outfile;
    char                **cmd;
    struct s_list_node  *next;
} t_list_node;

//data center
typedef struct s_data
{
    int                 stdin_copy;
    int                 stdout_copy;
    char                **env;
    int                 errnum;
    t_list_node         *list_head;
    int                 *pid; //first
    int                 fd_in; //first
    int                 fd_out; //first
    int                 num_child;
    int                 exit_status;
    int                 *fd_pipe;
}   t_data;


void	path_cpy(char *dst, const char *src);
int     make_infile(t_list_node *token_center);
int     make_outfile(t_list_node *token_center);
int     make_cmd(t_list_node *token_center);
int     make_token_center(t_data *data);
void	file_error(char *file);
int     end_doc(char *hay_stack, char *needle);
int     check_infile(t_token_node *curr_token, t_data *data);
int     check_outfile(t_token_node *curr_token, t_data *data);
char	*get_next_line(int fd);
int     check_here_doc(t_list_node *curr_node, t_data *data);
int     ft_strcmp(const char *s1, const char *s2);

#endif