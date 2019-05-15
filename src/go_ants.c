#include "lem_in.h"

int refresh_parents(t_lem *lem)
{
	t_r *node;
	t_list *list;
	int i;

	i = 0;
	list = lem->all_rms;	
	while (list)
	{
		node = list->content;
		if (node->lvl > 0 && node != lem->end && node != lem->start)
		{
			++i;
			node->alrd = 0;
			node->lvl = 0;
		}
		list = list->next;
	}
	if (i == 0)
		return (0);
	return (1);
}

int move_existing_ants(t_lem *lem, t_list *road)
{
	t_r *room;
	int res;
    int fl;
	int ant;	
	t_list *cur;

	ant = 1;
	res = 0;
	while (ant <= lem->total)
	{
        fl = 0;
		cur = road;
		while (cur && (room = cur->content))
		{
			if (room->ant == ant && room != lem->end && ++fl && ++res)
			{
				ft_printf("L%d-%s ", room->ant, room->parent->name);
				room->ant = 0;
				room->parent->ant = ant++;
			}
			cur = cur->next;
		}
		ant = (fl == 0) ? ++ant : ant;
	}
	return (res);
}

int is_best_path(int ants, t_list *list, t_lem *lem)
{
	t_list *path;
	int res;

	res = 0;
	path = lem->path;
	while (path)
	{
		if (path == list)
			break;
		res += list->content_size - path->content_size;
		path = path->next;
	}
	if (ants > res)
		return (1);
	return (0);
}

void	push_from_start(int *ants, t_list *list, t_lem *lem)
{
	t_list *ptr;
	t_r *room;

	if (is_best_path(*ants, list, lem))
	{
		ptr = list->content;
		room = ptr->content;
		ft_printf("L%d-%s ", ABS(*ants - lem->total - 1), room->name);
		room->ant = ABS(*ants - lem->total - 1);
		*ants -= 1;
	}
}

void push_ants(t_lem *lem)
{
	t_list *list;
	int ants;
	int flag = 1;

	ants = lem->total;
	list = lem->path;
	lem->count = 0;
	while (ants >= 0)
	{
		while (list)
		{
			flag += move_existing_ants(lem, list->content);
			if (ants > 0)
				push_from_start(&ants, list, lem);
			list = list->next;
		}
		if (!flag || ants == lem->total)
			break ;
		ft_printf("\n");
		lem->count++;
		flag = 0;
		list = lem->path;
	}
	ft_printf("ITOGO %d\n", lem->count);
}