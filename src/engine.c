/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   engine.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 20:07:01 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/11 14:00:32 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/doom_map.h"

static void				device_register_keys(t_keyboard *k)
{
	register_new_key(k, KEY_ESCAPE);
	register_new_key(k, KEY_DEL);
	register_new_key(k, KEY_PAD_SUB);
	register_new_key(k, KEY_PAD_ADD);
	register_new_key(k, KEY_CTRL_LEFT);
	register_new_key(k, MOUSE_LEFT);
	register_new_key(k, MOUSE_RIGHT);
	register_new_key(k, MOUSE_MID);
	register_new_key(k, MOUSE_SCROLL_DOWN);
	register_new_key(k, MOUSE_SCROLL_UP);
	register_new_key(k, KEY_DEL);
	register_new_key(k, KEY_C);
	register_new_key(k, KEY_F);
	register_new_key(k, KEY_V);
	register_new_key(k, KEY_S);
	register_new_key(k, KEY_1);
	register_new_key(k, KEY_2);
	return ;
}

void					engine_destroy(t_engine *e)
{
	framework_destroy(e->mlx);
	keyboard_destroy(e->keyboard);
	mouse_destroy(e->mouse);
	gui_destroy(e->gui);
	ft_memdel((void **)&e);
	exit(1);
}

t_engine				*new_engine(void)
{
	t_engine			*e;
	t_image				*bg;
	t_vertex			v;

	v.x = 0;
	v.y = 0;
	if (!(e = (t_engine *)ft_memalloc(sizeof(t_engine))))
		return (0);
	if (!(e->mlx = new_framework()))
		return (0);
	if (!(e->keyboard = new_keyboard()))
		return (0);
	if (!(e->mouse = new_mouse(e->keyboard)))
		return (0);
	if (!(bg = new_image(e->mlx->id, e->mlx->win->id, WIDTH, HEIGH)))
		return (0);
	if (!(e->gui = new_gui(new_layer(bg, L_NO_DRAW))))
		return (0);
	image_fill(bg, CLR_BG);
	image_square(bg, &v, CLR_BG_S);
	device_register_keys(e->keyboard);
	return (e);
}
