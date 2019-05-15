#include "lem_in.h"

void save_end_room(char *l, t_lem *lem, int fd)
{
	char **rm;
	(void)fd;

	rm = NULL;	
	if (lem->end)
		p_error("Only one end room please!");
	ft_printf("%s\n", l);
	if (l[0] == '#')
	{
		while (l && l[0] == '#')
		{
			free(l);
			get_next_line(fd, &l);
		}
		ft_printf("%s\n", l);
	}
	if (l[0] == '\0' || l[0] == 'L' || !(rm = ft_strsplit(l, ' ')) || !rm[1] || !rm[2])
		p_error("No end room!");
	lem->end = ft_memalloc(sizeof(t_r));
	if (validation_data(lem->all_rms, rm))
	{
		lem->end->name = ft_strdup(rm[0]);
		lem->end->x = ft_atoi(rm[1]);
		lem->end->y = ft_atoi(rm[2]);
	}
	if (!lem->all_rms)
		lem->all_rms = ft_lstnew_new(lem->end, sizeof(t_r));
	else
		ft_lstadd(&lem->all_rms, ft_lstnew_new(lem->end, sizeof(t_r)));
	del_arr(rm);
	free(l);
}

void save_start_room(char *l, t_lem *lem, int fd)
{
	char **rm;

	rm = NULL;	
	if (lem->start)
		p_error("Only one start room please!");
	ft_printf("%s\n", l);
	if (l[0] == '#')
	{
		while (l && l[0] == '#')
		{
			free(l);
			get_next_line(fd, &l);
		}
		ft_printf("%s\n", l);
	}
	rm = ft_strsplit(l, ' ');
	if (l[0] == '\0' || l[0] == 'L' || !rm || !rm[1] || !rm[2])
		p_error("No start room!");
	lem->start = ft_memalloc(sizeof(t_r));
	if (validation_data(lem->all_rms, rm))
	{
		lem->start->name = ft_strdup(rm[0]);
		lem->start->x = ft_atoi(rm[1]);
		lem->start->y = ft_atoi(rm[2]);
	}
	if (!lem->all_rms)
		lem->all_rms = ft_lstnew_new(lem->start, sizeof(t_r));
	else
		ft_lstadd_end(lem->all_rms, ft_lstnew_new(lem->start, sizeof(t_r)));
	del_arr(rm);
	free(l);
}

void save_rooms(char *l, t_lem *lem)
{
	char **rm;
	t_r *roo;
	
	if (l[0] == 'L' || !(rm = ft_strsplit(l, ' ')) || !rm[1] || !rm[2])
		p_error("Invalid room!");
	if (l[0] == '#')
	{
		free(l);
		del_arr(rm);
		return ;
	}
	roo = ft_memalloc(sizeof(t_r));
	if (validation_data(lem->all_rms, rm))
	{
		roo->name = ft_strdup(rm[0]);
		roo->x = ft_atoi(rm[1]);
		roo->y = ft_atoi(rm[2]);
	}
	if (!lem->all_rms)
		lem->all_rms = ft_lstnew_new(roo, sizeof(t_r));
	else
		ft_lstadd_end(lem->all_rms, ft_lstnew_new(roo, sizeof(t_r)));
	del_arr(rm);
	free(l);
}
