/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:27:10 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/05/16 10:27:13 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_buffers(char *l, char **rm)
{
	free(l);
	del_arr(rm);
}

int		check_digit(char *l)
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

void	count_start_links(t_lem *lem)
{
	t_list	*all;
	int		ants;

	ants = 0;
	all = lem->start->links;
	while (all)
	{
		lem->ttl_rms++;
		if (all->content == lem->end)
		{
			while (++ants <= lem->total)
				ft_printf("L%d-%s ", ants, lem->end->name);
			ft_printf("\n\x1B[1;35;10mTOTAL MOVES: %d\x1B[0;0;0m\n", 1);
			exit(0);
		}
		all = all->next;
	}
	if (!lem->ttl_rms)
		p_error("Error! No any valid path!");
}

void	save_ants_number(int fd, t_lem *lem)
{
	char *l;

	if (!get_next_line(fd, &l) || l[0] == '\0')
		p_error("Error! Not valid ants quantity!");
	if (l[0] == '#')
		l = skip_comment(l, fd, lem);
	if (!l || !check_digit(l) || ft_atoi(l) < 1 || ft_atoi(l) > 2147480)
		p_error("Error! Not valid ants quantity!");
	lem->total = ft_atoi(l);
	lem->input = ft_lstnew(l, ft_strlen(l));
	free(l);
}

t_list	*ft_lstnew_new(void *content, size_t content_size)
{
	t_list	*new;

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
