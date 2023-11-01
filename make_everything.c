#include "first.h"

int make_infile(t_list_node *token_center)
{
    char *value = "l1";
    // char *value2 = "l2";
    size_t len_value = ft_strlen(value);
    // size_t len_value2 = ft_strlen(value2);
    //node 1
    token_center->infile = (t_token_node *)malloc(sizeof(t_token_node));
    token_center->infile->mark = m_infile;
    token_center->infile->value = (char *)malloc(len_value + 1);
    path_cpy(token_center->infile->value, value);
    token_center->infile->next = NULL;
    //node 2
    // token_center->next->infile = malloc(sizeof(t_token_node));
    // token_center->next->infile->mark = m_heredoc;
    // token_center->next->infile->value = malloc(len_value2 + 1);
    // path_cpy(token_center->next->infile->value, value2);
    // token_center->next->infile->next = NULL;
    // //node 2.1
    // token_center->next->infile->next = malloc(sizeof(t_token_node));
    // token_center->next->infile->next->type = malloc(len_type2 + 1);
    // path_cpy(token_center->next->infile->next->type, type2);
    // token_center->next->infile->next->value = malloc(len_value + 1);
    // path_cpy(token_center->next->infile->next->value, "l2");
    // token_center->next->infile->next->next = NULL;
    return (0);
}

int make_outfile(t_list_node *token_center)
{
    token_center->outfile = NULL;
    // token_center->next->outfile = NULL;
    // char *value = "out1";
    // char *value2 = "out3";
    // size_t len_value = ft_strlen(value);
    // size_t len_value2 = ft_strlen(value2);
    // //node 1
    // token_center->outfile = malloc(sizeof(t_token_node));
    // // token_center->outfile->mark = m_out_trunc;
    // // token_center->outfile->value = malloc(len_value + 1);
    // // path_cpy(token_center->outfile->value, "out1");
    // // token_center->outfile->next = NULL;
    // // //node 1.1
    // // token_center->outfile->next = malloc(sizeof(t_token_node));
    // // token_center->outfile->next->mark = m_out_trunc;
    // // token_center->outfile->next->value = malloc(len_value + 1);
    // // path_cpy(token_center->outfile->next->value, "out2");
    // // token_center->outfile->next->next = NULL;
    // // //node 2
    // token_center->next->outfile = malloc(sizeof(t_token_node));
    // token_center->next->outfile->mark = m_out_trunc;
    // token_center->next->outfile->value = malloc(len_value2 + 1);
    // path_cpy(token_center->next->outfile->value, "out3");
    // token_center->next->outfile->next = NULL;
    // //node 2.1
    // token_center->next->outfile->next = malloc(sizeof(t_token_node));
    // token_center->next->outfile->next->mark = m_out_trunc;
    // token_center->next->outfile->next->value = malloc(len_value + 1);
    // path_cpy(token_center->next->outfile->next->value, "out4");
    // token_center->next->outfile->next->next = NULL;
    return (0);
}

// ของจริงจะต้องเอา cmd ที่เป็น linklist มา join path เอง ตอนนี้เพื่อความสะดวกไปก่อน
int make_cmd(t_list_node *token_center)
{
    char    *cmd = "cat";
    // char    *cmd2 = "/usr/bin/wc";
    int     len_cmd = ft_strlen(cmd);
    // int     len_cmd2 = ft_strlen(cmd2);
    // // node 1
    // token_center->cmd = (char **)malloc(sizeof(char *) * 3);
    // token_center->cmd[0] = (char *)malloc((sizeof(char) * (len_cmd + 1)));
    // token_center->cmd[1] = NULL;
    // token_center->cmd[2] = NULL;
    // path_cpy(token_center->cmd[0], cmd);
    // // node 2
    // token_center->next->cmd = (char **)malloc(sizeof(char *) * 3);
    // token_center->next->cmd[0] = (char *)malloc((sizeof(char) * (len_cmd2 + 1)));
    // token_center->next->cmd[1] = (char *)malloc((sizeof(char) * (3))); // for "-l"
    // path_cpy(token_center->next->cmd[0], cmd2);
    // path_cpy(token_center->next->cmd[1], "-l");
    // token_center->next->cmd[2] = NULL;

    //Real cmd
    token_center->cmd = (t_token_node *)malloc(sizeof(t_token_node));
    token_center->cmd->mark = m_cmd;
    token_center->cmd->value = (char *)malloc(len_cmd + 1);
    path_cpy(token_center->cmd->value, cmd);
    return (0);
}

int make_token_center(t_data *data)
{
    //first node
    t_list_node *token_center = malloc(sizeof(t_list_node));
    // token_center->next = NULL;
    //second node
    token_center->next = malloc(sizeof(t_list_node));
    token_center->next->next = NULL;
    data->list_head = token_center;
    make_infile(token_center);
    make_outfile(token_center);
    make_cmd(token_center);
    data->num_child = 2;
    data->pid = malloc(sizeof(int) * 2);
    return (0);
}


//------------------test case---------------------
    // multiple here_document
    // //node 1
    // token_center->cmd = malloc(sizeof(char *) * 3); // for {"ls", "-l", NULL};
    // token_center->cmd[0] = malloc((sizeof(char) * (8 + 1))); // for "/bin/ls"
    // token_center->cmd[1] = NULL;
    // path_cpy(token_center->cmd[0], "/bin/cat");
    // //node 2
    // token_center->next->cmd = malloc(sizeof(char *) * 3); // for {"ls", "-l", NULL};
    // token_center->next->cmd[0] = malloc((sizeof(char) * (8 + 1))); // for "/bin/ls"
    // token_center->next->cmd[1] = NULL;
    // // token_center->next->cmd[1] = malloc((sizeof(char) * (1))); // for "-l"
    // path_cpy(token_center->next->cmd[0], "/bin/cat");
    // // path_cpy(token_center->next->cmd[1], "-l");
    // token_center->next->cmd[2] = NULL;

//------------------test case---------------------
   //pararell sleep test
        //node 1
    // char *type = "/bin/sleep";
    // char *type2 = "/bin/sleep";
    // char *value = "1";
    // char *value2 = "7";
    // size_t len_type = ft_strlen(type);
    // size_t len_type2 = ft_strlen(type2);
    // size_t len_value = ft_strlen(value);
    // size_t len_value2 = ft_strlen(value2);
    // token_center->cmd = malloc(sizeof(char *) * 3); // for {"ls", "-l", NULL};
    // token_center->cmd[0] = malloc((sizeof(char) * (len_type + 1))); // for "/bin/ls"
    // token_center->cmd[1] = malloc((sizeof(char) * (len_value + 1))); // for "-l"
    // path_cpy(token_center->cmd[0], type);
    // path_cpy(token_center->cmd[1], value);
    // //node 2
    // token_center->next->cmd = malloc(sizeof(char *) * 3); // for {"ls", "-l", NULL};
    // token_center->next->cmd[0] = malloc((sizeof(char) * (len_type + 1))); // for "/bin/ls"
    // token_center->next->cmd[1] = malloc((sizeof(char) * (len_value2 + 1))); // for "-l"
    // path_cpy(token_center->next->cmd[0], type);
    // path_cpy(token_center->next->cmd[1], value2);
    // token_center->next->cmd[2] = NULL;
    // return (0);
    // //node 3
    // token_center->next->next->cmd = malloc(sizeof(char *) * 3); // for {"ls", "-l", NULL};
    // token_center->next->next->cmd[0] = malloc((sizeof(char) * (11 + 1))); // for "/bin/ls"
    // token_center->next->next->cmd[1] = malloc((sizeof(char) * (2 + 1))); // for "-l"
    // path_cpy(token_center->next->next->cmd[0], type);
    // path_cpy(token_center->next->next->cmd[1], value2);
    // token_center->next->next->cmd[2] = NULL;
    // return (0);

//---------------------------- Hard code cmd test---------------------------------//
    // char    *cmd = "/bin/cat";
    // char    *cmd2 = "/usr/bin/wc";
    // int     len_cmd = ft_strlen(cmd);
    // int     len_cmd2 = ft_strlen(cmd2);
    //node 1
    // token_center->cmd = (char **)malloc(sizeof(char *) * 3);
    // token_center->cmd[0] = (char *)malloc((sizeof(char) * (len_cmd + 1)));
    // token_center->cmd[1] = NULL;
    // token_center->cmd[2] = NULL;
    // token_center->cmd[1] = malloc((sizeof(char) * (1 + 1))); // for "-l"
    // path_cpy(token_center->cmd[0], cmd);
    // path_cpy(token_center->cmd[1], "-l");
    //node 2
    // token_center->next->cmd = (char **)malloc(sizeof(char *) * 3);
    // token_center->next->cmd[0] = (char *)malloc((sizeof(char) * (len_cmd2 + 1)));
    // // token_center->next->cmd[1] = NULL;
    // token_center->next->cmd[1] = (char *)malloc((sizeof(char) * (3))); // for "-l"
    // path_cpy(token_center->next->cmd[0], cmd2);
    // path_cpy(token_center->next->cmd[1], "-l");
    // token_center->next->cmd[2] = NULL;
    //pararell sleep test
        //node 1
    // char *type = "/bin/sleep";
    // char *value = "10";
    // char *value2 = "2";
    // size_t len_type = ft_strlen(type);
    // size_t len_value = ft_strlen(value);
    // size_t len_value2 = ft_strlen(value2);
    // token_center->cmd = malloc(sizeof(char *) * 3); // for {"ls", "-l", NULL};
    // token_center->cmd[0] = malloc((sizeof(char) * (len_type + 1))); // for "/bin/ls"
    // token_center->cmd[1] = malloc((sizeof(char) * (len_value + 1))); // for "-l"
    // path_cpy(token_center->cmd[0], type);
    // path_cpy(token_center->cmd[1], value);
    // //node 2
    // token_center->next->cmd = malloc(sizeof(char *) * 3); // for {"ls", "-l", NULL};
    // token_center->next->cmd[0] = malloc((sizeof(char) * (len_type + 1))); // for "/bin/ls"
    // token_center->next->cmd[1] = malloc((sizeof(char) * (len_value2 + 1))); // for "-l"
    // path_cpy(token_center->next->cmd[0], type);
    // path_cpy(token_center->next->cmd[1], value2);
    // token_center->next->cmd[2] = NULL;