/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   math.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:39:18 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 18:28:21 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int fn_cross(float x1, float y1, float x2, float y2)
{
	return ((x1 * y2) - (y1 * x2));
}

void intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *x, float *y)
{
	float det;
	*x = fn_cross(x1, y1, x2, y2);
	*y = fn_cross(x3, y3, x4, y4);
	det = fn_cross(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	*x = fn_cross(*x, x1 - x2, *y, x3 - x4) / det;
	*y = fn_cross(*x, y1 - y2, *y, y3 - y4) / det;
}

int return_min(int x1, int x2)
{
	return ((x1 > x2 ? x2 : x1));
}

void physics(t_mem *mem)
{
	//printf("floor = %d\n", mem->level->sector[mem->level->player.sector - 1].h_floor);
	//printf("camX = %d, camY = %d\n", mem->camera_x, mem->camera_y);
	if (mem->level->player.sector > 0 && mem->level->player.z > mem->level->sector[mem->level->player.sector - 1].h_floor - 5)	
	{

		if (mem->level->player.on_jump == FALSE)
		{
			if (mem->level->player.z - 5 > mem->level->sector[mem->level->player.sector - 1].h_floor)
			{
				mem->level->player.z -= mem->level->player.inertia;
				mem->level->player.inertia += 0.07;
			}
			else if (mem->level->player.z - 5 < mem->level->sector[mem->level->player.sector - 1].h_floor)
				mem->level->player.z = mem->level->sector[mem->level->player.sector - 1].h_floor + 5;
		}
		else
		{
			if (mem->level->player.z > mem->level->sector[mem->level->player.sector - 1].h_floor + 10)
				mem->level->player.on_jump = FALSE;
			mem->level->player.z += mem->level->player.inertia;
			if (mem->level->player.inertia - 0.07 > 0)
				mem->level->player.inertia -= 0.07;
		}
		mem->gravity = 0;
	}
	else
	{
		mem->level->player.z -= 0.07*mem->gravity;
		mem->gravity++;
	}
	
	if (mem->level->player.z < -500)
	{
		player_die(&mem->level->player, mem->level);
		camera_reset(mem);
	}
}

void	player_tp(t_player *player, float x, float y, float z)
{
	player->x = x;
	player->y = y;
	player->z = z;
	return ;
}

void	player_die(t_player *player, t_level *level)
{
	player->angle = level->spawn.angle;
	player_tp(player, level->spawn.x, level->spawn.y, level->spawn.z);
	return ;
}

void jump(t_mem *mem)
{
	if (mem->level->player.z - 5 == mem->level->sector[mem->level->player.sector - 1].h_floor)
	{
		//audio("sound/jump2.wav");
		play_audio(mem->level->sounds.jump);
		mem->level->player.on_jump = TRUE;
		mem->level->player.inertia = 1;
		mem->level->player.last_hitting_floor = mem->level->sector[mem->level->player.sector - 1].h_floor;
	}
}

void player_animation(t_mem *mem)
{
	if (mem->level->player.motion > 30)
		mem->level->player.motion_state = -1;
	else if (mem->level->player.motion < 0)
		mem->level->player.motion_state = 1;
	mem->level->player.motion += mem->level->player.motion_state;
}

float		distance(float x1, float y1, float x2, float y2)
{
	float	a;
	float	b;

	a = x1 - x2;
	b = y1 - y2;
	return (sqrt(a * a + b * b));
}
