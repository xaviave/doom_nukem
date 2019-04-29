/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 21:39:51 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 18:41:56 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/wolf.h"

t_cycle			*new_cycle(t_grid *grid, e_stack is_cycle)
{
	t_cycle		*cycle;

	if (!(cycle = (t_cycle*)ft_memalloc(sizeof(t_cycle))))
		return (0);
	cycle->next = is_cycle != 0 ? cycle : 0;
	cycle->prev = is_cycle != 0 ? cycle : 0;
	cycle->grid = grid;
	return (cycle);
}

void			cycle_destroy(t_cycle *cycle)
{
	grid_destroy(cycle->grid);
	ft_memdel((void**)&cycle);
	return ;
}

void			cycle_delall(t_cycle **board)
{
	t_cycle		*cur;
	
	cur = *board;
	while (cur)
	{
		cycle_destroy(cur);
		cur = cur->next;
		if (cur == *board)
			break;
	}
	cycle_destroy(*board);
	return ;
}

void			cycle_iter(t_cycle **board, void (*f)(t_cycle *elem))
{
	t_cycle		*cur;

	cur = *board;
	while (cur)
	{
		(*f)(cur);
		cur = cur->next;
		if (cur == *board)
			break;
	}
	return ;
}

int				cycle_index(t_cycle **board, t_cycle **marker)
{
	int			index;
	t_cycle		*cur;

	index = 0;
	cur = *board;
	while (cur)
	{
		index++;
		cur = cur->next;
		if (cur == *board || cur == *marker)
			break;
	}
	return (index);
}

void			cycle_delone(t_cycle **board, t_cycle **marker)
{
	t_cycle		*del;

	del = *marker;
	if (cycle_index(board, marker) > 1)
	{
		(*marker)->next->prev = (*marker)->prev;
		(*marker)->prev->next = (*marker)->next;
		*marker = (*marker)->prev;
		cycle_destroy(del);
	}
	return ;
}

void			cycle_insert(t_cycle **marker, t_cycle *new_cycle)
{
	new_cycle->prev = *marker;
	new_cycle->next = (*marker)->next;
	(*marker)->next->prev = new_cycle;
	(*marker)->next = new_cycle;
	marker = &new_cycle;
	return ;
}

void			cycle_draw(t_cycle **board, t_cycle **marker)
{
	int			color;
	t_cycle		*cur;

	cur = *board;
	while (cur)
	{
		if (*marker == cur)
			color = CLR_LAYER;
		else
			color = CLR_SHADOW;
		grid_draw(cur->grid, color);
		cur = cur->next;
		if (cur == *board)
			break;
	}
	return ;
}

int				cycle_detector(t_cycle *cycle)
{
	t_cycle		*slow;
	t_cycle		*fast;

	slow = cycle;
	fast = cycle;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow)
			return (1);
	}
	return (0);
}
