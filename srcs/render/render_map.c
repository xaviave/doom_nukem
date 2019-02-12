/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 18:16:59 by mel-akio    ###    #+. /#+    ###.fr     */
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

t_line line_init(t_fcoord p)
{
	t_line line;

	line.dx = abs((int)p.x2 - (int)p.x1);
	line.sx = ((int)p.x1 < (int)p.x2) ? 1 : -1;
	line.dy = abs((int)p.y2 - (int)p.y1);
	line.sy = ((int)p.y1 < (int)p.y2) ? 1 : -1;
	line.err = ((line.dx > line.dy) ? line.dx : -line.dy) / 2;
	line.e2 = line.err;

	return (line);
}

void paint_sector(t_fcoord pf1, t_fcoord pf2, t_fcoord step, int sect, t_mem *mem)
{
	t_line line;
	t_line line2;
	t_line line3;

	t_coord p3;
	t_coord p4;
	int i;

	i = 0;

	line = line_init(pf1);
	line2 = line_init(pf2);
	line3 = line_init(step);

	while ((int)pf1.x1 != (int)pf1.x2)
	{
		line.e2 = line.err;
		line2.e2 = line2.err;
		line3.e2 = line3.err;

		if (i++)
		{
			if (line.e2 > -line.dx)
			{
				line.err -= line.dy;
				pf1.x1 += line.sx;
				line2.err -= line2.dy;
				pf2.x1 += line2.sx;

				line3.err -= line3.dy;
				step.x1 += line3.sx;
			}
			if (line.e2 < line.dy)
			{
				line.err += line.dx;
				pf1.y1 += line.sy;
			}
			//--------

			if (line2.e2 < line2.dy)
			{
				line2.err += line2.dx;
				pf2.y1 += line2.sy;
			}
			if (line3.e2 < line3.dy)
			{
				line3.err += line3.dx;
				step.y1 += line3.sy;
			}
		}
		if (((int)pf1.x1 > 0 && (int)pf1.x1 < W))
		{
			p3.y1 = (int)pf1.y1 - mem->camera_y;
			p3.y2 = (int)pf2.y1 - mem->camera_y;

			p4.y1 = p3.y2;
			p4.y2 = (int)step.y1 - mem->camera_y;

			fill_column((int)pf1.x1, p3, p4, sect, mem);
		}
	}
}

void render(t_mem *mem, int i, int iter)
{
	int j;
	t_fcoord p1;
	t_fcoord p2;
	t_fcoord step;
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
			step.x1 = p1.x1;
			step.x2 = p1.x2;

			p1.y1 = -H * (mem->level->sector[i].h_ceil - mem->level->player.z) / tz1 + H / 2;
			p1.y2 = -H * (mem->level->sector[i].h_ceil - mem->level->player.z) / tz2 + H / 2;

			p2.y1 = H * (mem->level->player.z - mem->level->sector[i].h_floor) / tz1 + H / 2;
			p2.y2 = H * (mem->level->player.z - mem->level->sector[i].h_floor) / tz2 + H / 2;

			// step sont les coordones qui partente du haut du sol suivant au haut de notre sol
			if (iter - 1 > 0)
			{
				step.y1 = H * (mem->level->player.z - mem->level->sector[send_s_id(mem, mem->level->n_sector[iter - 1])].h_floor) / tz1 + H / 2;
				step.y2 = H * (mem->level->player.z - mem->level->sector[send_s_id(mem, mem->level->n_sector[iter - 1])].h_floor) / tz2 + H / 2;

				printf("%f sol actuel , %f sol voisin\n", p1.y1, step.y1);
			}
			else
			{
				step.y1 = p2.y1 + 1;
				step.y2 = p2.y2 + 1;
			}
			

			//step.y1 = H * (mem->level->player.z - mem->level->sector[send_s_id(mem, mem->level->n_sector[iter + 1])].h_floor) / tz1 + H / 2;
			//step.y2 = H * (mem->level->player.z - mem->level->sector[send_s_id(mem, mem->level->n_sector[iter + 1])].h_floor) / tz2 + H / 2;
			//send_s_id(mem, mem->level->n_sector[iter - 1])].h_floor)

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
			paint_sector(p1, p2, step, i, mem);
		}
	}
}

void refresh_screen(t_mem *mem)
{
	int i;

	if (mem->img.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->img.ptr);

	ft_create_img(mem);
	i = mem->level->nb_sector - 1;
	while (i != -1)
	{
		render(mem, send_s_id(mem, mem->level->n_sector[i]), i);
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
