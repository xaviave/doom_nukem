/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:35:08 by xamartin          #+#    #+#             */
/*   Updated: 2020/03/13 13:58:35 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/doom.h"

void		update_keys3(t_mem *mem)
{
	if (mem->level->player.last_position != mem->level->player.x
		+ mem->level->player.y)
	{
		player_sector(mem, 0);
		player_animation(mem);
		sort_dist_monsters(mem);
	}
	if (mem->level->player.keyspressed & RELOAD)
		on_reload(mem);
	if (mem->level->player.keyspressed & PICKUP)
		on_collision(mem);
	if (mem->level->player.keyspressed & EXIT_GAME)
		free_mem(mem);
	mem->level->player.last_position = mem->level->player.x
		+ mem->level->player.y;
	if (mem->level->player.shoot > 0)
		mem->level->player.shoot--;
	if (mem->level->player.keyspressed & JUMP)
		jump(mem);
	refresh_screen(mem);
	ai_think(mem);
	check_mobs(mem);
}

void		update_keys2(t_mem *mem, float try_pos_x, float try_pos_y)
{
	if (mem->level->player.keyspressed & CROUCH)
		mem->level->player.z -= 3;
	if (mem->level->player.keyspressed & MOVE_UP)
		alloc_up(mem);
	if (mem->level->player.keyspressed & MOVE_DOWN)
		alloc_down(mem);
	if (!mem->level->player.god_mode && (player_sector(mem, 1) == -1 ||
		mem->level->player.heigth_player + mem->level->sector[send_s_id(mem,
		mem->level->player.sector)].h_floor >= mem->level->sector[send_s_id(mem,
		player_sector(mem, 1))].h_ceil))
	{
		mem->level->player.x = try_pos_x;
		mem->level->player.y = try_pos_y;
	}
	else
	{
		mem->level->player.x = mem->col_x;
		mem->level->player.y = mem->col_y;
	}
	update_keys3(mem);
}

int			update_keys(t_mem *mem)
{
	float	try_pos_x;
	float	try_pos_y;

	camera_move(mem);
	mem->cos_angle = cos(mem->level->player.angle);
	mem->sin_angle = sin(mem->level->player.angle);
	if (mem->level->player.recoil > 0)
		mem->level->player.recoil -= 1.3;
	try_pos_x = mem->level->player.x;
	try_pos_y = mem->level->player.y;
	mem->col_x = try_pos_x;
	mem->col_y = try_pos_y;
	if (mem->level->player.keyspressed & MOVE_LEFT)
		alloc_left(mem);
	if (mem->level->player.keyspressed & MOVE_RIGHT)
		alloc_right(mem);
	if (!(mem->level->player.keyspressed & FLY))
		physics(mem);
	update_keys2(mem, try_pos_x, try_pos_y);
	return (0);
}

int			camera_move(t_mem *mem)
{
	mlx_mouse_get_pos(mem->win.win_ptr, &mem->mouse_x, &mem->mouse_y);
	if (mem->mouse_y != H / 2)
		mem->camera_y += (mem->mouse_y - H / 2);
	if (mem->mouse_x != W / 2)
		mem->camera_x += (mem->mouse_x - W / 2);
	mem->level->player.angle = mem->camera_x * 0.001;
	mlx_mouse_move(mem->win.win_ptr, W / 2, H / 2);
	mlx_mouse_hide();
	return (0);
}
