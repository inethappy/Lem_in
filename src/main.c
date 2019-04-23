#include "lem_in.h"

void	ft_lstadd_end(t_list *alst, t_list *new)
{
	t_list *list_ptr;

	list_ptr = alst;
	while (list_ptr->next != NULL)
		list_ptr = list_ptr->next;
	list_ptr->next = new;
}

void del_arr(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
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
		lem->all_rms = ft_lstnew(roo, sizeof(t_r));
	else
		ft_lstadd_end(lem->all_rms, ft_lstnew(roo, sizeof(t_r)));
	free(roo);
	del_arr(rm);
}

void save_start_end(char *l, t_lem *lem)
{
	if (ft_strstr(l, "start"))
	{
		lem->start = ft_strnew(ft_str_len_n(l, ' '));
		ft_strncpy(lem->start, l, ft_str_len_n(l, ' '));
	}
	else if (ft_strstr(l, "end"))
	{
		lem->end = ft_strnew(ft_str_len_n(l, ' '));
		ft_strncpy(lem->end, l, ft_str_len_n(l, ' '));
	}
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
	t_r *ptr;
	t_r *p;
	char **rm;
	t_list *ptr2;
	t_list *pt;

	rm = ft_strsplit(l, '-');
	ptr2 = lem->all_rms;
	pt = lem->all_rms;

	// printf("all = %p\n", lem->all_rms);

	while (pt)
	{
		ptr = pt->content;
		if (ft_strcmp(ptr->name, rm[0]) == 0)
		{
			// printf("ptr->name %s\n", ptr->name);
			while (lem->all_rms)
			{
				p = lem->all_rms->content;
				// printf("p->name %s\n", p->name);
				if (ft_strcmp(p->name, rm[1]) == 0)
				{
					// printf("%s, \n", p->name);
					ptr->link = p;
					printf("ptr->name %s, ptr->link->name = %s\n", ptr->name, ptr->link->name);

				}
				lem->all_rms = lem->all_rms->next;
			}
		}
		lem->all_rms = lem->all_rms;
		pt = pt->next;
	}
	lem->all_rms = ptr2;
}

void save_inp(t_lem *lem, int fd)
{
	char *l;
	t_r *ptr;
	// int fl;

	while (get_next_line(fd, &l))// && (fl = check_total(l, lem)))
	{
		if (ft_atoi(l) && !ft_strchr(l, ' ') && !ft_strchr(l, '\t') && !ft_strchr(l, '-'))
			lem->total = ft_atoi(l);
		else if (ft_strchr(l, '-') && !ft_strchr((ft_strchr(l, '-') + 1), '-'))
			save_links(l, lem);
		else if (l[0] == '#' && l[1] == '#')
		{
			free(l);
			get_next_line(fd, &l);
			save_start_end(l, lem);
			save_rooms(l, lem);
		}
		else if (ft_strchr(l, ' ')) //some validation please?
			save_rooms(l, lem);
		free(l);
	}
	free(l);
	while (lem->all_rms)
	{
		ptr = lem->all_rms->content;
		printf("lem->all_rms->name = %s, x = %d, total = %d, link to %s\n", ptr->name, ptr->x, lem->total, ptr->link->name);
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
