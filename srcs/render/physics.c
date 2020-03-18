/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   physics.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:39:18 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 13:30:45 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	physics(t_mem *mem)
{
	if (mem->level->player.on_jump == FALSE)
	{
		if (mem->level->player.z - 5 >
mem->level->sector[mem->level->player.sector - 1].h_floor)
		{
			mem->level->player.z -= mem->level->player.inertia;
			mem->level->player.inertia += 0.07;
		}
		else if (mem->level->player.z - 5 <
mem->level->sector[mem->level->player.sector - 1].h_floor)
			mem->level->player.z =
mem->level->sector[mem->level->player.sector - 1].h_floor + 5;
	}
	else
	{
		if (mem->level->player.z >
mem->level->sector[mem->level->player.sector - 1].h_floor + 10)
			mem->level->player.on_jump = FALSE;
		mem->level->player.z += mem->level->player.inertia;
		if (mem->level->player.inertia - 0.07 > 0)
			mem->level->player.inertia -= 0.07;
	}
}

void	jump(t_mem *mem)
{
	if (mem->level->player.z - 5 ==
mem->level->sector[mem->level->player.sector - 1].h_floor)
	{
		play_audio(mem->level->sounds.jump);
		mem->level->player.on_jump = TRUE;
		mem->level->player.inertia = 1;
		mem->level->player.last_hitting_floor =
mem->level->sector[mem->level->player.sector - 1].h_floor;
	}
}

void	player_animation(t_mem *mem)
{
	if (mem->level->player.motion > 30)
		mem->level->player.motion_state = -1;
	else if (mem->level->player.motion < 0)
		mem->level->player.motion_state = 1;
	mem->level->player.motion += mem->level->player.motion_state;
}
