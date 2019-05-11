/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 17:52:25 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 00:42:04 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

static void			event_edit_shape(t_keyboard *k, t_layer *l)
{
	if (key_is_pressed(k, KEY_C))
	{
		if (key_is_rising(k, KEY_PAD_ADD) && l->s_tmp)
			l->s_tmp->ceil++;
		else if (key_is_rising(k, KEY_PAD_SUB) && l->s_tmp
			&& (l->s_tmp->ceil - 1 > -1))
			l->s_tmp->ceil--;
	}
	else if (key_is_pressed(k, KEY_F))
	{
		if (key_is_rising(k, KEY_PAD_ADD) && l->s_tmp)
			l->s_tmp->floor++;
		else if (key_is_rising(k, KEY_PAD_SUB) && l->s_tmp
			&& (l->s_tmp->floor - 1 > -1))
			l->s_tmp->floor--;
	}
	return ;
}

static void			delete_tmp(t_layer *l)
{
	if (l->s_tmp->vertex->n < 2)
	{
		shape_destroy(l->s_tmp);
		l->s_tmp = 0;
	}
	else
		shape_remove(l->s_tmp);
	return ;
}

static void			edit_tmp(t_layer *l, t_vertex *v)
{
	t_vertex		*v_shape;
	t_vertex		*begin;

	begin = (t_vertex*)l->s_tmp->vertex->begin->content;
	v_shape = shape_has_vertex(l->s_tmp, v->x, v->y);
	if (l->s_tmp->vertex->n > 2 && v_shape && v_shape == begin)
	{
		vertex_update(v, v_shape->x, v_shape->y);
		shape_add(l->s_tmp, v);
		l->mode = L_VISUAL;
		if (!l->shape)
			layer_init(l, l->s_tmp);
		else
			layer_add(l, l->s_tmp);
		l->s_tmp = 0;
	}
	else if (!v_shape)
		shape_add(l->s_tmp, v);
	return ;
}

static void			event_editor(t_mouse *m, t_keyboard *k,
					t_layer *l, t_gui *g)
{
	t_vertex		*v;

	event_edit_shape(k, l);
	if (((m->x > O_SKETCH - 1) && (m->x < WIDTH))
		&& ((m->y > -1) && (m->y < HEIGH)))
	{
		if (key_is_rising(k, MOUSE_RIGHT))
			event_pipet(l, g->pipet, m->x, m->y);
		else if (key_is_rising(k, KEY_DEL) && l->s_tmp)
			delete_tmp(l);
		else if (key_is_rising(k, MOUSE_LEFT) || (key_is_pressed(k, MOUSE_MID)))
		{
			v = new_vertex(m->x, m->y);
			if (l->s_tmp)
				edit_tmp(l, v);
			else
				l->s_tmp = new_shape(v);
		}
	}
	return ;
}

void				event_refresh(t_engine *e)
{
	t_layer			*l;

	l = (t_layer*)e->gui->iterator->content;
	if (key_is_pressed(e->keyboard, KEY_ESCAPE))
		engine_destroy(e);
	if (key_is_rising(e->keyboard, MOUSE_SCROLL_UP))
		gui_next(e->gui);
	else if (key_is_rising(e->keyboard, MOUSE_SCROLL_DOWN))
		gui_prev(e->gui);
	if (l->mode != L_NO_DRAW)
	{
		if (key_is_rising(e->keyboard, KEY_1))
			e->gui->pipet = P_PLAYER;
		else if (key_is_rising(e->keyboard, KEY_2))
			e->gui->pipet = P_ENTITY;
		event_gui_mode(e->keyboard, l, e->gui);
	}
	if (l->mode == L_EDIT)
		event_editor(e->mouse, e->keyboard, l, e->gui);
	else if (l->mode == L_VISUAL)
		event_visual(e->mouse, e->keyboard, l);
	event_gui_manage(e->mlx, e->keyboard, e->gui);
	return ;
}
