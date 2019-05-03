/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 18:25:11 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

/*void draw_minimap(t_mem *mem)
{
	int i;
	int j;
	t_vector vec;

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
			vec.tx1 = mem->coord.x1 - mem->level->player.x;
			vec.tx2 = mem->coord.x2 - mem->level->player.x;
			vec.ty1 = mem->coord.y1 - mem->level->player.y;
			vec.ty2 = mem->coord.y2 - mem->level->player.y;
			vec.tz1 = vec.tx1 * mem->cos_angle + vec.ty1 * mem->sin_angle;
			vec.tz2 = vec.tx2 * mem->cos_angle + vec.ty2 * mem->sin_angle;
			vec.tx1 = vec.tx1 * mem->sin_angle - vec.ty1 * mem->cos_angle;
			vec.tx2 = vec.tx2 * mem->sin_angle - vec.ty2 * mem->cos_angle;
			mem->coord.x1 = vec.tx1 + 150;
			mem->coord.x2 = vec.tx2 + 150;
			mem->coord.y1 = vec.tz1 + 150;
			mem->coord.y2 = vec.tz2 + 150;
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
*/

t_line line_init(t_fcoord p)
{
	t_line line;

	line.dx = abs((int)p.x2 - (int)p.x1);
	line.sx = ((int)p.x1 < (int)p.x2) ? 1 : -1;
	line.dy = abs((int)p.y2 - (int)p.y1);
	line.sy = ((int)p.y1 < (int)p.y2) ? 1 : -1;
	line.err = ((line.dx > line.dy) ? line.dx : -line.dy) * 0.5;
	line.e2 = line.err;
	return (line);
}

void calc_linedef_one(t_fcoord *pf1, t_fcoord *pf2, t_fcoord *step, t_fcoord *top, t_mem *mem)
{
	if (mem->line.e2 > -mem->line.dx)
	{
		mem->line.err -= mem->line.dy;
		pf1->x1 += mem->line.sx;
		mem->line2.err -= mem->line2.dy;
		pf2->x1 += mem->line2.sx;
		mem->line3.err -= mem->line3.dy;
		step->x1 += mem->line3.sx;
		mem->line4.err -= mem->line4.dy;
		top->x1 += mem->line4.sx;
	}
}

void calc_linedef_two(t_fcoord *pf1, t_fcoord *pf2, t_fcoord *step, t_fcoord *top, t_mem *mem)
{
	if (mem->line.e2 < mem->line.dy)
	{
		mem->line.err += mem->line.dx;
		pf1->y1 += mem->line.sy;
	}
	if (mem->line2.e2 < mem->line2.dy)
	{
		mem->line2.err += mem->line2.dx;
		pf2->y1 += mem->line2.sy;
	}
	if (mem->line3.e2 < mem->line3.dy)
	{
		mem->line3.err += mem->line3.dx;
		step->y1 += mem->line3.sy;
	}
	if (mem->line4.e2 < mem->line4.dy)
	{
		mem->line4.err += mem->line4.dx;
		top->y1 += mem->line4.sy;
	}
}

void set_column(t_fcoord pf1, t_fcoord pf2, t_fcoord step, t_fcoord top, t_mem *mem)
{
	mem->p3.y1 = (int)pf1.y1 - mem->camera_y + mem->level->player.recoil;
	mem->p3.y2 = (int)pf2.y1 - mem->camera_y + mem->level->player.recoil;
	mem->p4.y1 = mem->p3.y2;
	mem->p4.y2 = (int)step.y1 - mem->camera_y + mem->level->player.recoil;
	mem->p5.y1 = (int)top.y1 - mem->camera_y + mem->level->player.recoil;
	mem->p5.y2 = mem->p3.y1;
}

void paint_linedef(t_fcoord pf1, t_fcoord pf2, t_fcoord step, t_fcoord top, int sect, t_mem *mem)
{
	int i;

	i = 0;
	mem->line = line_init(pf1);
	mem->line2 = line_init(pf2);
	mem->line3 = line_init(step);
	mem->line4 = line_init(top);
	while ((int)pf1.x1 != (int)pf1.x2)
	{
		mem->line.e2 = mem->line.err;
		mem->line2.e2 = mem->line2.err;
		mem->line3.e2 = mem->line3.err;
		mem->line4.e2 = mem->line4.err;
		if (i++)
		{
			calc_linedef_one(&pf1, &pf2, &step, &top, mem);
			calc_linedef_two(&pf1, &pf2, &step, &top, mem);
		}
		if (((int)pf1.x1 >= 0 && (int)pf1.x1 < W))
		{
			set_column(pf1, pf2, step, top, mem);
			fill_column((int)pf1.x1, sect, mem);
		}
	}
}

void calc_linedef(t_fcoord pf1, t_mem *mem)
{
	int i;
	int j;

	i = 0;
	if ((int)pf1.x1 < (int)pf1.x2)
		j = 1;
	else
		j = -1;
	while ((int)pf1.x1 != (int)pf1.x2)
	{
		pf1.x1 += j;
		if (((int)pf1.x1 >= 0 && (int)pf1.x1 < W))
		{
			mem->fill_screen[(int)pf1.x1] = 1;
		}
	}
}

t_vector calc_wall(t_mem *mem, t_vector vec, int sect, int j)
{
	mem->coord.x1 = send_l_vx(mem->level, mem->level->sector[sect].linedef[j], 1);
	mem->coord.y1 = send_l_vy(mem->level, mem->level->sector[sect].linedef[j], 1);
	mem->coord.x2 = send_l_vx(mem->level, mem->level->sector[sect].linedef[j], 2);
	mem->coord.y2 = send_l_vy(mem->level, mem->level->sector[sect].linedef[j], 2);
	vec.tx1 = mem->coord.x1 - mem->level->player.x;
	vec.tx2 = mem->coord.x2 - mem->level->player.x;
	vec.ty1 = mem->coord.y1 - mem->level->player.y;
	vec.ty2 = mem->coord.y2 - mem->level->player.y;
	vec.tz1 = vec.tx1 * mem->cos_angle + vec.ty1 * mem->sin_angle;
	vec.tz2 = vec.tx2 * mem->cos_angle + vec.ty2 * mem->sin_angle;
	vec.tx1 = vec.tx1 * mem->sin_angle - vec.ty1 * mem->cos_angle;
	vec.tx2 = vec.tx2 * mem->sin_angle - vec.ty2 * mem->cos_angle;
	return (vec);
}

t_vector pre_calc_vec(t_vector vec)
{
	intersect(vec.tx1, vec.tz1, vec.tx2, vec.tz2, -5, 5, -20, 5, &vec.ix1, &vec.iz1); // 7eme argument definit la precision
	if (vec.tz1 <= 0 && vec.iz1 > 0)
	{
		vec.tx1 = vec.ix1;
		vec.tz1 = vec.iz1;
	}
	if (vec.tz2 <= 0 && vec.iz1 > 0)
	{
		vec.tx2 = vec.ix1;
		vec.tz2 = vec.iz1;
	}
	return (vec);
}

t_vector calc_vec(t_vector vec)
{
	intersect(vec.tx1, vec.tz1, vec.tx2, vec.tz2, -5, 5, -20, 5, &vec.ix1, &vec.iz1); // 7eme argument definit la precision
	intersect(vec.tx1, vec.tz1, vec.tx2, vec.tz2, 5, 5, 20, 5, &vec.ix2, &vec.iz2);   // 7eme argument definit la precision
	if (vec.iz1 > 0 && vec.tz1 <= 0)
	{
		vec.tx1 = vec.ix1;
		vec.tz1 = vec.iz1;
	}
	else if (vec.tz1 <= 0)
	{
		vec.tx1 = vec.ix2;
		vec.tz1 = vec.iz2;
	}
	if (vec.iz1 > 0 && vec.tz2 <= 0)
	{
		vec.tx2 = vec.ix1;
		vec.tz2 = vec.iz1;
	}
	else if (vec.tz2 <= 0)
	{
		vec.tx2 = vec.ix2;
		vec.tz2 = vec.iz2;
	}
	return (vec);
}

int pre_render(t_mem *mem, int sect, int i)
{
	int j;
	t_fcoord p1;
	t_vector vec;

	j = -1;
	while (++j < mem->level->sector[sect].nb_linedef)
	{
		vec = calc_wall(mem, vec, sect, j);
		if (vec.tz1 > 0 || vec.tz2 > 0)
		{
			vec = pre_calc_vec(vec);
			p1.x1 = -vec.tx1 * 800 / vec.tz1 + (W >> 1); // 800 (ratio map)
			p1.x2 = -vec.tx2 * 800 / vec.tz2 + (W >> 1);
			mem->color.a = 0;
			change_color(&mem->color, mem->level->c[mem->level->linedef[send_l_id(mem, mem->level->sector[sect].linedef[j])].side.text[0]]);
		}
		if (!(mem->color.r == 255 && mem->color.g == 0 && mem->color.b == 0))
			calc_linedef(p1, mem);
		if (further_sector(mem, sect) != -1)
			return (i);
	}
	return (-1);
}

void render_calc(t_render *coor, t_vector *vec, t_mem *mem, int sect)
{
	intersect(vec->tx1, vec->tz1, vec->tx2, vec->tz2, -5, 5, -20, 5, &vec->ix1, &vec->iz1); // 7eme argument definit la precision
	intersect(vec->tx1, vec->tz1, vec->tx2, vec->tz2, 5, 5, 20, 5, &vec->ix2, &vec->iz2);   // 7eme argument definit la precision
	*vec = calc_vec(*vec);
	coor->p1.x1 = -vec->tx1 * 800 / vec->tz1 + (W >> 1); // 800 (ratio map)
	coor->p1.x2 = -vec->tx2 * 800 / vec->tz2 + (W >> 1);
	coor->p2.x1 = coor->p1.x1;
	coor->p2.x2 = coor->p1.x2;
	coor->step.x1 = coor->p1.x1;
	coor->step.x2 = coor->p1.x2;
	coor->top.x1 = coor->p1.x1;
	coor->top.x2 = coor->p1.x2;
	coor->p1.y1 = H * (mem->level->player.z - mem->level->sector[sect].h_ceil) / vec->tz1 + (H >> 1);
	coor->p1.y2 = H * (mem->level->player.z - mem->level->sector[sect].h_ceil) / vec->tz2 + (H >> 1); // transformer cette valeur pour plafond penché
	coor->p2.y1 = H * (mem->level->player.z - mem->level->sector[sect].h_floor) / vec->tz1 + (H >> 1);
	coor->p2.y2 = H * (mem->level->player.z - mem->level->sector[sect].h_floor) / vec->tz2 + (H >> 1); // // transformer cette valeur pour sol penché
}

void render_update(t_mem *mem, int *neighbour, t_render *coor, t_vector vec, int sect)
{
	if (!(mem->level->linedef[send_l_id(mem, mem->level->sector[sect].linedef[j])].side.text[0]))
		*neighbour = next_sector(mem, mem->level->sector[sect].linedef[j], sect);
	if (mem->level->sector[*neighbour].h_floor >= mem->level->sector[sect].h_floor && *neighbour > 0)
	{
		coor->step.y1 = coor->p2.y1;
		coor->step.y2 = coor->p2.y2;
		coor->p2.y1 = H * (mem->level->player.z - mem->level->sector[sect].h_floor) / vec.tz1 + (H >> 1) - fabs(H * ((mem->level->player.z - mem->level->sector[*neighbour].h_floor)) / vec.tz1 + (H >> 1) - coor->p2.y1);
		coor->p2.y2 = H * (mem->level->player.z - mem->level->sector[sect].h_floor) / vec.tz2 + (H >> 1) - fabs(H * ((mem->level->player.z - mem->level->sector[*neighbour].h_floor)) / vec.tz2 + (H >> 1) - coor->p2.y2);
	}
	else
	{
		coor->step.y1 = coor->p2.y1;
		coor->step.y2 = coor->p2.y2;
	}
	if (mem->level->sector[*neighbour].h_ceil <= mem->level->sector[sect].h_ceil && *neighbour > 0)
	{
		coor->top.y1 = coor->p1.y1;
		coor->top.y2 = coor->p1.y2;
		coor->p1.y1 = H * (mem->level->player.z - mem->level->sector[sect].h_ceil) / vec.tz1 + (H >> 1) + fabs(H * ((mem->level->player.z - mem->level->sector[*neighbour].h_ceil)) / vec.tz1 + (H >> 1) - coor->p1.y1);
		coor->p1.y2 = H * (mem->level->player.z - mem->level->sector[sect].h_ceil) / vec.tz2 + (H >> 1) + fabs(H * ((mem->level->player.z - mem->level->sector[*neighbour].h_ceil)) / vec.tz2 + (H >> 1) - coor->p1.y2);
	}
	else
	{
		coor->top.y1 = coor->p1.y1;
		coor->top.y2 = coor->p1.y2;
	}
}

void render(t_mem *mem, int sect)
{
	int j;
	t_render coor;
	t_vector vec;
	int neighbour;

	neighbour = -1;
	mlx_clear_window(mem->mlx_ptr, mem->win.win_ptr);
	j = -1;
	while (++j < mem->level->sector[sect].nb_linedef)
	{
		neighbour = 0;
		vec = calc_wall(mem, vec, sect, j);
		if (vec.tz1 > 0 || vec.tz2 > 0)
		{
			render_calc(&coor, &vec, mem, sect);
			render_update(mem, &neighbour, &coor, vec, sect);
			mem->color.a = 0;
			change_color(&mem->color, mem->level->c[mem->level->linedef[send_l_id(mem, mem->level->sector[sect].linedef[j])].side.text[0]]);
		}
		paint_linedef(coor.p1, coor.p2, coor.step, coor.top, sect, mem);
		further_sector(mem, sect);
	}
}

void refresh_screen(t_mem *mem)
{
	int i;
	int j;

	j = -1;
	bzero(mem->fill_screen, (sizeof(char) * W));
	if (mem->img.ptr)
		mlx_destroy_image(mem->mlx_ptr, mem->img.ptr);
	ft_create_img(mem);
	i = -1;
	while (++i < mem->level->nb_sector)
	{
		j = pre_render(mem, send_s_id(mem, mem->level->n_sector[i]), i);
		if (j != -1)
			break;
	}
	while (i > -1)
	{
		render(mem, send_s_id(mem, mem->level->n_sector[i]));
		render_sprites(mem, send_s_id(mem, mem->level->n_sector[i--]));
	}
	if (mem->level->player.shoot > 0)
		shoot(mem, mem->level->player.shoot);
	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->img.ptr, 0, 0);
	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->gun.ptr, (W * 0.4) + 200 + (int)mem->level->player.motion + mem->level->player.recoil, (H >> 1) + (int)mem->level->player.motion + mem->level->player.recoil);
	mlx_put_image_to_window(mem->mlx_ptr, mem->win.win_ptr, mem->crosshair.ptr, (W >> 1) - 16, (H >> 1) - 16);
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

int further_sector(t_mem *mem, int sector)
{
	int i;
	int j;

	j = 0;
	i = -1;
	while (++i <= W)
	{
		if (mem->fill_screen[i])
			j++;
	}
	if (j >= W)
		return (sector);
	else
		return (-1);
}

void shoot(t_mem *mem, char frame)
{
	if (frame == 2)
	{
		change_color(&mem->color, 0xFF0000);
		draw_to_line(W >> 1, H >> 1, W - 340, H - 150, mem);
	}
	else
	{
		change_color(&mem->color, 0x0000FF);
		draw_to_line(W >> 1, H >> 1, W - 340, H - 150, mem);
	}
}