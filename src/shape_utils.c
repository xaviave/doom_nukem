/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shape_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 15:36:06 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 00:25:33 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

void				shape_draw(t_shape *shape, t_image *img, int pipet)
{
	t_node			*cur;

	cur = shape->vertex->begin;
	vertex_draw(img, (t_vertex*)cur->content, CLR_VERTEX_1);
	cur = cur->child;
	while (cur)
	{
		if (cur->parent)
			image_line(img, (t_vertex*)cur->content,
			(t_vertex*)cur->parent->content, pipet);
		vertex_draw(img, (t_vertex*)cur->content, CLR_VERTEX);
		cur = cur->child;
	}
	return ;
}

void				shape_add(t_shape *s, t_vertex *v)
{
	payload_add(s->vertex, s->iterator, (void*)v);
	payload_next(s->vertex, &s->iterator);
	return ;
}

void				shape_remove(t_shape *s)
{
	payload_remove(s->vertex, &s->iterator);
	return ;
}

t_vertex			*shape_has_vertex(t_shape *s, int x, int y)
{
	t_vertex	*vcur;
	t_node		*cur;

	cur = s->vertex->begin;
	while (cur)
	{
		vcur = (t_vertex*)cur->content;
		if (((x > vcur->x - V_BOX) && (x < vcur->x + V_BOX)) &&
			((y > vcur->y - V_BOX) && (y < vcur->y + V_BOX)))
			return ((t_vertex*)cur->content);
		cur = cur->child;
	}
	return (0);
}
