/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:35:08 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 13:22:12 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int update_keys(t_mem *mem)
{
	camera_move(mem);

	mem->level->player.z = 5 + (mem->level->sector[mem->level->player.sector - 1].h_floor);
	//printf("sector %d |  hauteur sol %d\n", mem->level->player.sector, mem->level->sector[mem->level->player.sector - 1].h_floor);

	if (mem->level->player.keyspressed & MOVE_LEFT)
	{
		mem->level->player.x += (1.2f * sin(mem->level->player.angle));
		mem->level->player.y -= (1.2f * cos(mem->level->player.angle));
		player_sector(mem);
	}
	if (mem->level->player.keyspressed & MOVE_RIGHT)
	{
		mem->level->player.x -= (1.2f * sin(mem->level->player.angle));
		mem->level->player.y += (1.2f * cos(mem->level->player.angle));
		player_sector(mem);
	}
	if (mem->level->player.keyspressed & MOVE_UP)
	{
		mem->level->player.x += (1.2f * cos(mem->level->player.angle));
		mem->level->player.y += (1.2f * sin(mem->level->player.angle));
		player_sector(mem);
	}
	if (mem->level->player.keyspressed & MOVE_DOWN)
	{
		mem->level->player.x -= (1.2f * cos(mem->level->player.angle));
		mem->level->player.y -= (1.2f * sin(mem->level->player.angle));
		player_sector(mem);
	}
	if (mem->level->player.keyspressed & ROTATE_LEFT)
	{
	}
	if (mem->level->player.keyspressed & ROTATE_RIGHT)
	{
	}
	if (mem->level->player.keyspressed & ZOOM_OUT)
		mem->level->player.z -= 0.10;
	if (mem->level->player.keyspressed & ZOOM_IN)
		mem->level->player.z += 0.10;
	if (mem->level->player.keyspressed & EXIT_GAME)
	{
		exit(1);
	}
	refresh_screen(mem);
	return (1);
}

int mouse_move_hook(int x, int y, t_mem *mem)
{
	if (x || y || mem)
		;
	/*	if (mem->mouse_x > x)
		mem->level->player.angle -= 0.10;
	else if (mem->mouse_x + 2 < x)
		mem->level->player.angle += 0.10;


	mlx_mouse_get_pos(mem->win.win_ptr, &x, &y);
	*/
	/*	mem->mouse_x = x;
	mem->mouse_y = y;
	if (x == W / 2 && y == H / 2)
		mlx_mouse_move(mem->win.win_ptr, W / 2, H / 2);*/
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

int camera_move(t_mem *mem)
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