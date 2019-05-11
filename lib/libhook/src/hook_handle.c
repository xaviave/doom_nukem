/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hook_handle.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 12:29:59 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 21:40:04 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/libhook.h"

void			register_new_key(t_keyboard *keyboard, int key)
{
	if (keyboard->reg_size < REG_KMASK_MAX)
		keyboard->reg_id[key] = ++keyboard->reg_size;
	return ;
}

int				key_is_pressed(t_keyboard *k, int key)
{
	return (k->reg_key & (1 << k->reg_id[key]) ? 1 : 0);
}

int				key_is_falling(t_keyboard *k, int key)
{
	if ((k->reg_fall & (1 << k->reg_id[key])) && !(key_is_pressed(k, key)))
	{
		k->reg_fall ^= 1 << k->reg_id[key];
		return (1);
	}
	return (0);
}

int				key_is_rising(t_keyboard *k, int key)
{
	if ((k->reg_rise & (1 << k->reg_id[key])) && (key_is_pressed(k, key)))
	{
		k->reg_rise ^= 1 << k->reg_id[key];
		return (1);
	}
	return (0);
}
