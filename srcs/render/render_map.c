/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 17:02:19 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void fill_form(int x1, int x2, int y1, int y2, t_mem *mem)
{
	t_line line;
	t_color colorCeil;
	t_color colorFloor;
	int light;

	line.dx = abs(x2 - x1);
	line.sx = (x1 < x2) ? 1 : -1;
	line.dy = abs(y2 - y1);
	line.sy = (y1 < y2) ? 1 : -1;
	line.err = ((line.dx > line.dy) ? line.dx : -line.dy) / 2;
	line.e2 = line.err;

	change_color(&colorCeil, 0x666666);
	change_color(&colorFloor, 0x0022FF);
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
			if (y1 < (H / 2))
			{
				fill_column(x1, 0, y1 - mem->camera_y, colorCeil, mem); // plafond
			}
			else if (y1 > (H / 2))
			{
				fill_column(x1, H, y1 - mem->camera_y, colorFloor, mem); // sol
			}
			light = abs(y1 - (H / 2)) * 0.20;
			fill_column(x1, y1 - mem->camera_y, (H / 2) - mem->camera_y, add_rgb(mem->color, light, light, light), mem); // murs
		}
	}
}

int	*send_vertex(t_mem *mem, int *linedef)
{
	int	i;
	int	j;
	int	k;
	int ok;
	int	*test;

	i = -1;
	j = 0;
	if (linedef)
	;
	test = malloc(sizeof(int) * mem->level->sector[mem->level->player.sector].nb_vertex);
	ft_bzero(&test, mem->level->sector[mem->level->player.sector].nb_vertex);
	while (++i < mem->level->nb_linedef)
	{
		ok = 0;
		k = -1;
		while (j && ++k < mem->level->sector[mem->level->player.sector].nb_vertex)
		{
			if (test[k] && mem->level->sector[i].linedef[j] == test[k])
			
				ok = 1;
		}
		if (ok && !test[j])
		{
			 test[j] = mem->level->sector[i].linedef[j];
			 j++;
		}
	}
	return (test);
}

void MovePlayer(float dx, float dy, t_mem *mem)
{
	/* dx = player.x + 1.2f * cos(player.angle) */
	/* dy = player.y + 1.2f * sin(player.angle) */
    float px = mem->level->player.x, py = mem->level->player.y;
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    t_sector *sect = &mem->level->sector[send_s_id(mem, mem->level->player.sector)];
    int *vert = send_vertex(mem, sect->linedef); // mettre tout les vertex des linedefs dedans
    for(int s = 0; s < sect->nb_linedef; ++s)
        if(sect->nb_neighbors >= 0
        && IntersectBox(px,py, px+dx,py+dy, send_vx(mem->level, vert[s+0]), send_vy(mem->level, vert[s+0]), send_vx(mem->level, vert[s+1]), send_vy(mem->level, vert[s+1]))
        && PointSide(px+dx, py+dy, send_vx(mem->level, vert[s+0]), send_vy(mem->level, vert[s+0]), send_vx(mem->level, vert[s+1]), send_vy(mem->level, vert[s+1])) < 0)
        {
            mem->level->player.sector = sect->neighbors[s];
            break;
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
	while (++i < 1) //mem->level->nb_sector
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

				y1a = -H * mem->level->sector[i].h_ceil / tz1 + H / 2;
				y2a = -H * mem->level->sector[i].h_ceil / tz2 + H / 2;

				y1b = H * (5 - mem->level->sector[i].h_floor) / tz1 + H / 2;
				y2b = H * (5 - mem->level->sector[i].h_floor) / tz2 + H / 2;

				//	if (mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].side.text[0] == 0)
				//		mem->color.a = 255;
				//	else
				//	{
				//		mem->color.a = 0;

				//	if (mem->level->c[mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].side.text[0]] == 0xfc522f)
				//	{
				// afficher juste la partie basse
				//	y1a = H / 2;
				//	y2a = H / 2;

				//	y1b = H * (5 - mem->level->sector[i].h_floor) / tz1 + H / 2;
				//	y2b = H * (5 - mem->level->sector[i].h_floor) / tz2 + H / 2;
				//	}
				change_color(&mem->color, mem->level->c[mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].side.text[0]]);
			}
			//	}
			if (!mem->color.a)
			{
				fill_form(x1, x2, y1a + i, y2a + i, mem);
				fill_form(x1, x2, y1b + i, y2b + i, mem);
			}
		}
	}

	/* player position */
	mem->color.a = 0;
	change_color(&mem->color, 0xffffff);
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
