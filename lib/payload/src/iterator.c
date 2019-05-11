/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   iterator.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/04 17:45:32 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 21:37:03 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/payload.h"

t_node				*new_iterator(t_payload *p)
{
	return (p->begin);
}

void				payload_next(t_payload *p, t_node **iterator)
{
	*iterator = (*iterator)->child;
	p->index++;
	return ;
}

void				payload_prev(t_payload *p, t_node **iterator)
{
	*iterator = (*iterator)->parent;
	p->index--;
	return ;
}

void				payload_iter(t_payload *p, void (*f)(void *content))
{
	node_iter(p->begin, f);
	return ;
}
