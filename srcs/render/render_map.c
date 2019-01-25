/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: mem->z19/01/10 14:14:48 by mel-akio     #+#   ##    ##    #+#       */
/*   Updated: mem->z19/01/10 15:58:17 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void fill_form(int x1, int x2, int y1, int y2, t_mem *mem)
{
	t_line line;

	line.dx = abs(x2 - x1);
	line.sx = (x1 < x2) ? 1 : -1;
	line.dy = abs(y2 - y1);
	line.sy = (y1 < y2) ? 1 : -1;
	line.err = ((line.dx > line.dy) ? line.dx : -line.dy) / 2;
	line.e2 = line.err;
	while (x1 != x2 || y1 != y2)
	{
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			x1 += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			y1 += line.sy;
		}
		if ((x1 > 0 && x1 < W))
		{
			if (y1 > H / 2)
				fill_column(x1, y1 - mem->camera_y, (H / 2) - mem->camera_y, mem);
			else
				fill_column(x1, y1 - mem->camera_y, (H / 2) + 1 - mem->camera_y, mem);
		}
	}
}

void draw_minimap(t_mem *mem)
{
	int i;
	int j;
	float tx1;
	float tx2;
	float ty1;
	float ty2;
	float tz1;
	float tz2;
	float x1;
	float x2;
	float y1a;
	float y1b;
	float y2a;
	float y2b;
	float ix1;
	float ix2;
	float iz1;
	float iz2;

	i = -1;
	mem->z = 10;
	mlx_clear_window(mem->mlx_ptr, mem->win.win_ptr);
	while (++i < mem->level->nb_sector)
	{
		j = -1;
		while (++j < mem->level->sector[i].nb_linedef)
		{
			mem->coord.x1 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 1) * mem->z;
			mem->coord.y1 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 1) * mem->z;
			mem->coord.x2 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 2) * mem->z;
			mem->coord.y2 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 2) * mem->z;
			tx1 = mem->coord.x1 - mem->level->player.x;
			tx2 = mem->coord.x2 - mem->level->player.x;
			ty1 = mem->coord.y1 - mem->level->player.y;
			ty2 = mem->coord.y2 - mem->level->player.y;
			tz1 = tx1 * cos(mem->level->player.angle) + ty1 * sin(mem->level->player.angle);
			tz2 = tx2 * cos(mem->level->player.angle) + ty2 * sin(mem->level->player.angle);
			tx1 = tx1 * sin(mem->level->player.angle) - ty1 * cos(mem->level->player.angle);
			tx2 = tx2 * sin(mem->level->player.angle) - ty2 * cos(mem->level->player.angle);
			mem->coord.x1 = tx1 + 150;
			mem->coord.x2 = tx2 + 150;
			mem->coord.y1 = tz1 + 150;
			mem->coord.y2 = tz2 + 150;
			if (tz1 > 0 || tz2 > 0)
			{
				intersect(tx1, tz1, tx2, tz2, -5, 5, -20, 5, &ix1, &iz1);  // 7eme argument definit la precision
				intersect(tx1, tz1, tx2, tz2, 5, 5, 20, 5, &ix2, &iz2); // 7eme argument definit la precision
				if (tz1 <= 0)
				{
					if (iz1 > 0)
					{
						tx1 = ix1;
						tz1 = iz1;
					}
					else
					{
						tx1 = ix2;
						tz1 = iz2;
					}
				}
				if (tz2 <= 0)
				{
					if (iz1 > 0)
					{
						tx2 = ix1;
						tz2 = iz1;
					}
					else
					{
						tx2 = ix2;
						tz2 = iz2;
					}
				}
				x1 = -tx1 * 800 / tz1 + W / 2; // 800 (ratio map)
				x2 = -tx2 * 800 / tz2 + W / 2;
				y1a = -H * 5 / tz1 + H / 2;
				y2a = -H * 5 / tz2 + H / 2;
				y1b = H * 5 / tz1 + H / 2;
				y2b = H * 5 / tz2 + H / 2;
			}
			change_color(&mem->color, mem->level->c[j]);

			fill_form(x1, x2, y1a + i, y2a + i, mem);
			fill_form(x1, x2, y1b + i, y2b + i, mem);
			/*
			draw_to_line((W / 2 + x1), (H / 2 + y1a), (W / 2 + x2), (H / 2 + y2a), mem);
			draw_to_line((W / 2 + x1), (H / 2 + y1b), (W / 2 + x2), (H / 2 + y2b), mem);
			draw_to_line((W / 2 + x1), (H / 2 + y1a), (W / 2 + x1), (H / 2 + y1b), mem);
			draw_to_line((W / 2 + x2), (H / 2 + y2a), (W / 2 + x2), (H / 2 + y2b), mem);
			*/
		}
	}

	/* player position */
	
	change_color(&mem->color, 0xff);
	i = -1;
	while (++i < mem->level->nb_sector)
	{
		j = -1;
		while (++j < mem->level->sector[i].nb_linedef)
		{
			mem->coord.x1 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 1) * mem->z;
			mem->coord.y1 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 1) * mem->z;
			mem->coord.x2 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 2) * mem->z;
			mem->coord.y2 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 2) * mem->z;
			tx1 = mem->coord.x1 - mem->level->player.x;
			tx2 = mem->coord.x2 - mem->level->player.x;
			ty1 = mem->coord.y1 - mem->level->player.y;
			ty2 = mem->coord.y2 - mem->level->player.y;
			tz1 = tx1 * cos(mem->level->player.angle) + ty1 * sin(mem->level->player.angle);
			tz2 = tx2 * cos(mem->level->player.angle) + ty2 * sin(mem->level->player.angle);
			tx1 = tx1 * sin(mem->level->player.angle) - ty1 * cos(mem->level->player.angle);
			tx2 = tx2 * sin(mem->level->player.angle) - ty2 * cos(mem->level->player.angle);
			mem->coord.x1 = tx1 + 150;
			mem->coord.x2 = tx2 + 150;
			mem->coord.y1 = tz1 + 150;
			mem->coord.y2 = tz2 + 150;
			
			draw_circle(mem);
			draw_line(mem);
			draw_circle(mem);
		}
	}
	mem->coord.x1 = 150;
	mem->coord.y1 = 150;
	mem->coord.x2 = 150;
	mem->coord.y2 = 150 + 30;
	draw_circle(mem);
	draw_line(mem);
	
}

int update_keys(t_mem *mem)
{
	camera_move(mem);
	if (mem->level->player.keyspressed & MOVE_LEFT)
	{
		mem->level->player.x = mem->level->player.x + 3 * sin(mem->level->player.angle);
		mem->level->player.y = mem->level->player.y + 3 * cos(mem->level->player.angle);
	}
	if (mem->level->player.keyspressed & MOVE_RIGHT)
	{
		mem->level->player.x = mem->level->player.x - 3 * sin(mem->level->player.angle);
		mem->level->player.y = mem->level->player.y - 3 * cos(mem->level->player.angle);
	}
	if (mem->level->player.keyspressed & MOVE_UP)
	{
		mem->level->player.x = mem->level->player.x + 3 * cos(mem->level->player.angle);
		mem->level->player.y = mem->level->player.y + 3 * sin(mem->level->player.angle);
	}
	if (mem->level->player.keyspressed & MOVE_DOWN)
	{
		mem->level->player.x = mem->level->player.x - 3 * cos(mem->level->player.angle);
		mem->level->player.y = mem->level->player.y - 3 * sin(mem->level->player.angle);
	}
	if (mem->level->player.keyspressed & ROTATE_LEFT)
	{
	}
	if (mem->level->player.keyspressed & ROTATE_RIGHT)
	{
	}
	if (mem->level->player.keyspressed & ZOOM_OUT)
		mem->z -= 2;
	if (mem->level->player.keyspressed & ZOOM_IN)
		mem->z += 2;
	if (mem->level->player.keyspressed & EXIT_GAME)
	{
		exit(1);
	}
	refresh_screen(mem);
	return (1);
}

void refresh_screen(t_mem *mem)
{
	if (mem->img.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->img.ptr);
	ft_create_img(mem);
	draw_minimap(mem);

	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->img.ptr, 0, 0);
}

void event_loop(t_mem *mem)
{
	mlx_hook(mem->win.win_ptr, 17, 0L, cross_close, mem);
	mlx_hook(mem->win.win_ptr, MOTION_NOTIFY, PTR_MOTION_MASK,
			 mouse_move_hook, mem);
	mlx_mouse_hook(mem->win.win_ptr, mouse_click_hook, mem);
	mlx_hook(mem->win.win_ptr, 2, 1L << 0, add_key, mem);
	mlx_hook(mem->win.win_ptr, 3, 1L << 1, remove_key, mem);
	mlx_loop_hook(mem->mlx_ptr, update_keys, mem);
	mlx_loop(mem->mlx_ptr);
}
