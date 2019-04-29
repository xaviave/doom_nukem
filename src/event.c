/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 17:52:25 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 18:25:46 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/wolf.h"

static void			event_catch_mouse(t_engine *e)
{
	t_keyboard 		*k;

	k = e->keyboard;
	if (key_is_pressed(k, MOUSE_SCROLL_UP))
	{
		k->reg_key &= k->reg_key ^ (1 << k->reg_id[MOUSE_SCROLL_UP]);
		if (key_is_pressed(k, KEY_CTRL_LEFT))
			cycle_insert(e->sketch->marker, new_cycle(new_grid(new_image(e->mlx->id, WIDTH, HEIGH))));
		else
			ft_putstr("Zoom In\n");
	}
	else if (key_is_pressed(k, MOUSE_SCROLL_DOWN))
	{
		k->reg_key &= k->reg_key ^ (1 << k->reg_id[MOUSE_SCROLL_DOWN]);
		if (key_is_pressed(k, KEY_CTRL_LEFT))
			cycle_delone(&e->sketch->board, e->sketch->marker);
		else
			ft_putstr("Zoom Out\n");
	}
	if (key_is_pressed(k, MOUSE_RIGHT))
		ft_putstr("mouseRight\n");
	else if (key_is_pressed(k, MOUSE_LEFT))
		ft_putstr("mouseLeft\n");
	if (key_is_pressed(k, MOUSE_MID))
		ft_putstr("mouseMiddle\n");
	return ;
}

static void			event_catch_keyboard(t_engine *e)
{
	t_keyboard		*k;

	k = e->keyboard;
	if (key_is_pressed(k, KEY_SPACE))
		ft_putstr("Space\n");
	return ;
}

void				event_refresh(t_engine *e)
{
	if (key_is_pressed(e->keyboard, KEY_ESCAPE))
		engine_destroy(e);
	event_catch_mouse(e);
	event_catch_keyboard(e);
	return ;
}