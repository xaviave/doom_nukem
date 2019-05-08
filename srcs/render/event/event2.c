/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 21:17:41 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 13:31:04 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

int			mouse_move_hook(int x, int y, t_mem *mem)
{
	if (x || y || mem)
		;
	return (0);
}

int			mouse_click_hook(int k, int x, int y, t_mem *mem)
{
	if (k == 1)
	{
		play_audio(mem->level->sounds.shoot1);
		if (mem->level->player.recoil < 50)
			mem->level->player.recoil += 14;
		else
			mem->level->player.recoil += 3;
		mem->level->player.shoot = 2;
	}
	if (k || x || y || mem)
		return (0);
	return (0);
}

int			add_key(int k, t_mem *mem)
{
	mem->level->player.keyspressed |= mem->level->player.keys_shortcuts[k];
	return (0);
}

int			remove_key(int k, t_mem *mem)
{
	mem->level->player.keyspressed &= ~mem->level->player.keys_shortcuts[k];
	return (0);
}

int			cross_close(t_mem *mem)
{
	if (mem)
		;
	exit(1);
	return (1);
}
