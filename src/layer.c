/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   layer.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/04 19:57:51 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 00:40:35 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

static void			layer_destroy_shape(void *content)
{
	shape_destroy((t_shape*)content);
	return ;
}

void				layer_destroy(t_layer *layer)
{
	if (layer->s_tmp)
		shape_destroy(layer->s_tmp);
	if (layer->v_tmp)
		vertex_destroy(layer->v_tmp);
	if (layer->shape)
		payload_destroy(layer->shape);
	if (layer->entity)
		payload_destroy(layer->entity);
	vertex_destroy(layer->spawn);
	image_destroy(layer->img);
	ft_memdel((void**)&layer);
	return ;
}

t_layer				*new_layer(t_image *img, t_mode m)
{
	t_layer		*layer;

	if (!(layer = (t_layer*)ft_memalloc(sizeof(t_layer))))
		return (0);
	layer->spawn = new_vertex(-1, -1);
	layer->img = img;
	layer->pipet = CLR_LAYER;
	layer->scale = G_SCALE;
	layer->mode = m;
	image_fill(layer->img, CLR_A);
	return (layer);
}

void				layer_init(t_layer *l, t_shape *s)
{
	l->shape = new_payload((void*)s, &layer_destroy_shape);
	l->it_shape = new_iterator(l->shape);
	return ;
}

void				layer_add_entity(t_layer *l, t_vertex *e)
{
	payload_add(l->entity, l->it_entity, (void*)e);
	payload_next(l->entity, &l->it_entity);
	return ;
}
