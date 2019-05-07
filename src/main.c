#include "lem_in.h"

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

void save_inp(t_lem *lem, int fd)
{
	char *l;
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

	// t_r *ptr;
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

int main(int argc, char **argv)
{
	t_lem *lem;
	int fd;

	fd = open(argv[1], O_RDONLY);
	lem = ft_memalloc(sizeof(t_lem));
	if (argc == 2)
		save_inp(lem, fd);
	count_rooms(lem);
	bfs(lem);
	
	system("leaks lem-in > leaks");
	return (0);
}
