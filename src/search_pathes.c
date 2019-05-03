#include "lem_in.h"

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

void bfs_recursieve(t_list *all, t_lem *lem, int step)
{
	t_r *node;
	t_r *node2;
	t_list *l;
	int i;

	i = lem->count;

	while (all)
	{
		node = all->content;
		if (node->lvl == (step - 1))
		{
			l = node->links;
			while (l)
			{
			++lem->count;

				node2 = l->content;
				node2->lvl = (node2->lvl == 0) ? step : node2->lvl;
				if (check_existing_node(node2, lem->queue) && (node2->parent = node))
					ft_lstadd_end(lem->queue, ft_lstnew(node2, sizeof(t_r)));
				l = l->next;
			}
		}
		// printf("step %d, %s %d, %d\n", step, node2->name, node2->lvl, lem->count);
		all = all->next;
	}
	if (lem->count < lem->ttl_rms && i < lem->count)
		bfs_recursieve(lem->all_rms, lem, ++step);
}

int search_path(t_lem *lem, t_list **ptr)
{
	t_list *list;
	t_list *list2;
	t_r *res;
	t_r *res3;
	t_r *res2;
    int fl;

    fl = 0;
	list = lem->start->links;
	while (list)
	{
		res = list->content;
		if (res->lvl == 0)
			res->lvl = -1;
		list = list->next;
	}
	list = lem->start->links;
	list2 = lem->start->links;
    res = list->content;
	while (list2)
	{
		while (list)
		{
			if (list->next)
			{
				list = list->next;
				res2 = list->content;
				if ((res->lvl > res2->lvl && res2->lvl != -1) || (res->lvl == -1 && res2->lvl != -1))
				{
					if (fl == 0)
					{
						res3 = res2;
						fl = 1;
					}
					else
						res3 = ((res3->lvl > res2->lvl || res3->lvl == -1) && res2->lvl > 0) ? res2 : res3;
				}
				else
				{
					if (fl == 0)
					{
						res3 = res;
						fl = 1;
					}
				}
			}
			else
				list = list->next;
				printf("res = %s %d, res2 = %s %d, res3 = %s %d\n", res->name, res->lvl, res2->name, res2->lvl, res3->name, res3->lvl);
			
			res = res2;
		}
		fl = 0;
		list = lem->start->links;
		res = list->content;
		list2 = list2->next;
	}
	printf("%d\n", res3->lvl);
    if (res3->lvl == -1)
        return (-1);
	list = ft_lstnew_new(res3, sizeof(t_r));
	res3->lvl = -1;
	while (res3 != lem->end)
	{
		res3 = res3->parent;
		printf("tut %d\n", res3->lvl);
		if (res3->lvl == -1)
			return (0);
		printf("tut tyt %d\n", res3->lvl);

		res3->lvl = -1;
		ft_lstadd_end(list, ft_lstnew_new(res3, sizeof(t_r)));

		// if (ft_strcmp(res3->name, lem->end->name) == 0)
		// 	break ;
	}
	*ptr = list;
	return (1);
}

void save_all_pathes(t_lem *lem)
{
	t_list *list;
	int res;

	res = search_path(lem, &list);
		printf("return %d\n", res);
	
	if (list == NULL)
		p_error("No any valid path!");
	lem->path = ft_lstnew_new(list, sizeof(t_list));
	while ((res = search_path(lem, &list)))
	{
		printf("return %d\n", res);
		if (res > 0)
			ft_lstadd_end(lem->path, ft_lstnew_new(list, sizeof(t_list)));
	}
}

void bfs(t_lem *lem)
{
	t_list *l;
	t_r *node;
	int step;
	t_list *list;

	step = 1;
	lem->queue = ft_lstnew(lem->end, sizeof(t_r));
	l = lem->end->links;
	
	lem->ttl_rms++;
	while (l)
	{
		node = l->content;
		node->lvl = step;
		node->parent = lem->end;
		lem->ttl_rms++;
		ft_lstadd_end(lem->queue, ft_lstnew(node, sizeof(t_r)));
		l = l->next;
	}
	bfs_recursieve(lem->all_rms, lem, ++step);
	save_all_pathes(lem);
	// l = lem->start->links;
	// while (l)
	// {
	// 	node = l->content;
	// 	printf("%s %d\n", node->name, node->lvl);
	// 	l = l->next;
	// }
	
	// otladka
	t_list *path;
	int i = 0;
	t_r *res;
	path = lem->path;
	while (path)
	{
		list = path->content;
		while (list)
		{
			res = list->content;
			printf("%d %s\n", i, res->name);
			list = list->next;
		}
		path = path->next;
		i++;
	}
	// otladka queue
	// t_r *ptr;
	// list = lem->all_rms;
	// while (list)
	// {
	// 	ptr = list->content;
	// 	printf("queue %s, lvl = %d, ", ptr->name, ptr->lvl);
	// 	if (ptr->parent)
	// 		 printf("prnt = %s", ptr->parent->name);
	// 	printf("\n");
	// 	list = list->next;
	// }
}
