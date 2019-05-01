#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// # define ABS(Value) (((Value) < 0) ? -(Value) : (Value))

typedef struct	s_l		t_l;
typedef struct	s_r		t_r;
typedef struct	s_lem	t_lem;

struct	s_r
{
	char *name;
	int x;
	int y;
	int alrd;
	int lvl;
	t_r *parent;
	t_list *links;
};

struct	s_lem
{
	int total;
	t_list *all_rms;
	t_list *queue;
	t_list *path;
	t_r *start;
	t_r *end;
	int count;
};

void save_end_room(char *l, t_lem *lem);
void save_start_room(char *l, t_lem *lem);
void save_rooms(char *l, t_lem *lem);
void save_links(char *l, t_lem *lem);
void save_inp(t_lem *lem, int fd);
int	validation_data(t_lem *lem, char **rm);
t_list	*ft_lstnew_new(t_r *content, size_t content_size);
void     link_if_list(t_r *r1, t_r *r2, t_list *list, t_r *ptr);


// void bfs_recursieve(t_list *list, t_lem *lem, int step, t_r *pr);


#endif
