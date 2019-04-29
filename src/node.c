/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   node.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 19:28:47 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 19:44:47 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/wolf.h"

t_node			*new_node(void *content, size_t n)
{
	t_node		*node;

	if (!(node = (t_node*)ft_memalloc(sizeof(t_node))))
		return (0);
	if (!(node->content = (void *)ft_memalloc(sizeof(void)*n)))
		return (node);
	ft_memcpy(node->content, content, n);
	node->size = n;
	return (node);
}

void			node_destroy(t_node **node, void (*del)(void *, size_t))
{
	(*del)((*node)->content, (*node)->size);
	ft_memdel((void **)node);
	return ;
}

void			node_add(t_node **)