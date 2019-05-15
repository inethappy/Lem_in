#include "lem_in.h"

int	validation_data(t_list *ptr, char **rm)
{
	t_r *var;
	int i;
	int j;

	i = 0;
	j = -1;
	while (++i < 3)
	{
		while (rm[i][++j])
			if (!ft_isdigit(rm[i][j]) && rm[i][j] != '-' && rm[i][j] != '+')
				p_error("Error! Not valid coordinate!");
		j = -1;
	}
	if (ft_strrchr(rm[0], '-'))
		p_error("Error! Not valid name!");
	while (ptr)
	{
		var = ptr->content;
		if (ft_strcmp(var->name, rm[0]) == 0)
			p_error("Error! The room names must not be repeated!");
		if (var->x == ft_atoi(rm[1]) && var->y == ft_atoi(rm[2]))
			p_error("Error! Room coordinates must be unique!");
		ptr = ptr->next;
	}
	return (1);
}

void save_inp(t_lem *lem, int fd)
{
	char *l;
	int fl;

	while (get_next_line(fd, &l))
	{
		if (l[0] == '\0')
			break ;
		ft_printf("%s\n", l);
		if (l[0] == '#' && l[1] == '#' && (ft_strcmp(l + 2, "start") == 0 
			|| ft_strcmp(l + 2, "end") == 0))
		{
			fl = ft_strstr(l, "start") ? 0 : 1;
			free(l);
			get_next_line(fd, &l);
			fl == 0 ? save_start_room(l, lem, fd) : save_end_room(l, lem, fd);
		}
		else if (ft_strchr(l, ' '))
			save_rooms(l, lem);
		else if (ft_strchr(l, '-'))
		{
			if (!save_links(l, lem, fd))
				break ;
		}
	}
	free(l);
}

void find_pathes(t_lem *lem)
{
	while (lem->ttl_rms--)
	{
		refresh_parents(lem);
		bfs(lem);
		save_path(lem);
	}
}

int main(void)
{
	t_lem *lem;
	int fd;

	fd = 0;
	lem = ft_memalloc(sizeof(t_lem));
	save_ants_number(fd, lem);    
	save_inp(lem, fd);
	if (!lem->start || !lem->end )
		p_error("Error! Should be start and end rooms.");
	count_start_links(lem);
	find_pathes(lem);
	push_ants(lem);
	system("leaks lem-in > leaks");
	return (0);
}
	


	// t_list *list;
	// t_list *path;
	// int i = 0;
	// int j = 0;
	// size_t ll = 0;
	// t_r *next_node;
	// path = lem->path;
	// while (path)
	// {
	// 	list = path->content;
	// 	printf("path %d\n", i);
	// 	while (list)
	// 	{
	// 		next_node = list->content;
	// 		ll = list->content_size;
	// 		printf("[%s] ", next_node->name);
	// 		j++;
	// 		list = list->next;
	// 	}
	// 	printf("all length = %zu\n", ll);
	// 	j = 0;
	// 	path = path->next;
	// 	i++;
	// }
