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
	t_r *link;
	t_l *links;
};

// struct	s_l
// {
// 	t_r *first;
// 	t_r *next;
// };

struct	s_lem
{
	int total;
	t_list *all_rms;
	char *start;
	char *end;
};

#endif
