#ifndef _TEST_H
#define _TEST_H

#include "../libft/inc/libft.h"
# include <stdint.h>
# include <math.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct 		s_secret
{
	char			*msg;
}					t_secret;

typedef struct		s_node
{
	void			*content;
	struct s_node	*parent;
	struct s_node	*child;
}					t_node;

typedef struct		s_payload
{
	int				n;
	int				index;
	t_node			*begin;
	void 			(*destroy)(void *elem);
}					t_payload;

t_payload			*new_payload(void *content, void (*destroy)(void *elem));
void				payload_destroy(t_payload *p);
void				payload_add(t_payload *p, t_node *iterator, void *content);
void				payload_remove(t_payload *p, t_node **iterator);
int					payload_size(t_payload *p);

t_node				*new_iterator(t_payload *p);
void				payload_next(t_payload *p, t_node **iterator);
void				payload_prev(t_payload *p, t_node **iterator);
void				payload_iter(t_payload *p, void (*f)(void *content));

void				tree_destroy(t_node *tree, void (*del)(void *));
int					cycle_detector(t_node *begin);

t_node				*new_node(void *content);
void				node_destroy(t_node *node, void (*del)(void *));
void				node_insert(t_node *iterator, t_node *new);
void				node_remove(t_node *iterator, void (*del)(void *));
void				node_iter(t_node *iterator, void (*f)(void *content));

#endif