/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:35:08 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 16:36:32 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int mouse_move_hook(int x, int y, t_mem *mem)
{
	if (x || y || mem)
		return (0);
	return (0);
}

int mouse_click_hook(int k, int x, int y, t_mem *mem)
{
	if (k || x || y || mem)
		return (0);
	return (0);
}

int add_key(int k, t_mem *mem)
{
	mem->level->player.keyspressed |= mem->level->player.keys_shortcuts[k];
	return (0);
}

int remove_key(int k, t_mem *mem)
{
	mem->level->player.keyspressed &= ~mem->level->player.keys_shortcuts[k];
	return (0);
}

int cross_close(t_mem *mem)
{
	if (mem)
		;
	exit(1);
	return (1);
}
