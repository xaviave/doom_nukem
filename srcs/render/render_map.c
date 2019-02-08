/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 16:59:00 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

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

int is_inside(t_vertex v1, t_vertex v2, t_vertex v3, t_vertex player)
{
	double s1;
	double s2;
	double s3;
	double s4;
	double w1;
	double w2;

	s1 = v3.y - v1.y;
	s2 = v3.x - v1.x;
	s3 = v2.y - v1.y;
	s4 = player.y - v1.y;
	w1 = (v1.x * s1 + s4 * s2 - player.x * s1) / (s3 * s2 - (v2.x - v1.x) * s1);
	w2 = (s4 - w1 * s3) / s1;
	return (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1);
}

int check_in_sector(t_mem *mem, int l1, int l2, int save)
{
	t_vertex vertex;

	if (send_v_id(mem, save) == send_v_id(mem, l1) || send_v_id(mem, save) == send_v_id(mem, l2))
		return (0);
	vertex.x = mem->level->player.x;
	vertex.y = mem->level->player.y;
	if (is_inside(mem->level->vertex[send_v_id(mem, save)],
				  mem->level->vertex[send_v_id(mem, l1)],
				  mem->level->vertex[send_v_id(mem, l2)], vertex))
		return (1);
	return (0);
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

	i = -1;
	while (++i < mem->level->nb_sector)
	{
		save = mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[0])].id_v1;
		if (in_box(mem, i) == 2)
		{
			j = 0;
			while (++j < mem->level->sector[i].nb_linedef)
				if (check_in_sector(mem, mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].id_v1, mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].id_v2, save))
					mem->level->player.sector = mem->level->sector[i].id;
		}
	}
	mem->level->n = 1;
	mem->level->n_sector[0] = mem->level->player.sector;
	fill_n_sector(mem, 0);
	return (mem->level->player.sector);
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

void paint_sector(t_fcoord pf1, t_fcoord pf2, int sect, t_mem *mem)
{
	t_line line;
	t_line line2;
	t_coord p1;
	t_coord p2;
	t_coord p3;
	int i;

	i = 0;
	p1.x1 = pf1.x1;
	p1.x2 = pf1.x2;
	p1.y1 = pf1.y1;
	p1.y2 = pf1.y2;

	p2.x1 = pf2.x1;
	p2.x2 = pf2.x2;
	p2.y1 = pf2.y1;
	p2.y2 = pf2.y2;

	line.dx = abs(p1.x2 - p1.x1);
	line.sx = (p1.x1 < p1.x2) ? 1 : -1;
	line.dy = abs(p1.y2 - p1.y1);
	line.sy = (p1.y1 < p1.y2) ? 1 : -1;
	line.err = ((line.dx > line.dy) ? line.dx : -line.dy) / 2;
	line.e2 = line.err;

	line2.dx = abs(p2.x2 - p2.x1);
	line2.sx = (p2.x1 < p2.x2) ? 1 : -1;
	line2.dy = abs(p2.y2 - p2.y1);
	line2.sy = (p2.y1 < p2.y2) ? 1 : -1;
	line2.err = ((line2.dx > line2.dy) ? line2.dx : -line2.dy) / 2;
	line2.e2 = line2.err;

	while (p1.x1 != p1.x2)
	{
		line.e2 = line.err;
		line2.e2 = line2.err;

		if (i++)
		{
			if (line.e2 > -line.dx && line2.e2 > -line2.dx)
			{
				line.err -= line.dy;
				p1.x1 += line.sx;
				line2.err -= line2.dy;
				p2.x1 += line2.sx;
			}
			if (line.e2 < line.dy)
			{
				line.err += line.dx;
				p1.y1 += line.sy;
			}
			//--------

			if (line2.e2 < line2.dy)
			{
				line2.err += line2.dx;
				p2.y1 += line2.sy;
			}
		}
		if ((p1.x1 > 0 && p1.x1 < W))
		{
			p3.y1 = p1.y1 - mem->camera_y;
			p3.y2 = p2.y1 - mem->camera_y;
			fill_column(p1.x1, p3, sect, mem);
		}
	}
}

void render(t_mem *mem, int i)
{
	int j;
	t_fcoord p1;
	t_fcoord p2;
	float tx1;
	float tx2;
	float ty1;
	float ty2;
	float tz1;
	float tz2;
	float ix1;
	float ix2;
	float iz1;
	float iz2;
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
			intersect(tx1, tz1, tx2, tz2, -2, 5, -20, 5, &ix1, &iz1); // 7eme argument definit la precision
			intersect(tx1, tz1, tx2, tz2, 2, 5, 20, 5, &ix2, &iz2);   // 7eme argument definit la precision
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
			p1.x1 = -tx1 * 800 / tz1 + W / 2; // 800 (ratio map)
			p1.x2 = -tx2 * 800 / tz2 + W / 2;
			p2.x1 = p1.x1;
			p2.x2 = p1.x2;
			p1.y1 = -H * (mem->level->sector[i].h_ceil - mem->level->player.height) / tz1 + H / 2;
			p1.y2 = -H * (mem->level->sector[i].h_ceil - mem->level->player.height) / tz2 + H / 2;

			p2.y1 = H * (mem->level->player.height - mem->level->sector[i].h_floor) / tz1 + H / 2;
			p2.y2 = H * (mem->level->player.height - mem->level->sector[i].h_floor) / tz2 + H / 2;

					//	if (mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].side.text[0] == 0)
						//	mem->color.a = 255;
						//else
					//	{
			mem->color.a = 0;
			change_color(&mem->color, mem->level->c[mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].side.text[0]]);
			//			}
		}
		if (!mem->color.a)
		{
			paint_sector(p1, p2, i, mem);
		}
	}
}

void refresh_screen(t_mem *mem)
{
	int i;

	if (mem->img.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->img.ptr);
	player_sector(mem);

	ft_create_img(mem);
	i = mem->level->nb_sector - 1;
	while (i != -1)
	{
		render(mem, send_s_id(mem, mem->level->n_sector[i]));
		i--;
	}
	/*

	i = -1;
	while(++i < mem->level->nb_sector)
		render(mem, i);
	render(mem, send_v_id(mem, mem->level->player.sector));
	*/
	draw_minimap(mem);
	//mem->level->player->sector
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
