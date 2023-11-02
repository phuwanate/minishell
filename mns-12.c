/*
gcc -I/opt/homebrew/Cellar/readline/8.2.1/include -L/opt/homebrew/Cellar/readline/8.2.1/lib -o mns mns.c libft/libft.a -lreadline -lncurses
gcc -I/usr/local/Cellar/readline/8.2.1/include -L/usr/local/Cellar/readline/8.2.1/lib -o mns mns.c libft/libft.a -lreadline -lncurses
*/

/////////////////////////////////* * PLAN * *////////////////////////////////////
/*
	- readline
	- signal
	- unorganized_token (except error , $, ~)
	- organized_token <-- NOW
	- err_check
	- grouped_token
*/
/////////////////////////////////////////////////////////////////////////////////

#include "minishell.h"

////////////////////////////**DEBUG FUNCTION**////////////////////////////////////

// print token_node 
void print_token_node(t_token_node *node) 
{
	if (node) 
	{
		printf("Mark: %u\n", node->mark); // show in index
		printf("Value: %s\n", node->value); 
	} 
	else
		printf("Node is NULL\n");
}

// print link list (t_token_node)
void print_link_list(t_token_node *head) 
{
	int i = 1;
	t_token_node *current = head;
	while (current != NULL)
	{
		printf("\nnumber: %d\n", i);
		print_token_node(current);
		printf("\n");
		current = current->next;
		i++;
	}
	printf("\nNULL\n");
}

// print link list (t_list_node)
void print_group_list(t_list_node *head) 
{
	t_list_node *current = head;
	int i = 1;
	while (current != NULL) 
	{
		printf("\nnode number: %d\n", i);
		printf("is_pipe: %d\n", current->is_pipe);

		// Print infile
		t_token_node *infile = current->infile;
		printf("infile: ");
		while (infile != NULL) {
			printf("%s(%u) -> ", infile->value, infile->mark);
			infile = infile->next;
		}
		printf("NULL\n");

		// Print outfile
		t_token_node *outfile = current->outfile;
		printf("outfile: ");
		while (outfile != NULL) {
			printf("%s(%u) -> ", outfile->value, outfile->mark);
			outfile = outfile->next;
		}
		printf("NULL\n");

		// Print cmd
		t_token_node *cmd = current->cmd;
		printf("cmd: ");
		while (cmd != NULL) {
			printf("%s(%u) -> ", cmd->value, cmd->mark);
			cmd = cmd->next;
		}
		printf("NULL\n");
		i++;
		current = current->next;
	}
}

// // print node (group list)
// void print_group_head(t_list_node *head) {
// 	if (head != NULL) {
// 		printf("is_pipe: %d\n", head->is_pipe);

// 		// Print infile
// 		t_token_node *infile = head->infile;
// 		printf("infile: ");
// 		while (infile != NULL) {
// 			printf("%s -> ", infile->value);
// 			infile = infile->next;
// 		}
// 		printf("NULL\n");

// 		// Print outfile
// 		t_token_node *outfile = head->outfile;
// 		printf("outfile: ");
// 		while (outfile != NULL) {
// 			printf("%s -> ", outfile->value);
// 			outfile = outfile->next;
// 		}
// 		printf("NULL\n");

// 		// Print cmd
// 		t_token_node *cmd = head->cmd;
// 		printf("cmd: ");
// 		while (cmd != NULL) {
// 			printf("%s -> ", cmd->value);
// 			cmd = cmd->next;
// 		}
// 		printf("NULL\n");
// 	} else {
// 		printf("The linked list is empty.\n");
// 	}
// }


////////////////////////////mns_free.c////////////////////////////////////

void	free_mns(t_data *data)
{
	(void)(data);
	rl_clear_history();
}

void	free_char_2d(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free (ptr);
	ptr = NULL;
}

void	free_token_list(t_token_node *token_ptr)
{
	t_token_node	*tmp_node;

	while (token_ptr)
	{
		tmp_node = token_ptr->next;
		free(token_ptr->value);
		free(token_ptr);
		token_ptr = tmp_node;
	}
}

void	free_group_list (t_list_node *list_head)
{
	t_list_node	*tmp_head;
	
	while (list_head)
	{
		tmp_head = list_head;
		list_head = list_head->next;
		free_token_list(tmp_head->cmd);
		free_token_list(tmp_head->infile);
		free_token_list(tmp_head->outfile);
		free(tmp_head);
	}
}

/////////////////////////////////////////////////////////////////////////////////

t_token_node	*token_node_create (t_token_ptr *ptr, t_token_mark mark)
{
	t_token_node	*new;

	if(!ptr)
		return (NULL);
	new = (t_token_node *)malloc(sizeof(t_token_node) * 1);
	if (!new)
		return (NULL);
	new->mark = mark;
	new->value = 0;
	new->next = 0;
	if (ptr->head)
	{
		(ptr->tail)->next = new;
		ptr->tail = (ptr->tail)->next;
		return (new);
	}
	else
	{
		ptr->head = new;
		ptr->tail = ptr->head;
		return (new);
	}
}

/////////////////////////////token_to_organize_utils.c///////////////////////////////////


void	group_init (t_group_ptr	*group)
{
	group->infile.head = 0;
	group->infile.tail = 0;
	group->outfile.head = 0;
	group->outfile.tail = 0;
	group->cmd.head = 0;
	group->cmd.tail = 0;
}

void	skip_next_node(t_token_node *node)
{
	t_token_node	*tmp;

	if(!node->next)
		return ;
	tmp = node->next;
	node->next = node->next->next;
	free(tmp->value);
	free(tmp);
}
///////////////////////////////token_to_organize.c//////////////////////////////////////
	
// t_token_node *	move_token(t_token_ptr *src, t_token_node *dst_head)
// {
// 	t_token_node *dst_tail;
	
// 	// **move_token(input) : CORRECT**
// 	// printf("\nsrc input:\n");// ** DEBUG **********************************************************************
// 	// print_link_list(src->head); // ** DEBUG **********************************************************************
// 	// printf("\ndst input:\n");// ** DEBUG **********************************************************************
// 	// print_link_list(dst_head); // ** DEBUG **********************************************************************
	
// 	dst_tail = 0;
// 	if (!src || !src->head)
// 		return (NULL);
// 	printf("\ndst input:\n");// ** DEBUG **********************************************************************
// 	print_link_list(dst_head); // ** DEBUG **********************************************************************
	
// 	if (dst_head == 0)
// 		dst_head = src->head;
// 	else
// 	{
// 		dst_tail = dst_head;
// 		while (dst_tail->next)
// 			dst_tail = dst_tail->next;
// 		dst_tail->next = src->head;
// 	}
// 	return (dst_head);

// 	//**dst output: correct**
// 	// printf("\ndst output:\n");// ** DEBUG **********************************************************************
// 	// print_link_list(dst_head); // ** DEBUG **********************************************************************
	
// }

t_list_node	*make_list_node(t_group_ptr *group, int pipe)
{
	//in each of tmp group is link list
	//move_token: is to move from one link llist(in tmp group) to another link list(output)


	// **group(input) : CORRECT**
	// printf("\nGROUP INPUT\n");
	// printf("\nCMD output:\n");// ** DEBUG **********************************************************************
	// print_link_list(group->cmd.head); // ** DEBUG **********************************************************************

	// printf("\nINFILE output:\n");// ** DEBUG **********************************************************************
	// print_link_list(group->infile.head); // ** DEBUG **********************************************************************
	
	// 	printf("\nOUTFILE output:\n");// ** DEBUG **********************************************************************
	// print_link_list(group->outfile.head); // ** DEBUG **********************************************************************

	t_list_node	*new_node;

	if (!group || (!(group->cmd.head) && !(group->infile.head) && !(group->outfile.head)))
		return (NULL);
	new_node = (t_list_node *)malloc(sizeof(t_list_node) * 1);
	if(!new_node)
		return (NULL);
	new_node->is_pipe = 0;
	new_node->cmd = 0;
	new_node->infile = 0;
	new_node->outfile = 0;
	new_node->next = 0;
	if(group->cmd.head)
		new_node->cmd = group->cmd.head;
		// new_node->cmd = move_token(&group->cmd, new_node->cmd);
	if(group->infile.head)
		new_node->infile = group->infile.head;
		// new_node->infile = move_token(&group->infile, new_node->infile);
	if(group->outfile.head)
		new_node->outfile = group->outfile.head;
		// new_node->outfile = move_token(&group->outfile, new_node->outfile);
	if (pipe)
		new_node->is_pipe = 1;
	group_init (group);
	return (new_node);
	// if (!group->cmd.head->value)
	// {
	// 	output->head = 
	// }

		// **group(output) : CORRECT**
	// printf("\nGROUP OUTPUT\n");

	// printf("\nCMD output:\n");// ** DEBUG **********************************************************************
	// print_link_list(new_node->cmd); // ** DEBUG **********************************************************************

	// printf("\nINFILE output:\n");// ** DEBUG **********************************************************************
	// print_link_list(new_node->infile); // ** DEBUG **********************************************************************
	
	// printf("\nOUTFILE output:\n");// ** DEBUG **********************************************************************
	// print_link_list(new_node->outfile); // ** DEBUG **********************************************************************

}

t_list_node	*unorganize_to_tmp_group(t_group_ptr *group, t_token_node *src_head)
{
	// ** input: CORRECT **

	// printf("\nun_to_tmp_g input:\n"); // ** DEBUG ********************************************************************
	// print_link_list(src_head); // ** DEBUG ********************************************************************

	if (src_head->mark == m_undefined)
		token_node_create(&group->cmd, m_cmd)->value = ft_strdup(src_head->value);
	if (src_head->next)
	{
		// ** input: CORRECT **

		// printf("\ninput:\n"); // ** DEBUG ********************************************************************
		// print_link_list(src_head); // ** DEBUG ********************************************************************

		if (src_head->mark == m_heredoc || src_head->mark == m_infile)
		{
			token_node_create(&group->infile, src_head->mark)->value = ft_strdup(src_head->next->value);
			skip_next_node(src_head);
		}
	
		if (src_head->mark == m_out_append|| src_head->mark == m_out_trunc)
		{
			token_node_create(&group->outfile, src_head->mark)->value = ft_strdup(src_head->next->value);
			skip_next_node(src_head);
		}

		// printf("\nOUTFILE output:\n");// ** DEBUG **********************************************************************
		// print_link_list(group->outfile.head); // ** DEBUG **********************************************************************
	}
	// **group : CORRECT**
	// printf("\nCMD output:\n");// ** DEBUG **********************************************************************
	// print_link_list(group->cmd.head); // ** DEBUG **********************************************************************

	// printf("\nINFILE output:\n");// ** DEBUG **********************************************************************
	// print_link_list(group->infile.head); // ** DEBUG **********************************************************************
	
	// 	printf("\nOUTFILE output:\n");// ** DEBUG **********************************************************************
	// print_link_list(group->outfile.head); // ** DEBUG **********************************************************************
	if (!src_head->next)
		return (make_list_node(group, 0));
	if (src_head->mark == m_pipe)
		return (make_list_node(group, 1));
	return (NULL);
}

void	unorganize_to_organize(t_group_ptr *group, t_token_ptr *src, t_list_node *dst_head)
{
	t_list_node		*tmp_new;
	t_list_node		*dst_tail;
	t_token_node	*head_ptr;
	
	// ** input: CORRECT **

	// printf("\nun_to_or input:\n"); // ** DEBUG ********************************************************************
	// print_link_list(src->head); // ** DEBUG ********************************************************************

	if(!src || !src->head)
		return ;
	tmp_new = unorganize_to_tmp_group(group, src->head);
	head_ptr = src->head;
	src->head = src->head->next;
	free(head_ptr->value);
	free(head_ptr);

	// **tmp_new: NOT CORRECT**
	// printf("\nun_to_tmp output:\n"); // ** DEBUG ********************************************************************
	// print_group_list(tmp_new);// ** DEBUG ********************************************************************

	if(!tmp_new)
		return ;
	if (!dst_head)
		dst_head = tmp_new;
	else
	{
		dst_tail = dst_head;
		while(dst_tail->next)
			dst_tail = dst_tail->next;
		dst_tail->next = tmp_new;
		
	}

		
	// ** dst: NOT CORRECT **

	// printf("\noutput:\n"); // ** DEBUG ********************************************************************
	// print_group_list(dst_head); // ** DEBUG ******************************************************************

}

void	token_to_organize(t_data *data, t_token_ptr *input)
{
	
	t_group_ptr	tmp_group;
	t_list_node	dst_head;
	
	// t_token_ptr	*success_group_token;
	// success_group_token = &data->grouped_token;

	// ** input: CORRECT **

	// printf("\nt_to_o input:\n"); // ** DEBUG ********************************************************************
	// print_link_list(input->head); // ** DEBUG ********************************************************************

	// int i = 1;// ** DEBUG ********************************************************************
	group_init (&tmp_group);
	dst_head.cmd = 0;
	dst_head.infile = 0;
	dst_head.is_pipe = 0;
	dst_head.outfile = 0;
	dst_head.next = 0;
	while (input->head)
	{
		// ** input loop: CORRECT **

		// printf("\nwhile loop %d\n", i); // * DEBUG ********************************************************************
		// print_link_list(input->head); // ** DEBUG ********************************************************************
		// i++;// ** DEBUG ********************************************************************

		if(!input->head->value)
		{
			free_token_list(tmp_group.infile.head);
			free_token_list(tmp_group.outfile.head);
			free_token_list(tmp_group.cmd.head);
			free_token_list(input->head);
			//free_token_list(data->organized_token.head);//output chande to grouped_token
			return ;
		}
		unorganize_to_organize(&tmp_group, input, &dst_head);
	}

	data->grouped_token = dst_head.next;

	
	// 	// **data->grouped_token: CORRECT **
	// printf("\nGROUP_TOKEN output:\n"); // ** DEBUG ********************************************************************
	// print_group_list(data->grouped_token); // ** DEBUG ******************************************************************




	// ** data->organized_token): CORRECT **
	//correct order and no token from last prompt


	// printf("\noutput:\n"); // ** DEBUG ********************************************************************
	// print_link_list(data->organized_token.head); // ** DEBUG ******************************************************************


	// err_check(data);
	//ungroup_to_group(data);
	// if (!success_group_token)
	// {
	// 	free_mns(data);
	// 	exit (0);
	// }
}

////////////////////////////input_to_token_utils2.c////////////////////////////////////

char	*match_outside_qoute(char *tmp_ptr, char *must_match, int match_in_dbq)
{
	int		sq;
	int		dbq;

	sq = 0;
	dbq = 0;
	while (*tmp_ptr)
	{
		if (!dbq && *tmp_ptr == '\'')
			sq = !sq;
		if (!sq && *tmp_ptr == '\"')
			dbq = !dbq;
		if (!ft_strncmp(tmp_ptr, must_match, ft_strlen(must_match)) && !sq && (!dbq || match_in_dbq))
			break ;
		tmp_ptr++;
	}
	return (tmp_ptr);
}

void	split_quote(t_data *data, t_token_ptr *tmp_ptr, t_token_node *src_head)
{
	int		sq;
	int		dbq;
	char	*res;
	size_t	i;
	size_t	res_i;

	(void)(data);
	sq = 0;
	dbq = 0;
	i = 0;
	res_i = 0;
	res = ft_calloc(ft_strlen(src_head->value) + 1, 1);
	while (src_head->value[i])
	{
		if (!sq && src_head->value[i] == '\"')
			dbq = !dbq;
		else if (!dbq && src_head->value[i] == '\'')
			sq = !sq;
		else
			res[res_i++] = src_head->value[i];
		i++;
	}
	token_node_create(tmp_ptr, src_head->mark)->value = res;
}

void	split_pipe(t_data *data, t_token_ptr *tmp_ptr, t_token_node *src_head)
{
	char	*main_cptr;
	char	*match_cptr;
	size_t	len;

	(void)(data);
	main_cptr = src_head->value;
	match_cptr = src_head->value;
	while (1)
	{
		match_cptr = match_outside_qoute(match_cptr, "|", 0);
		len = match_cptr - main_cptr;
		if (len)
			token_node_create(tmp_ptr, src_head->mark)->value = ft_substr(main_cptr, 0, len);
		if (*match_cptr)
			token_node_create(tmp_ptr, m_pipe)->value = ft_strdup("|");
		else
			break ;
		match_cptr += 1;
		main_cptr = match_cptr;
	}
}

void	split_infile(t_data *data, t_token_ptr *tmp_ptr, t_token_node *src_head)
{
	char	*main_cptr;
	char	*match_cptr;
	size_t	len;

	(void)(data);
	main_cptr = src_head->value;
	match_cptr = src_head->value;
	if (src_head->mark == m_heredoc)
	{
		token_node_create(tmp_ptr, src_head->mark)->value = ft_strdup("<<");
		return ;
	}
	while (1)
	{
		match_cptr = match_outside_qoute(match_cptr, "<", 0);
		len = match_cptr - main_cptr;
		if (len)
			token_node_create(tmp_ptr, src_head->mark)->value = ft_substr(main_cptr, 0, len);
		if (*match_cptr)
			token_node_create(tmp_ptr, m_infile)->value = ft_strdup("<");
		else
			break ;
		match_cptr += 1;
		main_cptr = match_cptr;
	}
}

////////////////////////////input_to_token_utils3.c////////////////////////////////////

char	*ft_strjoin_free(char *src, char *dst)
{
	char	*res;
	size_t	count;
	size_t	i;
	size_t	j;

	if (!dst && !src)
		return (NULL);
	if (!dst || !*dst)
		return (src);
	else if (!src || !*src)
		return (dst);
	count = ft_strlen(src) + ft_strlen(dst);
	res = (char *)malloc(sizeof(char) * (count + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while(src[j])
		res[i++] = src[j++];
	j = 0;
	while (dst[j])
		res[i++] = dst[j++];
	res[i] = '\0';
	return (free(src), free(dst), res);
}
size_t	index_of_c(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
char	*env_key(t_data *data, char *key)
{
	size_t	i;
	size_t	str_len;
	size_t	key_len;
	char	**env = data->env;
	
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		str_len = index_of_c(env[i], '=');
		if (key_len > str_len)
			str_len = key_len;
		if (ft_strncmp(key, env[i], str_len) == 0)
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

void	env_replacement(char **env_replace, char **next_nonchar, char **match_cptr,
		t_data *data)
{
	char	*str;
	char	*env_c;
	char	*tmp;
	char	*get_env;

	str = (*match_cptr) + 1;
	if (*str == '?')
	{
		str++;
		*env_replace = ft_strjoin_free((*env_replace), ft_itoa(data->errnum));
		*next_nonchar = str;
		return ;
	}
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	if (str > (*match_cptr) + 1)
	{
		env_c = ft_substr(*match_cptr, 1, str - *match_cptr - 1);
		tmp = *env_replace;
		get_env = env_key(data, env_c);
		if (get_env)
		{
			*env_replace = ft_strjoin(tmp, get_env);
			free(tmp);
		}
		free(env_c);
	}
	else
		*env_replace = ft_strjoin_free(*env_replace, ft_strdup("$"));
	*next_nonchar = str;
}

void	split_dollar_sign(t_data *data, t_token_ptr *dst_ptr, t_token_node *src_head)
{
	char	*main_cptr;
	char	*match_cptr;
	char	*next_nonchar;
	char	*env_replace;
	size_t	len;

	main_cptr = src_head->value;
	match_cptr = main_cptr;
	env_replace = ft_strdup("");
	while (1)
	{
		match_cptr = match_outside_qoute(match_cptr, "$", 1);
		len = match_cptr - main_cptr;
		if (len)
			env_replace = ft_strjoin(env_replace, ft_substr(main_cptr, 0, len));
		if (*match_cptr)
			env_replacement(&env_replace, &next_nonchar, &match_cptr, data);
		if (!*match_cptr)
			break ;
		match_cptr = next_nonchar;
		main_cptr = match_cptr;
	}
	token_node_create(dst_ptr, src_head->mark)->value = env_replace;
}



////////////////////////////input_to_token_utils1.c////////////////////////////////////

static void	split_out_trunc(t_data *data, t_token_ptr *tmp_ptr, t_token_node *src_head)
{
	char	*main_cptr;
	char	*match_cptr;
	size_t	len;

	(void)(data);
	main_cptr = src_head->value;
	match_cptr = src_head->value;
	if (src_head->mark == m_out_append)
	{
		token_node_create(tmp_ptr, src_head->mark)->value = ft_strdup(">>");
		return ;
	}
	while (1)
	{
		match_cptr = match_outside_qoute(match_cptr, ">", 0);
		len = match_cptr - main_cptr;
		if (len)
			token_node_create(tmp_ptr, src_head->mark)->value = ft_substr(main_cptr, 0, len);
		if (*match_cptr)
			token_node_create(tmp_ptr, m_out_trunc)->value = ft_strdup(">");
		else
			break ;
		match_cptr += 1;
		main_cptr = match_cptr;
	}
}

static void	split_out_append(t_data *data, t_token_ptr *tmp_ptr, t_token_node *src_head)
{
	char	*main_cptr;
	char	*match_cptr;
	size_t	len;

	(void)(data);
	main_cptr = src_head->value;
	match_cptr = src_head->value;
	while (1)
	{
		match_cptr = match_outside_qoute(match_cptr, ">>", 0);
		len = match_cptr - main_cptr;
		if (len)
			token_node_create(tmp_ptr, src_head->mark)->value = ft_substr(main_cptr, 0, len);
		if (*match_cptr)
			token_node_create(tmp_ptr, m_out_append)->value = ft_strdup(">>");
		else
			break ;
		match_cptr += 2;
		main_cptr = match_cptr;
	}
}

static void	split_heredoc(t_data *data, t_token_ptr *tmp_ptr, t_token_node *src_head)
{
	char	*main_cptr;
	char	*match_cptr;
	size_t	len;

	(void)(data);
	main_cptr = src_head->value;
	match_cptr = src_head->value;
	while (1)
	{
		match_cptr = match_outside_qoute(match_cptr, "<<", 0);
		len = match_cptr - main_cptr;
		if (len)
			token_node_create(tmp_ptr, src_head->mark)->value = ft_substr(main_cptr, 0, len);
		if (*match_cptr)
			token_node_create(tmp_ptr, m_heredoc)->value = ft_strdup("<<");
		else
			break ;
		match_cptr += 2;
		main_cptr = match_cptr;
	}
}

static void	split_space(t_data *data, t_token_ptr *tmp_ptr, t_token_node *src_head)
{
	char	*main_cptr;
	char	*match_cptr;
	size_t	len;

	(void)(data);
	main_cptr = src_head->value;
	match_cptr = src_head->value;
	while (1)
	{
		match_cptr = match_outside_qoute(match_cptr, " ", 0);
		len = match_cptr - main_cptr;
		if (len)
			token_node_create(tmp_ptr, src_head->mark)->value = ft_substr(main_cptr, 0, len);
		if (!*match_cptr)
			break ;
		match_cptr += 1;
		main_cptr = match_cptr;
	}
}

void	token_split(t_data *data, t_token_ptr *src, t_token_ptr *dst, void (*fn)(t_data *data, t_token_ptr *tmp_ptr, t_token_node *src_head))
{
	t_token_ptr		tmp_ptr;
	t_token_node	*head_ptr;

	while (src->head)
	{
		tmp_ptr.head = 0;
		tmp_ptr.tail = 0;
		if(!fn || !src || !dst || !src->head)
			return ;
		fn (data, &tmp_ptr, src->head);
		head_ptr = src->head;
		src->head = src->head->next;
		free(head_ptr->value);
		free(head_ptr);
		if(!tmp_ptr.head)
			return ;
		if (!dst->head)
			dst->head = tmp_ptr.head;
		else
			dst->tail->next = tmp_ptr.head;
		dst->tail = tmp_ptr.tail;
	}
}

////////////////////////////input_to_token.c////////////////////////////////////

void	input_to_token(t_data *data, char *input)
{
	t_token_ptr	tmp1;
	t_token_ptr	tmp2;
	t_token_ptr	*output;

	output = &data->unorganized_token;
	if(!input || !output)
		return ;
	tmp1.head = 0;
	tmp1.tail = 0;
	tmp2.head = 0;
	tmp2.tail = 0;
	token_node_create(&tmp1, m_undefined)->value = input;
	// free(input); //ไม่แน่ใจว่าต้องฟรีมั้ย แต่เอาค่าไป = valueแล้ว ซึ่งจะฟรีvalueทีหลัง
	token_split (data, &tmp1, &tmp2, split_space);
	token_split (data, &tmp2, &tmp1, split_heredoc);
	token_split (data, &tmp1, &tmp2, split_out_append);
	token_split (data, &tmp2, &tmp1, split_out_trunc);
	token_split (data, &tmp1, &tmp2, split_infile);
	token_split (data, &tmp2, &tmp1, split_pipe);
	token_split (data, &tmp1, &tmp2, split_dollar_sign); //** not finish **
	// token_split (data, &tmp2, &tmp1, split_tilde_symbol); ** not finish **
	token_split (data, &tmp2, &tmp1, split_quote);
	data->unorganized_token.head = tmp1.head;
	data->unorganized_token.tail = tmp1.tail;

	// print_link_list(data->unorganized_token.head); // ** DEBUG **********************************************************************
}

////////////////////////////mns_init.c////////////////////////////////////

static void	env_init(t_data *data, char **envp)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	while (envp[row])
		row++;
	data->env = (char **)malloc(sizeof(char *) * (row + 1));
	if(!data->env)
		return ;
	while (i < row)
	{
		data->env[i] = ft_strdup(envp[i]);
		if(!data->env[i])
		{
			free_char_2d(data->env);
			return ;
		}
		i++;
	}
	data->env[row] = 0;
	data->env_row_max = row;
}

static void	sig_quit_handling(int sig_num)
{
	if (sig_num == SIGINT && g_signal == 0)
		rl_redisplay();
}

static void	sig_int_handling(int sig_num)
{
	if (sig_num == SIGINT && g_signal == 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDOUT_FILENO);
		rl_redisplay();
	}
}

static void	signal_init (void)
{
	t_sigaction	sig_int;
	t_sigaction	sig_quit;

	sig_int.sa_handler = sig_int_handling;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = sig_quit_handling;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	mns_init (t_data *data, char **envp)
{
	g_signal = 0;
	data->errnum = 0;
	data->env = 0;
	data->env_row_max = 0;
	data->unorganized_token.head = 0;
	data->unorganized_token.tail = 0;
	data->grouped_token = 0;
	data->path_exec = 0;
	data->stdin_copy = 0;
	data->stdout_copy = 0;
	data->pid = 0;
	data->fd_in = 0;
	data->fd_out = 0;
	data->num_child = 0;
	data->index = 0;
	data->len_path = 0;
	data->builtin_parent = 0;
	data->child_born = 0;

	signal_init ();
	env_init(data, envp);
}

////////////////////////////minishell.c////////////////////////////////////


static char	*input_msg_init (t_data *data)
{
	char	*path_color;
	char	*err_color;
	char	*input_msg;
	char	path_dir[PATH_MAX];

	getcwd(path_dir, sizeof(path_dir));
	path_color = ft_strjoin_free (ft_strdup("\x1b[34m"), ft_strdup(path_dir));
	err_color = ft_strjoin_free(ft_strdup("\x1b[33m?"), ft_itoa(data->errnum));
	input_msg = ft_strjoin_free(ft_strjoin_free(path_color, err_color), ft_strdup("\x1b[34m $\x1b[0m "));
	// input_msg = ft_strjoin_free(ft_strjoin_free (ft_strdup("\x1b[34m"), ft_strdup(path_dir)), ft_strdup("$\x1b[0m "));
	if (!input_msg)
		input_msg = ft_strdup("minishell_input: ");
	return(input_msg);
}

static int	main_while (t_data *data)
{
	char	*input;
	char	*input_msg;

	input_msg = input_msg_init(data);
	input = readline(input_msg);
	free(input_msg);
	if (!input)
		return (1);
	if (!input[0])
	{
		free (input);
		return (0);
	}
	add_history(input);
	input_to_token(data, input);
	//err_check(data);//
	token_to_organize(data, &data->unorganized_token);

	// ** output: CORRECT **

	// printf("\noutput:\n"); // ** DEBUG ********************************************************************
	// print_group_list(data->grouped_token); // ** DEBUG ********************************************************************

	return(0);
}

void	free_cmd_history(t_data *data)
{
	if(data->unorganized_token.head)
	{
		free_token_list(data->unorganized_token.head);
		data->unorganized_token.head = 0;
		data->unorganized_token.tail = 0;
	}
	if(data->grouped_token)
	{
		free_group_list(data->grouped_token);
		data->grouped_token = 0;
	}
}

int main(int argc, char **argv, char **envp) 
{
	t_data	data;

	(void) argv;
	if (argc != 1)
		return (0);
	mns_init(&data, envp);
	while (1)
	{
		if(main_while(&data))
			break ;
		g_signal = 1;

		// **data->grouped_token: CORRECT **
		// printf("\nGROUP_TOKEN output:\n"); // ** DEBUG ********************************************************************
		// print_group_list(data.grouped_token); // ** DEBUG ******************************************************************

		first_execute(&data);
		g_signal = 0;
		free_cmd_history(&data);
	}
	printf ("exit\n");
	free_mns(&data);
	return (0);
}

////////////////////////////**DEBUG**////////////////////////////////////

// print env_init
	// for (i = 0; i < row; i++) {
	// 	printf("data->env[%d] = %s\n", i, data->env[i]);}

// print input
	// if (input) {
	// 	printf("You entered: %s\n", input);
	// 	free(input); 
	// }

// printf
	// printf("%s", "checked");