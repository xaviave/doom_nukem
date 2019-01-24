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

static int cross_close(t_mem *mem)
{
	if (mem)
		;
	exit(1);
	return (1);
}

int send_vx(t_level *level, int id)
{
	int i;

	i = -1;
	while (++i < level->nb_vertex)
	{
		if (level->vertex[i].id == id)
			return (level->vertex[i].x);
	}
	return (0);
}

int send_vy(t_level *level, int id)
{
	int i;

	i = -1;
	while (++i < level->nb_vertex)
	{
		if (level->vertex[i].id == id)
			return (level->vertex[i].y);
	}
	return (0);
}

int send_l_vx(t_level *level, int id_l, int vertex)
{
	int i;

	i = -1;
	while (++i < level->nb_linedef)
	{
		if (id_l == level->linedef[i].id)
			break;
	}
	if (vertex == 1)
		return (send_vx(level, level->linedef[i].id_v1));
	else
		return (send_vx(level, level->linedef[i].id_v2));
}

int send_l_vy(t_level *level, int id_l, int vertex)
{
	int i;

	i = -1;
	while (++i < level->nb_linedef)
	{
		if (id_l == level->linedef[i].id)
			break;
	}
	if (vertex == 1)
		return (send_vy(level, level->linedef[i].id_v1));
	else
		return (send_vy(level, level->linedef[i].id_v2));
}

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

void fill_form(int x1, int x2, int y1, int y2, t_mem *mem)
{
	t_line line;
	t_color color = {0, 70, 200, 0, 0};

	mem->color = color;
	line.dx = abs(x2 - x1);
	line.sx = (x1 < x2) ? 1 : -1;
	line.dy = abs(y2 - y1);
	line.sy = (y1 < y2) ? 1 : -1;
	line.err = ((line.dx > line.dy) ? line.dx : -line.dy) / 2;
	line.e2 = line.err;
	while (x1 != x2 && y1 != y2)
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
		if ((x1 > 0 && x1 < W) && -x1 % 2) // modulo 3 a suprimer pour le saut de colonnes
		{
			if (y1 > H / 2)
				draw_to_line(x1, y1, x1, (H / 2), mem);
			else
				draw_to_line(x1, y1, x1, (H / 2) + 1, mem);
		}
	}
}

void change_color(t_color *color, int hex)
{
	color->r = hex >> 16;
	color->g = hex >> 8;
	color->b = hex;
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

			mem->coord.x1 = tx1 + 150; //(mem->z * 0.01 * mem->level->player.x);
			mem->coord.x2 = tx2 + 150; //(mem->z * 0.01 * mem->level->player.x);
			mem->coord.y1 = tz1 + 150; //(mem->z * 0.01 * mem->level->player.y);
			mem->coord.y2 = tz2 + 150; //(mem->z * 0.01 * mem->level->player.y);

			if (tz1 > 0 || tz2 > 0)
			{
				intersect(tx1, tz1, tx2, tz2, -0.0001, 0.0001, -30, 5, &ix1, &iz1);
				intersect(tx1, tz1, tx2, tz2, 0.0001, 0.0001, 30, 5, &ix2, &iz2);
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
				x1 = -tx1 * 800 / tz1;
				x2 = -tx2 * 800 / tz2;
				y1a = -H * 5 / tz1;
				y2a = -H * 5 / tz2;
				y1b = H * 5 / tz1;
				y2b = H * 5 / tz2;
			}

			change_color(&mem->color, 0xaf2215);

			fill_form(W / 2 + x1, W / 2 + x2, H / 2 + y1a, H / 2 + y2a, mem);
			fill_form(W / 2 + x1, W / 2 + x2, H / 2 + y1b, H / 2 + y2b, mem);

			change_color(&mem->color, 0xffff00);

			draw_to_line((W / 2 + x1), (H / 2 + y1a), (W / 2 + x2), (H / 2 + y2a), mem);
			draw_to_line((W / 2 + x1), (H / 2 + y1b), (W / 2 + x2), (H / 2 + y2b), mem);
			draw_to_line((W / 2 + x1), (H / 2 + y1a), (W / 2 + x1), (H / 2 + y1b), mem);
			draw_to_line((W / 2 + x2), (H / 2 + y2a), (W / 2 + x2), (H / 2 + y2b), mem);

			change_color(&mem->color, 0xa81291);

			draw_circle(mem);
			draw_line(mem);
			draw_circle(mem);
		}
	}
	//player position
	mem->coord.x1 = 150;
	mem->coord.y1 = 150;
	draw_circle(mem);
	mem->coord.x2 = 150;
	mem->coord.y2 = 150 + 30;

	draw_line(mem);
}

int update_keys(t_mem *mem)
{

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
		mem->level->player.angle -= 0.05;
	}
	if (mem->level->player.keyspressed & ROTATE_RIGHT)
	{
		mem->level->player.angle += 0.05;
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
