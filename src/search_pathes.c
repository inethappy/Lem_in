#include "lem_in.h"

void	block_not_valid_pathes(t_lem *lem)
{
	t_list *list;
	t_r	*next_node;

	list = lem->start->links;
	while (list)
	{
		next_node = list->content;
		if (next_node->lvl == 0)
			next_node->lvl = -1;
		list = list->next;
	}
}

void	next_node_levels( t_r *ptr2, t_r *next_node2, t_r **ptr, int *fl)
{
	t_r *pointer;

	pointer = *ptr;
	if (((ptr2->lvl >= next_node2->lvl) || (ptr2->lvl == -1)) && next_node2->lvl != -1)
	{
		if (*fl == 0 && (pointer = next_node2))
			*fl = 1;
		else
			pointer = (((pointer->lvl >= next_node2->lvl) || pointer->lvl == -1) && next_node2->lvl > 0)
				 ? next_node2 : pointer;
	}
	else
		if (*fl == 0 && (pointer = ptr2))
			*fl = 1;
	*ptr = pointer;
}

void search_smallest_level(t_r **next_node, t_list **l, t_r **result, int *fl)
{
	t_r *ptr;
	t_r *ptr2;
	t_r *next_node2;
	t_list *list;
	int ret;

	ret = 1;
	ptr2 = *next_node;
	ptr = *result;
	list = *l;
	if (list->next)
	{
		list = list->next;
		next_node2 = list->content;
		next_node_levels(ptr2, next_node2, &ptr, fl);
		ptr2 = next_node2;
		ret = 0;
	}
	else 
		ptr = (ptr) ? ptr : ptr2;
	*result = ptr;
	if (ret == 1)
		list = list->next;
	*l = list;
}

t_r *search_smallest_path(t_lem *lem)
{
	t_list *list;
	t_r *next_node;
	t_r *result;
	int fl = 0;

	if (!lem->start->links)
		p_error("No any valid path!");
	list = lem->start->links;
	lem->queue = lem->start->links;
    next_node = list->content;
	result = NULL;
	while (lem->queue)
	{
		while (list)
			search_smallest_level(&next_node, &list, &result, &fl);
		fl = 0;
		list = lem->start->links;
		next_node = list->content;
		lem->queue = lem->queue->next;
	}
	return result;
}

void block_path(t_list *path, t_lem *lem)
{
	t_r *node;

	while (path)
	{
		node = path->content;
		if (node != lem->end)
			node->lvl = 0;
		path = path->next;
	}
}

t_list *search_path(t_lem *lem, int *next_node)
{
	t_list *list;
	t_r *result = NULL;
	
	block_not_valid_pathes(lem);
	result = search_smallest_path(lem);
	if (!result || result->lvl == -1)
	{
		*next_node = -1;
        return (NULL);
	}
	lem->count = 1;
	result->lvl = -1;
	list = ft_lstnew_new(result, lem->count);
	while (result != lem->end)
	{
		result = result->parent;
		if (result->lvl == -1)
		{
			block_path(list, lem);
			*next_node = 0;
			free(list);
			return (NULL);
		}
		ft_lstadd_end(list, ft_lstnew_new(result, ++lem->count));
		if (result != lem->end)
			result->lvl = -1;
	}
	*next_node = 1;
	return (list);
}