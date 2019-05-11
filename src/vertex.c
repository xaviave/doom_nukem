/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vertex.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 12:24:02 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 23:04:54 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

void				vertex_destroy(t_vertex *v)
{
	ft_memdel((void**)&v);
	return ;
}

void				vertex_destroy_elem(void *content)
{
	vertex_destroy((t_vertex*)content);
	return ;
}

t_vertex			*new_vertex(int x, int y)
{
	t_vertex		*vertex;

	if (!(vertex = (t_vertex*)ft_memalloc(sizeof(t_vertex))))
		return (0);
	vertex->x = x;
	vertex->y = y;
	return (vertex);
}

void				vertex_update(t_vertex *v, int x, int y)
{
	v->x = x;
	v->y = y;
	return ;
}

void				vertex_draw(t_image *img, t_vertex *v, int pipet)
{
	image_pixel_put(img, v->x, v->y - 1, pipet);
	image_pixel_put(img, v->x + 1, v->y, pipet);
	image_pixel_put(img, v->x, v->y, pipet);
	image_pixel_put(img, v->x - 1, v->y, pipet);
	image_pixel_put(img, v->x, v->y + 1, pipet);
	return ;
}
