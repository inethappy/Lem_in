#include "lem_in.h"

t_list	*ft_lstnew_new(t_r *content, size_t content_size)
{
	t_list *new;
	new = NULL;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = content;
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}

int	validation_data(t_lem *lem, char **rm)
{
	t_list *ptr;
	t_r *var;
	int i;
	int j;

	ptr = lem->all_rms;
	i = 0;
	j = -1;
	while (++i < 3)
	{
		while (rm[i][++j])
			if (!ft_isdigit(rm[i][j]))
				p_error("Not valid coordinate!");
		j = -1;
	}
	while (ptr)
	{
		var = ptr->content;
		if (ft_strcmp(var->name, rm[0]) == 0)
			p_error("The room names must not be repeated!");
		if (var->x == ft_atoi(rm[1]) && var->y == ft_atoi(rm[2]))
			p_error("Room coordinates must be unique!");
		ptr = ptr->next;
	}
	return (1);
}

int check_digit(char *l)
{
	int i;

	i = 0;
	while (l[i])
	{
		if (!ft_isdigit(l[i]))
			return (0);
		i++;
	}
	return (1);
}

void save_inp(t_lem *lem, int fd)
{
	char *l;
	// t_r *ptr;
	int fl;

	// int i = 0;
	l = NULL;
    get_next_line(fd, &l);
    if (!check_digit(l) || ft_atoi(l) == 0)
        p_error("Error! Not valid ants quantity!");
    lem->total = ft_atoi(l);
    free(l);
	while (get_next_line(fd, &l))// && i < 9)
	{
		if (l[0] == '#' && l[1] == '#' && (ft_strcmp(l + 2, "start") == 0 || ft_strcmp(l + 2, "end") == 0))
		{
			fl = ft_strstr(l, "start") ? 0 : 1;
			free(l);
			get_next_line(fd, &l);
			fl == 0 ? save_start_room(l, lem) : save_end_room(l, lem);
		}
		else if (ft_strchr(l, '-'))
			save_links(l, lem);
		else if (ft_strchr(l, ' '))
			save_rooms(l, lem);
		free(l);
		// i++;
	}
	free(l);

	// while (lem->all_rms)
	// {
	// 	ptr = lem->all_rms->content;
	// 	t_r *ptr2;
	// 	while (ptr->links)
	// 	{
	// 		ptr2 = ptr->links->content;
	// 		printf("start = %s, end = %s, lem->all_rms->name = %s, x = %d, y = %d, total = %d, link to %s\n", lem->start->name, lem->end->name, ptr->name, ptr->x, ptr->y, lem->total, ptr2->name);
	// 		ptr->links = ptr->links->next;
	// 	}
	// 	lem->all_rms = lem->all_rms->next;
	// }
}

int check_existing_node(t_r *node, t_list *queue)
{
	t_list *ptr;
	t_r *ptr_tr;

	ptr = queue;
	while (ptr)
	{
		ptr_tr = ptr->content;
        if (ft_strcmp(ptr_tr->name, node->name) == 0)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

void bfs(t_lem *lem)
{
	t_r *ptr;
	t_list *list;
	t_list *b_list;
	int fl;

	fl = 0;
	ptr = NULL;
	b_list = lem->all_rms;
	while (b_list)
	{
		ptr = b_list->content;
		if (fl == 0)
		{
			lem->queue = ft_lstnew(ptr, sizeof(t_r));
			fl = 1;
		}
		ptr->alrd = 1;
		list = ptr->links;
		while (list)
		{
			ptr = list->content;
			if (check_existing_node(ptr, lem->queue))
				ft_lstadd_end(lem->queue, ft_lstnew(ptr, sizeof(t_r)));
			ptr->alrd = 1;
			list = list->next;
		}
		b_list = b_list->next;
	}
	
	list = lem->queue;
	while (list)
	{
		ptr = list->content;
		printf("tit %s\n", ptr->name);
		list = list->next;
	}
}

int main(int argc, char **argv)
{
	t_lem *lem;
	int fd;

	fd = open(argv[1], O_RDONLY);
	lem = ft_memalloc(sizeof(t_lem));
	if (argc == 2)
		save_inp(lem, fd);
	bfs(lem);
	system("leaks lem-in > leaks");
	return (0);
}
