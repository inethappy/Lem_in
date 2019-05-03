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

void count_rooms(t_lem *lem)
{
	t_list *all;

	all = lem->all_rms;
	while (all)
	{
		lem->ttl_rms++;
		all = all->next;
	}
	printf("%d\n", lem->ttl_rms);
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