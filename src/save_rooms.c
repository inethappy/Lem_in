#include "lem_in.h"

void save_end_room(char *l, t_lem *lem)
{
	char **rm;
	
	if (lem->end)
        p_error("Only one end room please!");
	rm = ft_strsplit(l, ' ');
	if (rm[0][0] == '#' || rm[0][0] == 'L')
		return ;
	lem->end = ft_memalloc(sizeof(t_r));
	if (validation_data(lem, rm))
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
}

void save_start_room(char *l, t_lem *lem)
{
	char **rm;
	
	if (lem->start)
        p_error("Only one start room please!");
	rm = ft_strsplit(l, ' ');
	if (rm[0][0] == '#')
		return ;
	lem->start = ft_memalloc(sizeof(t_r));
	if (validation_data(lem, rm))
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
}

void save_rooms(char *l, t_lem *lem)
{
	char **rm;
	t_r *roo;
	
	rm = ft_strsplit(l, ' ');
	if (rm[0][0] == '#')
	{
		del_arr(rm);
		return ;
	}
	roo = ft_memalloc(sizeof(t_r));
	if (validation_data(lem, rm))
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
}
