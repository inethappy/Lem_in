#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ABS(Value) (((Value) < 0) ? -(Value) : (Value))

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
	int ant;
	t_r *parent;
	t_list *links;
};

struct	s_lem
{
	int total;
	int ttl_rms;
	t_list *all_rms;
	t_list *queue;
	t_list *path;
	t_r *start;
	t_r *end;
	int count;
};

void save_ants_number(int fd, t_lem *lem);
void save_end_room(char *l, t_lem *lem, int fd);
void save_start_room(char *l, t_lem *lem, int fd);
void save_rooms(char *l, t_lem *lem);
int save_links(char *l, t_lem *lem, int fd);
void save_inp(t_lem *lem, int fd);
int	validation_data(t_list *ptr, char **rm);
t_list	*ft_lstnew_new(void *content, size_t content_size);
void     link_if_list(t_r *r1, t_r *r2);
int check_digit(char *l);
void bfs(t_lem *lem);
void bfs_recursieve(t_list *all, t_lem *lem, int step);
int check_existing_node(t_r *node, t_list *queue);
void save_path(t_lem *lem);
t_list *search_path(t_lem *lem, int *next_node);
void count_start_links(t_lem *lem);
int refresh_parents(t_lem *lem);
int move_existing_ants(t_lem *lem, t_list *road);
int is_best_path(int ants, t_list *list, t_lem *lem);
void push_ants(t_lem *lem);
void	push_from_start(int *ants, t_list *list, t_lem *lem);



#endif
