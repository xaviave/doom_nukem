/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shape.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 07:43:35 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 22:22:14 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

static void			destroy_shape_vertex(void *content)
{
	t_vertex		*vertex;

	vertex = (t_vertex*)content;
	ft_memdel((void**)&vertex);
	return ;
}

void				shape_destroy(t_shape *shape)
{
	payload_destroy(shape->vertex);
	ft_memdel((void**)&shape);
	return ;
}

t_shape				*new_shape(t_vertex *vertex)
{
	t_shape			*shape;

	if (!(shape = (t_shape*)ft_memalloc(sizeof(t_shape))))
		return (0);
	shape->vertex = new_payload((void*)vertex, &destroy_shape_vertex);
	shape->iterator = new_iterator(shape->vertex);
	return (shape);
}
