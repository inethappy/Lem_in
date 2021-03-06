/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:26:45 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/05/16 10:26:49 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	link_if_list(t_r *r1, t_r *r2)
{
	t_list	*list;
	t_r		*ptr;

	if (r1->links)
	{
		list = r1->links;
		while (list)
		{
			ptr = list->content;
			if (ft_strcmp(ptr->name, r2->name) == 0)
				p_error("Links should not repeaeted!");
			list = list->next;
		}
		ft_lstadd_end(r1->links, ft_lstnew_new(r2, sizeof(t_r)));
	}
}

int		search_linked_rooms(char **rm, t_r **r1, t_r **r2, t_lem *lem)
{
	t_list	*list;
	t_r		*ptr;

	list = lem->all_rms;
	while (list)
	{
		ptr = list->content;
		if (ft_strcmp(ptr->name, rm[0]) == 0)
			*r1 = ptr;
		if (ft_strcmp(ptr->name, rm[1]) == 0)
			*r2 = ptr;
		list = list->next;
	}
	if (*r1 == NULL || *r2 == NULL || rm[2])
		return (0);
	return (1);
}

int		save_links(char *l, t_lem *lem)
{
	char	**rm;
	t_r		*r1;
	t_r		*r2;

	r1 = NULL;
	r2 = NULL;
	if (l[0] == '#')
	{
		free(l);
		return (1);
	}
	rm = ft_strsplit(l, '-');
	if (!rm[1] || !search_linked_rooms(rm, &r1, &r2, lem) || l[0] == '-')
	{
		clean_buffers(l, rm);
		return (0);
	}
	link_if_list(r1, r2);
	link_if_list(r2, r1);
	if (!r1->links)
		r1->links = ft_lstnew_new(r2, sizeof(t_r));
	if (!r2->links)
		r2->links = ft_lstnew_new(r1, sizeof(t_r));
	clean_buffers(l, rm);
	return (2);
}

int		handle_links(char *l, t_lem *lem, int fd)
{
	int	a;

	if ((a = save_links(l, lem)) < 2)
		return (a);
	while (get_next_line(fd, &l))
	{
		if (l[0] == '\0')
			return (0);
		ft_lstadd_end(lem->input, ft_lstnew(l, ft_strlen(l)));
		if ((a = save_links(l, lem)) < 2)
			return (a);
	}
	return (1);
}
