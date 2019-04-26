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
		ft_lstadd_end(lem->all_rms, ft_lstnew_new(lem->end, sizeof(t_r)));
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
		ft_lstadd(&lem->all_rms, ft_lstnew_new(lem->start, sizeof(t_r))); // in begin
	del_arr(rm);
}

void save_rooms(char *l, t_lem *lem)
{
	char **rm;
	t_r *roo;
	
	rm = ft_strsplit(l, ' ');
	if (rm[0][0] == '#')
		return ;
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

void     link_if_list(t_r *r1, t_r *r2, t_list *list, t_r *ptr)
{
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
	if (r2->links)
    {
        list = r2->links;
        while (list)
        {
            ptr = list->content;
            if (ft_strcmp(ptr->name, r1->name) == 0)
                p_error("Links should not repeaeted!");
            list = list->next;
        }
		ft_lstadd_end(r2->links, ft_lstnew_new(r1, sizeof(t_r)));
    }
}

void save_links(char *l, t_lem *lem)
{
	char **rm;
	t_r *r1;
	t_r *r2;
	t_r *ptr;
	t_list *list;

	rm = ft_strsplit(l, '-');
	if (rm[0][0] == '#')
		return ;
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
	if (r1 == NULL || r2 == NULL || rm[2])
		p_error("Wrong room name in links!");
    link_if_list(r1, r2, list, ptr);
    if (!r1->links)
		r1->links = ft_lstnew_new(r2, sizeof(t_r));
    if (!r2->links)
		r2->links = ft_lstnew_new(r1, sizeof(t_r));
	del_arr(rm);
}