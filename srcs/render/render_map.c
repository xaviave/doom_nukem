/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/06 11:53:46 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void fill_form(int x1, int x2, int y1, int y2, t_mem *mem)
{
	t_line line;
	int i;

	i = 0;
	line.dx = abs(x2 - x1);
	line.sx = (x1 < x2) ? 1 : -1;
	line.dy = abs(y2 - y1);
	line.sy = (y1 < y2) ? 1 : -1;
	line.err = ((line.dx > line.dy) ? line.dx : -line.dy) / 2;
	line.e2 = line.err;
	while (x1 != x2 || y1 != y2)
	{

		if (i++)
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

int send_s_id(t_mem *mem, int id)
{
	int i;

	i = -1;
	while (++i < mem->level->nb_sector)
	{
		if (mem->level->sector[i].id == id)
			return (i);
	}
	return (0);
}

int send_v_id(t_mem *mem, int id)
{
	int i;

	i = -1;
	while (++i < mem->level->nb_vertex)
	{
		if (mem->level->vertex[i].id == id)
			return (i);
	}
	return (0);
}

void send_x(t_coord *coord, t_mem *mem, int l)
{
	int x1;
	int x2;

	x1 = send_l_vx(mem->level, l, 1);
	x2 = send_l_vx(mem->level, l, 2);
	if (x1 < x2)
	{
		coord->x1 = (coord->x1 == -1 || coord->x1 > x1) ? x1 : coord->x1;
		coord->x2 = (coord->x2 == -1 || coord->x2 < x2) ? x2 : coord->x2;
		return;
	}
	coord->x1 = (coord->x1 == -1 || coord->x1 > x2) ? x2 : coord->x1;
	coord->x2 = (coord->x2 == -1 || coord->x2 < x1) ? x1 : coord->x2;
}

void send_y(t_coord *coord, t_mem *mem, int l)
{
	int y1;
	int y2;

	y1 = send_l_vy(mem->level, l, 1);
	y2 = send_l_vy(mem->level, l, 2);
	if (y1 < y2)
	{
		coord->y1 = (coord->y1 == -1 || coord->y1 > y1) ? y1 : coord->y1;
		coord->y2 = (coord->y2 == -1 || coord->y2 < y2) ? y2 : coord->y2;
		return;
	}
	coord->y1 = (coord->y1 == -1 || coord->y1 > y2) ? y2 : coord->y1;
	coord->y2 = (coord->y2 == -1 || coord->y2 < y1) ? y1 : coord->y2;
}

int in_box(t_mem *mem, int nb)
{
	int i;

	i = -1;
	mem->coord.x1 = -1;
	mem->coord.x2 = -1;
	mem->coord.y1 = -1;
	mem->coord.y2 = -1;
	while (++i < mem->level->sector[nb].nb_linedef)
	{
		send_x(&mem->coord, mem, mem->level->sector[nb].linedef[i]);
		send_y(&mem->coord, mem, mem->level->sector[nb].linedef[i]);
	}
	i = 0;
	if ((mem->level->player.x > mem->coord.x1 && mem->level->player.x < mem->coord.x2) || (mem->level->player.x == mem->coord.x1 || mem->level->player.x == mem->coord.x2))
		i++;
	if ((mem->level->player.y > mem->coord.y1 && mem->level->player.y < mem->coord.y2) || (mem->level->player.y == mem->coord.y1 || mem->level->player.y == mem->coord.y2))
		i++;
	return (i);
}

float sign(t_vertex v1, t_vertex v2, t_vertex v3)
{
	return ((v1.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (v1.y - v3.y));
}

int check_in_sector(t_mem *mem, int l1, int l2, int save)
{
	t_vertex vertex;
	int b1;
	int b2;
	int b3;

	if (send_v_id(mem, save) == send_v_id(mem, l1) || send_v_id(mem, save) == send_v_id(mem, l2))
		return (0);
	vertex.x = mem->level->player.x;
	vertex.y = mem->level->player.y;
	b1 = sign(vertex, mem->level->vertex[send_v_id(mem, save)],
			  mem->level->vertex[send_v_id(mem, l1)]) < 0.0f;
	b2 = sign(vertex, mem->level->vertex[send_v_id(mem, l1)],
			  mem->level->vertex[send_v_id(mem, l2)]) < 0.0f;
	b3 = sign(vertex, mem->level->vertex[send_v_id(mem, l2)],
			  mem->level->vertex[send_v_id(mem, save)]) < 0.0f;
	dprintf(1, "%d %d %d | %d\n", b1, b2, b3, ((b1 == b2) && (b2 == b3)));
	return ((b1 == b2) && (b2 == b3));
}

int double_int(int *tab, int nu, int nb)
{
	int i;

	i = -1;
	while (++i < nb)
	{
		if (tab[i] == nu)
			return (0);
	}
	return (1);
}

int player_sector(t_mem *mem)
{
	int i;
	int j;
	int save;
	int sector;

	i = -1;
	sector = -1;
	while (++i < mem->level->nb_sector)
	{
		save = mem->level->linedef[mem->level->sector[i].linedef[0]].id_v1;
		if (in_box(mem, i) == 2)
		{
			j = 0;
			dprintf(1, "sector = %d\n", mem->level->sector[i].id);
			while (++j < mem->level->sector[i].nb_linedef)
				if (check_in_sector(mem, mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].id_v1, mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].id_v2, save))
					sector = mem->level->sector[i].id;
		}
	}
	mem->level->n = 1;
	mem->level->n_sector[0] = sector;
	printf("Actual sector = %d | (%f %f) | %d\n", sector, mem->level->player.x, mem->level->player.y, mem->z);
	return (sector);
}

void search_sector(t_mem *mem, int id, int ok)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < mem->level->nb_sector)
	{
		if (mem->level->sector[i].id == id)
			break;
	}
	while (++j < mem->level->sector[i].nb_neighbors)
	{
		if (double_int(mem->level->n_sector, mem->level->sector[i].neighbors[j], mem->level->n))
		{
			mem->level->n_sector[mem->level->n] = mem->level->sector[i].neighbors[j];
			mem->level->n++;
		}
	}
	if (mem->level->n < mem->level->nb_sector)
		search_sector(mem, mem->level->n_sector[ok], ok + 1);
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

	/* player position */

	change_color(&mem->color, 0xffffff);
	i = -1;
	while (++i < mem->level->nb_sector)
	{
		j = -1;
		while (++j < mem->level->sector[i].nb_linedef)
		{
			mem->coord.x1 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 1);
			mem->coord.y1 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 1);
			mem->coord.x2 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 2);
			mem->coord.y2 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 2);
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

void render(t_mem *mem, int i)
{
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
	dprintf(1, "i sector = %d | id sector = %d | sol =  %d\n", i, mem->level->n_sector[0], mem->level->sector[i].h_floor);
	mlx_clear_window(mem->mlx_ptr, mem->win.win_ptr);

	j = -1;
	while (++j < mem->level->sector[i].nb_linedef)
	{
		mem->coord.x1 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 1);
		mem->coord.y1 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 1);
		mem->coord.x2 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 2);
		mem->coord.y2 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 2);
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
			intersect(tx1, tz1, tx2, tz2, -5, 5, -20, 5, &ix1, &iz1); // 7eme argument definit la precision
			intersect(tx1, tz1, tx2, tz2, 5, 5, 20, 5, &ix2, &iz2);   // 7eme argument definit la precision
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

			y1a = -H * (5 + mem->level->sector[i].h_ceil) / tz1 + H / 2;
			y2a = -H * (5 + mem->level->sector[i].h_ceil) / tz2 + H / 2;


			y1b = H * (5 - mem->level->sector[i].h_floor) / tz1 + H / 2;
			y2b = H * (5 - mem->level->sector[i].h_floor) / tz2 + H / 2;

			//	if (mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].side.text[0] == 0)
			//		mem->color.a = 255;
			//	else
			//	{
			mem->color.a = 0;
			change_color(&mem->color, mem->level->c[mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].side.text[0]]);
			//	}
		}
		if (!mem->color.a)
		{
			fill_form(x1, x2, y1a + i, y2a + i, mem);
			fill_form(x1, x2, y1b + i, y2b + i, mem);
		}
	}
}

void refresh_screen(t_mem *mem)
{
	int i;

	if (mem->img.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->img.ptr);
	player_sector(mem);
	if (mem->level->n_sector[0] == -1)
	{
		i = -1;
		while (++i < mem->level->nb_sector)
			mem->level->n_sector[i] = mem->level->sector[i].id;
	}
	else
		(mem->level->nb_sector > 1 && mem->level->n_sector[0] > 0) ? search_sector(mem, mem->level->n_sector[0], 0) : 0;

	ft_create_img(mem);
	render(mem, send_v_id(mem, mem->level->n_sector[0]));
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
