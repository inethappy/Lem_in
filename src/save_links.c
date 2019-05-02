#include "lem_in.h"

void     link_if_list(t_r *r1, t_r *r2)
{
	t_list *list;
	t_r *ptr;

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

void search_linked_rooms(char **rm, t_r **r1, t_r **r2, t_lem *lem)
{
	t_list *list;
	t_r *ptr;

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
		p_error("Wrong room name in links!");
}

void save_links(char *l, t_lem *lem)
{
	char **rm;
	t_r *r1;
	t_r *r2;

	r1 = NULL;
	r2 = NULL;
	rm = ft_strsplit(l, '-');
	if (rm[0][0] == '#')
		return ;
	search_linked_rooms(rm, &r1, &r2, lem);
    link_if_list(r1, r2);
    link_if_list(r2, r1);
    if (!r1->links)
		r1->links = ft_lstnew_new(r2, sizeof(t_r));
    if (!r2->links)
		r2->links = ft_lstnew_new(r1, sizeof(t_r));
	del_arr(rm);
}