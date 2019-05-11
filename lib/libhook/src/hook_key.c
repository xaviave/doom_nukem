/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hook_key.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 02:53:12 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/11 13:53:12 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/libhook.h"

int				key_press_hook(int key, t_keyboard *keyboard)
{
	keyboard->reg_rise |= 1 << keyboard->reg_id[key];
	keyboard->reg_key |= 1 << keyboard->reg_id[key];
	return (0);
}

int				key_release_hook(int key, t_keyboard *keyboard)
{
	keyboard->reg_fall |= 1 << keyboard->reg_id[key];
	keyboard->reg_key ^= 1 << keyboard->reg_id[key];
	return (0);
}
