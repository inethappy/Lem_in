#include "lem_in.h"

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

void count_start_links(t_lem *lem)
{
	t_list *all;
	int ants;
	
	ants = 0;
	all = lem->start->links;
	while (all)
	{
		lem->ttl_rms++;
		if (all->content == lem->end)
		{
			while (++ants <= lem->total)
				ft_printf("L%d-%s ", ants, lem->end->name);
			ft_printf("\nITOGO 1\n");
			exit(0);
		}
		all = all->next;
	}
	if (!lem->ttl_rms)
        p_error("Error! No any valid path!");
}

void save_ants_number(int fd, t_lem *lem)
{
	char *l;
	get_next_line(fd, &l);
    if (!check_digit(l) || ft_atoi(l) < 1 || ft_atoi(l) > 2147480)
        p_error("Error! Not valid ants quantity!");
    lem->total = ft_atoi(l);
	ft_printf("%s\n", l);
    free(l);
}

t_list	*ft_lstnew_new(void *content, size_t content_size)
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