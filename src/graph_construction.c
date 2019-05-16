/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_construction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:26:31 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/05/16 10:26:32 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_existing_node(t_r *node, t_list *queue)
{
	t_list	*ptr;
	t_r		*ptr_tr;

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

void	bfs_recursieve(t_list *all, t_lem *lem, int step)
{
	t_r		*node;
	t_r		*node2;
	t_list	*l;
	int		i;

	i = lem->count;
	while (all)
	{
		node = all->content;
		if (node->lvl == (step - 1) && node != lem->start && node->lvl != -1)
		{
			l = node->links;
			while (l && (node2 = l->content))
			{
				if (node2->alrd == 0 && node2->lvl != -1
					&& (node2->parent = node)
					&& ++lem->count && (node2->lvl = step))
					node2->alrd = 1;
				l = l->next;
			}
		}
		all = all->next;
	}
	if (i < lem->count)
		bfs_recursieve(lem->all_rms, lem, ++step);
}

void	save_path(t_lem *lem)
{
	t_list	*list;
	int		next_node;

	next_node = 0;
	while (next_node >= 0)
	{
		lem->count = 1;
		list = search_path(lem, &next_node);
		if (next_node > 0)
		{
			list->content_size = lem->count;
			if (!lem->path)
				lem->path = ft_lstnew_new(list, lem->count);
			else
				ft_lstadd_end(lem->path, ft_lstnew_new(list, lem->count));
			break ;
		}
	}
	if (lem->path == NULL)
		p_error("No any valid path!");
}

void	bfs(t_lem *lem)
{
	t_list	*l;
	t_r		*node;
	int		step;

	step = 1;
	l = lem->end->links;
	while (l)
	{
		node = l->content;
		if (node->lvl > -1)
		{
			node->lvl = step;
			node->parent = lem->end;
			node->alrd = 1;
		}
		l = l->next;
	}
	bfs_recursieve(lem->all_rms, lem, ++step);
}
