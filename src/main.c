#include "lem_in.h"

void	ft_lstadd_end(t_list *alst, t_list *new)
{
	t_list *list_ptr;

	list_ptr = alst;
	while (list_ptr->next != NULL)
		list_ptr = list_ptr->next;
	list_ptr->next = new;
}

int	p_error(char *s)
{
	ft_printf("%s\n", s);
	exit(0);
}

void del_arr(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

t_list	*ft_lstnew_new(t_r *content, size_t content_size)
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

void save_end_room(char *l, t_lem *lem)
{
	char **rm;

	rm = ft_strsplit(l, ' ');
	lem->end = ft_memalloc(sizeof(t_r));
	lem->end->name = ft_strdup(rm[0]);
	lem->end->x = ft_atoi(rm[1]);
	lem->end->y = ft_atoi(rm[2]);
	if (!lem->all_rms)
		lem->all_rms = ft_lstnew_new(lem->end, sizeof(t_r));
	else
		ft_lstadd_end(lem->all_rms, ft_lstnew_new(lem->end, sizeof(t_r)));
	del_arr(rm);
}

void save_start_room(char *l, t_lem *lem)
{
	char **rm;

	rm = ft_strsplit(l, ' ');
	lem->start = ft_memalloc(sizeof(t_r));
	lem->start->name = ft_strdup(rm[0]);
	lem->start->x = ft_atoi(rm[1]);
	lem->start->y = ft_atoi(rm[2]);
	if (!lem->all_rms)
		lem->all_rms = ft_lstnew_new(lem->start, sizeof(t_r));
	else
		ft_lstadd(&lem->all_rms, ft_lstnew_new(lem->start, sizeof(t_r))); // in begin
	del_arr(rm);
}

void save_rooms(char *l, t_lem *lem)
{
	char **rm;
	t_r *roo;

	rm = ft_strsplit(l, ' ');
	roo = ft_memalloc(sizeof(t_r));
	roo->name = ft_strdup(rm[0]);
	roo->x = ft_atoi(rm[1]);
	roo->y = ft_atoi(rm[2]);
	if (!lem->all_rms)
		lem->all_rms = ft_lstnew_new(roo, sizeof(t_r));
	else
		ft_lstadd_end(lem->all_rms, ft_lstnew_new(roo, sizeof(t_r)));
	del_arr(rm);
}

// int check_total(char *l, t_lem *lem)
// {
// 	int flag;
// 	int i;

// 	while (l[i])
// 	{
// 		if (!ft_isdigit(l[i]) && !ft_isprint(l))
// 	if (l[0] == '#' && l[1] == '#')
// 	return (flag);
// }

void save_links(char *l, t_lem *lem)
{
	char **rm;
	t_r *r1;
	t_r *r2;
	t_r *ptr;
	t_list *list;

	rm = ft_strsplit(l, '-');
	r1 = NULL;
	r2 = NULL;
	list = lem->all_rms;
	while (list)
	{
		ptr = list->content;
		if (ft_strcmp(ptr->name, rm[0]) == 0)
			r1 = ptr;
		if (ft_strcmp(ptr->name, rm[1]) == 0)
			r2 = ptr;
		list = list->next;
	}
	if (r1 == NULL || r2 == NULL)
		p_error("Wrong room name in links!");
	if (!r1->links)
		r1->links = ft_lstnew_new(r2, sizeof(t_r));
	else
		ft_lstadd_end(r1->links, ft_lstnew_new(r2, sizeof(t_r)));
	if (!r2->links)
		r2->links = ft_lstnew_new(r1, sizeof(t_r));
	else
		ft_lstadd_end(r2->links, ft_lstnew_new(r1, sizeof(t_r)));
	del_arr(rm);
}

void save_inp(t_lem *lem, int fd)
{
	char *l;
	t_r *ptr;
	int fl;

	// int i = 0;
	while (get_next_line(fd, &l))// && i < 9)// && (fl = check_total(l, lem)))
	{
		if (ft_atoi(l) && !ft_strchr(l, ' ') && !ft_strchr(l, '\t') && !ft_strchr(l, '-'))
			lem->total = ft_atoi(l);
		else if (ft_strchr(l, '-') && !ft_strchr((ft_strchr(l, '-') + 1), '-'))
			save_links(l, lem);
		else if (l[0] == '#' && l[1] == '#')
		{
			if (ft_strstr(l, "start") || ft_strstr(l, "end"))
				fl = ft_strstr(l, "start") ? 0 : 1;
			else
				p_error("Wrong name of start/end!");
			free(l);
			get_next_line(fd, &l);
			fl == 0 ? save_start_room(l, lem) : save_end_room(l, lem);
		}
		else if (ft_strchr(l, ' ')) //some validation please?
			save_rooms(l, lem);
		free(l);
		// i++;
	}
	free(l);

	while (lem->all_rms)
	{
		ptr = lem->all_rms->content;
		t_r *ptr2;
		while (ptr->links)
		{
			ptr2 = ptr->links->content;
			printf("start = %s, end = %s, lem->all_rms->name = %s, x = %d, total = %d, link to %s\n", lem->start->name, lem->end->name, ptr->name, ptr->x, lem->total, ptr2->name);
			ptr->links = ptr->links->next;
		}
		lem->all_rms = lem->all_rms->next;
	}
}

int main(int argc, char **argv)
{
	t_lem *lem;
	int fd;

	fd = open(argv[1], O_RDONLY);
	lem = ft_memalloc(sizeof(t_lem));
	if (argc == 2)
		save_inp(lem, fd);
	system("leaks lem-in > leaks");
	return (0);
}
