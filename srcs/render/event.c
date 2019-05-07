/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:35:08 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 14:28:17 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int update_keys(t_mem *mem)
{
	camera_move(mem);
	physics(mem);
	mem->cos_angle = cos(mem->level->player.angle);
	mem->sin_angle = sin(mem->level->player.angle);
	if (mem->level->player.recoil > 0)
		mem->level->player.recoil -= 1.3;
	if (mem->level->player.keyspressed & MOVE_LEFT)
	{
		mem->level->player.x += (1 * mem->sin_angle);
		mem->level->player.y -= (1 * mem->cos_angle);
	}
	if (mem->level->player.keyspressed & MOVE_RIGHT)
	{
		mem->level->player.x -= (1 * mem->sin_angle);
		mem->level->player.y += (1 * mem->cos_angle);
	}
	if (mem->level->player.keyspressed & MOVE_UP)
	{
		mem->level->player.x += (2 * mem->cos_angle);
		mem->level->player.y += (2 * mem->sin_angle);
	}
	if (mem->level->player.keyspressed & MOVE_DOWN)
	{
		mem->level->player.x -= (2 * mem->cos_angle);
		mem->level->player.y -= (2 * mem->sin_angle);
	}
	if (mem->level->player.keyspressed & JUMP)
		jump(mem);
	if (mem->level->player.keyspressed & RELOAD)
		play_audio(mem->level->sounds.reload);
	if (mem->level->player.keyspressed & EXIT_GAME)
		exit(1);
	if (mem->level->player.last_position != mem->level->player.x + mem->level->player.y)
	{
		player_sector(mem);
		player_animation(mem);
		sort_dist_monsters(mem);
	}
	mem->level->player.last_position = mem->level->player.x + mem->level->player.y;
	if (!(mem->tv1.tv_sec))
		gettimeofday(&mem->tv1, NULL);
	refresh_screen(mem);
	mem->FPS += 1;
	gettimeofday(&mem->tv2, NULL);
	if (mem->tv2.tv_sec - mem->tv1.tv_sec >= 1)
	{
		ft_putstr("FPS : ");
		ft_putnbr(mem->FPS);
		putchar('\n');
		mem->FPS = 0;
		mem->tv1.tv_sec = 0;
		mem->tv2.tv_sec = 0;
	}
	if (mem->level->player.shoot > 0)
		mem->level->player.shoot--;
	return (0);
}

int	mouse_move_hook(int x, int y, t_mem *mem)
{
	if (x || y || mem)
		;
	return (0);
}

int	mouse_click_hook(int k, int x, int y, t_mem *mem)
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

int	add_key(int k, t_mem *mem)
{
	mem->level->player.keyspressed |= mem->level->player.keys_shortcuts[k];
	return (0);
}

int	remove_key(int k, t_mem *mem)
{
	mem->level->player.keyspressed &= ~mem->level->player.keys_shortcuts[k];
	return (0);
}

int	cross_close(t_mem *mem)
{
	if (mem)
		;
	exit(1);
	return (1);
}

int	camera_move(t_mem *mem)
{
	mlx_mouse_get_pos(mem->win.win_ptr, &mem->mouse_x, &mem->mouse_y);
	if (mem->mouse_y > H / 2)
		mem->camera_y += (mem->mouse_y - H / 2);
	else if (mem->mouse_y < H / 2)
		mem->camera_y += (mem->mouse_y - H / 2);
	if (mem->mouse_x > W / 2)
		mem->camera_x += (mem->mouse_x - W / 2);
	else if (mem->mouse_x < W / 2)
		mem->camera_x += (mem->mouse_x - W / 2);
	mem->level->player.angle = mem->camera_x * 0.001;
	mlx_mouse_move(mem->win.win_ptr, W / 2, H / 2);
	mlx_mouse_hide();
	return (0);
}
