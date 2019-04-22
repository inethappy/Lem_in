#include "lem_in.h"

void	ft_lstadd_end(t_list *alst, t_list *new)
{
	t_list *list_ptr;

	list_ptr = alst;
	while (list_ptr->next != NULL)
		list_ptr = list_ptr->next;
	list_ptr->next = new;
}

void save_inp(t_lem *lem, int fd)
{
	char *l;
	char **rm;
	// t_list *list;
	t_r *roo;
			t_r *ptr;

	// ft_lstadd_end(mlx->read->first, ft_lstnew(l, ft_strlen(l)));

	while (get_next_line(fd, &l))
	{

		if (ft_strchr(l, ' ')) //some validation please?
		{
			rm = ft_strsplit(l, ' ');
			roo = ft_memalloc(sizeof(t_r));
			roo->name = ft_strdup(rm[0]);
			roo->x = ft_atoi(rm[1]);
			roo->y = ft_atoi(rm[2]);
			if (!lem->all_rms)
				lem->all_rms = ft_lstnew(roo, sizeof(t_r));
			else
				ft_lstadd_end(lem->all_rms, ft_lstnew(roo, sizeof(t_r)));
		// printf("prost: lem->start = %s, roo->name = %s\n", lem->start, roo->name);

			free(roo);
			free(rm);
		}
		else if (l[0] == '#' && l[0] == '#')
		{
			if (ft_strstr(l, "start"))
			{
				free(l);
				get_next_line(fd, &l);
				rm = ft_strsplit(l, ' ');
				lem->start = ft_strdup(rm[0]);
				roo = ft_memalloc(sizeof(t_r));
				roo->name = ft_strdup(rm[0]);
				roo->x = ft_atoi(rm[1]);
				roo->y = ft_atoi(rm[2]);
				if (!lem->all_rms)
					lem->all_rms = ft_lstnew(roo, sizeof(t_r));
				else
					ft_lstadd_end(lem->all_rms, ft_lstnew(roo, sizeof(t_r)));
		// printf("start: lem->start = %s, roo->name = %s\n", lem->start, roo->name);

				free(roo);
				free(rm);

				// lem->rooms = ft_memalloc(sizeof(t_r));
				// lem->rooms->name = ft_strdup(lem->start);
				// lem->rooms->x = ft_atoi(rm[1]);
				// lem->rooms->y = ft_atoi(rm[2]);
			}
		}
		while (lem->all_rms)
		{
			ptr = lem->all_rms->content;
			printf("prost: lem->all_rms = %s, x = %d\n", ptr->name, ptr->x);
			lem->all_rms = lem->all_rms->next;
		}

		// printf("lem->start = %s, lem->all_rms->content->name = %s", lem->start, lem->all_rms->content->name);

	}
				// printf("lem->start = %s, lem->rooms->name = %s", lem->start, lem->rooms->name);

}

int main(int argc, char **argv)
{
	t_lem *lem;
	int fd;

	fd = open(argv[1], O_RDONLY);
	lem = ft_memalloc(sizeof(t_lem));
	if (argc == 2)
		save_inp(lem, fd);
	return (0);
}
