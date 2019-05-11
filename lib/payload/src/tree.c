/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tree.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 11:48:10 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 05:03:42 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/payload.h"

void			tree_destroy(t_node *tree, void (*del)(void *))
{
	while (tree)
	{
		node_destroy(tree, del);
		tree = tree->child;
	}
	return ;
}

int				cycle_detector(t_node *begin)
{
	t_node		*slow;
	t_node		*fast;

	slow = begin;
	fast = begin;
	while (fast && fast->child)
	{
		slow = slow->child;
		fast = fast->child->child;
		if (fast == slow)
			return (1);
	}
	return (0);
}
