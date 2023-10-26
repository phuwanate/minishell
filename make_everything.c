#include "first.h"

int make_infile(t_list_node *token_center)
{
    char *type = "<<";
    char *type2 = "<";
    char *value = "lim";
    char *value2 = "in_file";
    size_t len_type = ft_strlen(type);
    size_t len_type2 = ft_strlen(type2);
    size_t len_value = ft_strlen(value);
    size_t len_value2 = ft_strlen(value2);
    //node 1
    token_center->infile = malloc(sizeof(t_token_node));
    token_center->infile->type = malloc(len_type);
    path_cpy(token_center->infile->type, type);
    token_center->infile->value = malloc(len_value);
    path_cpy(token_center->infile->value, value);
    //node 2
    token_center->infile->next = malloc(sizeof(t_token_node));
    token_center->infile->next->type = malloc(len_type2);
    path_cpy(token_center->infile->next->type, type2);
    token_center->infile->next->value = malloc(len_value2);
    path_cpy(token_center->infile->next->value, value2);
    token_center->infile->next->next = NULL;
    return (0);
}

int make_outfile(t_list_node *token_center)
{
    char *type = ">>";
    char *type2 = ">";
    char *value = "out1";
    char *value2 = "out2";
    size_t len_type = ft_strlen(type);
    size_t len_type2 = ft_strlen(type2);
    size_t len_value = ft_strlen(value);
    size_t len_value2 = ft_strlen(value2);
    //node 1
    token_center->outfile = malloc(sizeof(t_token_node));
    token_center->outfile->type = malloc(len_type);
    path_cpy(token_center->outfile->type, type);
    token_center->outfile->value = malloc(len_value);
    path_cpy(token_center->outfile->value, value);
    //node 2
    token_center->outfile->next = malloc(sizeof(t_token_node));
    token_center->outfile->next->type = malloc(len_type2);
    path_cpy(token_center->outfile->next->type, type2);
    token_center->outfile->next->value = malloc(len_value2);
    path_cpy(token_center->outfile->next->value, value2);
    token_center->outfile->next->next = NULL;
    return (0);
}

// ของจริงจะต้องเอา cmd ที่เป็น linklist มา join path เอง ตอนนี้เพื่อความสะดวกไปก่อน
int make_cmd(t_list_node *token_center)
{
    token_center->cmd = malloc(sizeof(char *) * 3); // for {"ls", "-l", NULL};
    token_center->cmd[2] = NULL;
    token_center->cmd[0] = malloc((sizeof(char) * (7 + 1))); // for "/bin/ls"
    token_center->cmd[1] = malloc((sizeof(char) * (1 + 1))); // for "-l"
    path_cpy(token_center->cmd[0], "/bin/ls");
    path_cpy(token_center->cmd[1], "-l");
    return (0);
}

int make_token_center(t_data *data)
{
    data->list_head = malloc(sizeof(t_list_node *));
    t_list_node *token_center = malloc(sizeof(t_list_node));
    make_infile(token_center);
    make_outfile(token_center);
    make_cmd(token_center);
    data->list_head = &token_center;
    return (0);
}