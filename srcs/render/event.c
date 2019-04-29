/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:35:08 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/31 20:48:03 by lloyet      ###    #+. /#+    ###.fr     */
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
	//printf("angle = %f keyPress = %d cameraX = %d cameraY = %d\n", mem->playerOrientation, mem->level->player.keyspressed, mem->camera_x, mem->camera_y);
	//printf("neighbors = %d, sector = %d, x = %f, y = %f, z = %f\n", mem->level->sector[mem->level->player.sector].nb_neighbors, mem->level->player.sector, mem->level->player.x, mem->level->player.y,mem->level->player.z);
	
	if (mem->level->player.recoil > 0)
		mem->level->player.recoil -= 1.3;
	if ((mem->level->player.keyspressed & MOVE_LEFT) && !mem->menu) //&& (mem->level->player.sector > 0))
	{
		mem->level->player.x += (1 * mem->sin_angle);
		mem->level->player.y -= (1 * mem->cos_angle);
	}
	if ((mem->level->player.keyspressed & MOVE_RIGHT) && !mem->menu) //&& (mem->level->player.sector > 0))
	{
		mem->level->player.x -= (1 * mem->sin_angle);
		mem->level->player.y += (1 * mem->cos_angle);
	}
	if ((mem->level->player.keyspressed & MOVE_UP) && !mem->menu) //&& (mem->level->player.sector > 0))
	{
		mem->level->player.x += (2 * mem->cos_angle);
		mem->level->player.y += (2 * mem->sin_angle);
	}
	if ((mem->level->player.keyspressed & MOVE_DOWN) && !mem->menu) //&& (mem->level->player.sector > 0))
	{
		mem->level->player.x -= (2 * mem->cos_angle );
		mem->level->player.y -= (2 * mem->sin_angle);
	}
	if (mem->level->player.keyspressed & ROTATE_LEFT)
	{
	}
	if (mem->level->player.keyspressed & ROTATE_RIGHT)
	{
	}
	if (mem->level->player.keyspressed & ZOOM_OUT)
	{
		//	mem->z -= 0.05;
	}
	if (mem->level->player.keyspressed & ZOOM_IN)
	{
		//	mem->z += 0.05;
	}
	if ((mem->level->player.keyspressed & JUMP) && !mem->menu)
	{
		//player_tp(&mem->level->player, 0, 0 ,0);
		jump(mem);
	}
	if ((mem->level->player.keyspressed & RELOAD) && !mem->menu)
	{
		play_audio(mem->level->sounds.reload);
	}
	if (mem->level->player.keyspressed & EXIT_GAME)
	{
		exit(1);
	}
	if (mem->level->player.last_position != mem->level->player.x + mem->level->player.y)
	{
		player_sector(mem);
		player_animation(mem);
		sort_dist_monsters(mem);
	}
	/*if (mem->level->player.sector < 0)
	{
		mem->level->player.x = mem->lastX;
		mem->level->player.y = mem->lastY;
	}
	else
	{
		mem->lastX = mem->level->player.x;
		mem->lastY = mem->level->player.y;
		mem->level->player.last_position = mem->level->player.x + mem->level->player.y;
	}*/
	if (!(mem->tv1.tv_sec))
		gettimeofday(&mem->tv1, NULL);
	refresh_screen(mem);
	draw_minimap(mem);
	gettimeofday(&mem->tv2, NULL);
	mem->FPS++;

	if (mem->tv2.tv_sec - mem->tv1.tv_sec >= 1)
	{
		/*ft_putstr("FPS : ");
		ft_putnbr(mem->FPS);
		putchar('\n');*/
		mem->FPS = 0;
		mem->tv1.tv_sec = 0;
		mem->tv2.tv_sec = 0;
	}
	/*printf ("Total time = %f seconds\n",
        (double) (mem->tv2.tv_usec - mem->tv1.tv_usec) / 1000000 +
        (double) (mem->tv2.tv_sec - mem->tv1.tv_sec));*/
	if (mem->level->player.shoot > 0)
		mem->level->player.shoot--;
	return (0);
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
	if (!mem->menu && k == 1)
	{
		play_audio(mem->level->sounds.shoot1);
		if (mem->level->player.recoil < 50)
			mem->level->player.recoil += 14;
		else
			mem->level->player.recoil += 3;

		mem->level->player.shoot = 2;
	}
	else if (mem->menu && x > 0 && y > 0)
		mem->menu = !mem->menu;
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

void	camera_reset(t_mem *mem)
{
	mem->camera_x = mem->level->spawn.camX;
	mem->camera_y = mem->level->spawn.camY;
	return ;
}

int camera_move(t_mem *mem)
{
	if ((mem->level->player.keyspressed & EXIT_GAME) && mem->lastkeyPress != mem->level->player.keyspressed)
		mem->menu = !mem->menu;
	if (!mem->menu)
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
			mem->level->player.angle = mem->camera_x * mem->mouse_sensi; //sensi souris
			//mem->playerOrientation = 180.0*cos(((_PI)*mem->camera_x)/(6283.38*2));
			//90*cos((_PI/180)*mem->camera_x/8); 180.0*cos(((_TWO_PI)*mem->camera_x)/(6283.38*2));
			mlx_mouse_move(mem->win.win_ptr, W / 2, H / 2);
			mlx_mouse_hide();
	}
	else
		mlx_mouse_show();
	mem->lastkeyPress = mem->level->player.keyspressed;
	return (0);
}
