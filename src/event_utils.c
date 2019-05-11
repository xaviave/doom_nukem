/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 10:57:49 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 01:57:18 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

static void			visual_move(t_mouse *m, t_keyboard *k, t_layer *l)
{
	t_shape			*s;
	t_vertex		*v;

	if (key_is_rising(k, MOUSE_LEFT))
	{
		if (l->s_tmp)
			l->v_tmp = shape_has_vertex(l->s_tmp, m->x, m->y);
		else if ((s = layer_has_vertex(l, m->x, m->y)))
			l->v_tmp = shape_has_vertex(s, m->x, m->y);
	}
	if (key_is_falling(k, MOUSE_LEFT) && l->v_tmp)
	{
		if ((s = layer_has_vertex(l, m->x, m->y)) &&
			(v = shape_has_vertex(s, m->x, m->y)))
			vertex_update(l->v_tmp, v->x, v->y);
		else
			vertex_update(l->v_tmp, m->x, m->y);
		l->v_tmp = 0;
	}
	if (key_is_pressed(k, MOUSE_LEFT) && l->v_tmp)
		vertex_update(l->v_tmp, m->x, m->y);
	return ;
}

void				event_gui_manage(t_framework *mlx, t_keyboard *k, t_gui *g)
{
	t_image			*img;

	if (key_is_pressed(k, KEY_CTRL_LEFT))
	{
		if (key_is_rising(k, KEY_PAD_ADD))
		{
			if ((img = new_image(mlx->id, mlx->win->id, WIDTH, HEIGH)))
				gui_add_layer(g, new_layer(img, L_EDIT));
		}
		else if (key_is_rising(k, KEY_PAD_SUB))
			gui_remove_layer(g);
	}
	return ;
}

void				event_gui_mode(t_keyboard *k, t_layer *l, t_gui *g)
{
	if (key_is_rising(k, KEY_V))
	{
		if (l->mode == L_EDIT)
			l->mode = L_VISUAL;
		else if (l->mode == L_VISUAL)
			l->mode = L_EDIT;
		l->v_tmp = 0;
	}
	if (key_is_pressed(k, KEY_CTRL_LEFT) && key_is_rising(k, KEY_S))
		g->file = file_save(g);
	return ;
}

void				event_visual(t_mouse *m, t_keyboard *k, t_layer *l)
{
	if (key_is_rising(k, KEY_DEL))
	{
		if (l->s_tmp)
		{
			shape_destroy(l->s_tmp);
			l->s_tmp = 0;
			l->mode = L_EDIT;
		}
	}
	if (((m->x > O_SKETCH - 1) && (m->x < WIDTH))
		&& ((m->y > -1) && (m->y < HEIGH)))
		visual_move(m, k, l);
	return ;
}

void				event_pipet(t_layer *l, t_pipet pipet, int x, int y)
{
	if (l->entity)
	{
		if (pipet == P_PLAYER)
			vertex_update(l->spawn, x, y);
		else if (pipet == P_ENTITY)
			layer_add_entity(l, new_vertex(x, y));
	}
	else
	{
		if (pipet == P_PLAYER)
			vertex_update(l->spawn, x, y);
		else if (pipet == P_ENTITY)
		{
			l->entity = new_payload((void*)new_vertex(x, y), &vertex_destroy_elem);
			l->it_entity = new_iterator(l->entity);
		}
	}
	return ;
}
