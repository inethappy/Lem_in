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
				if (node2->alrd == 0 && (node2->parent = node))
					node2->alrd = 1;
				l = l->next;
			}
		}
		// printf("step %d, %s %d, %d\n", step, node2->name, node2->lvl, lem->count);
		all = all->next;
	}
	if (lem->count < lem->ttl_rms && i < lem->count)
		bfs_recursieve(lem->all_rms, lem, ++step);
}

void save_all_pathes(t_lem *lem)
{
	t_list *list;
	int next_node;

	// next_node = search_path(lem, &list);
	// if (list == NULL || next_node == -1)
	// 	p_error("No any valid path!");
	// lem->path = ft_lstnew_new(list, sizeof(t_list));
	while ((list = search_path(lem, &next_node)))
	{
		if (next_node > 0)
		{
			if (!lem->path)
				lem->path = ft_lstnew_new(list, sizeof(t_list));
			else
				ft_lstadd_end(lem->path, ft_lstnew_new(list, sizeof(t_list)));
		}
	}
	if (lem->path == NULL)
		p_error("No any valid path!");
}

void bfs(t_lem *lem)
{
	t_list *l;
	t_r *node;
	int step;

	step = 1;
	l = lem->end->links;
	lem->ttl_rms++;
	while (l)
	{
		node = l->content;
		node->lvl = step;
		node->parent = lem->end;
		node->alrd = 1;
		lem->ttl_rms++;
		l = l->next;
	}
	bfs_recursieve(lem->all_rms, lem, ++step);
    save_all_pathes(lem);
	
	
	// otladka path
	t_list *list;
	t_list *path;
	int i = 0;
	int j = 0;
	t_r *next_node;
	path = lem->path;
	while (path)
	{
		list = path->content;
		while (list)
		{
			next_node = list->content;
			printf("%d %d %s\n", i, j, next_node->name);
			j++;
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
