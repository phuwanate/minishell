#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

//token link list
typedef struct s_token_node
{
    char                *type;
    char                *value;
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
    t_list_node         **list_head;
    int                 *pid; //first
    int                 *fd_in; //first
    int                 *fd_out; //first
    int                 num_child;
    int                 exit_status;
}   t_data;


void	path_cpy(char *dst, const char *src);
int make_infile(t_list_node *token_center);
int make_outfile(t_list_node *token_center);
int make_cmd(t_list_node *token_center);
int make_token_center(t_data *data);