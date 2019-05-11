/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gui_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 02:39:27 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 21:36:23 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

static void			gui_display_layer(void *content)
{
	t_layer			*layer;

	layer = (t_layer*)content;
	mlx_put_image_to_window(layer->img->mlx_id,
		layer->img->win_id, layer->img->id, 0, 0);
	return ;
}

void				gui_display(t_gui *gui)
{
	t_layer			*layer;

	layer = (t_layer*)gui->iterator->content;
	gui_display_layer(gui->layer->begin->content);
	if (gui->iterator != gui->layer->begin)
	{
		layer_draw((t_layer*)gui->iterator->content);
		if (gui->iterator->parent && gui->iterator->parent != gui->layer->begin)
		{
			layer_draw((t_layer*)gui->iterator->parent->content);
			gui_display_layer(gui->iterator->parent->content);
		}
		gui_display_layer(gui->iterator->content);
	}
	return ;
}

void				gui_next(t_gui *gui)
{
	if (gui->iterator->child)
	{
		((t_layer*)(gui->iterator->content))->pipet = CLR_SHADOW;
		payload_next(gui->layer, &gui->iterator);
		((t_layer*)(gui->iterator->content))->pipet = CLR_LAYER;
	}
	return ;
}

void				gui_prev(t_gui *gui)
{
	if (gui->iterator->parent)
	{
		((t_layer*)(gui->iterator->content))->pipet = CLR_SHADOW;
		payload_prev(gui->layer, &gui->iterator);
		((t_layer*)(gui->iterator->content))->pipet = CLR_LAYER;
	}
	return ;
}
