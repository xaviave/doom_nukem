/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_calculate.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 10:23:01 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_vector		calc_vec(t_vector vec)
{
	intersect(vec, &vec.ix1, &vec.iz1);
	intersect_down(vec, &vec.ix2, &vec.iz2);
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

void			calc_linedef_one(t_render *coor, t_mem *mem)
{
	if (mem->line.e2 > -mem->line.dx)
	{
		mem->line.err -= mem->line.dy;
		coor->p1.x1 += mem->line.sx;
		mem->line2.err -= mem->line2.dy;
		coor->p2.x1 += mem->line2.sx;
		mem->line3.err -= mem->line3.dy;
		coor->step.x1 += mem->line3.sx;
		mem->line4.err -= mem->line4.dy;
		coor->top.x1 += mem->line4.sx;
	}
}

void			calc_linedef_two(t_render *coor, t_mem *mem)
{
	if (mem->line.e2 < mem->line.dy)
	{
		mem->line.err += mem->line.dx;
		coor->p1.y1 += mem->line.sy;
	}
	if (mem->line2.e2 < mem->line2.dy)
	{
		mem->line2.err += mem->line2.dx;
		coor->p2.y1 += mem->line2.sy;
	}
	if (mem->line3.e2 < mem->line3.dy)
	{
		mem->line3.err += mem->line3.dx;
		coor->step.y1 += mem->line3.sy;
	}
	if (mem->line4.e2 < mem->line4.dy)
	{
		mem->line4.err += mem->line4.dx;
		coor->top.y1 += mem->line4.sy;
	}
}

t_vector		calc_wall(t_mem *mem, t_vector vec, int s, int j)
{
	mem->coord.x1 = send_l_vx(mem->level, mem->level->sector[s].linedef[j], 1);
	mem->coord.y1 = send_l_vy(mem->level, mem->level->sector[s].linedef[j], 1);
	mem->coord.x2 = send_l_vx(mem->level, mem->level->sector[s].linedef[j], 2);
	mem->coord.y2 = send_l_vy(mem->level, mem->level->sector[s].linedef[j], 2);
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

void			calc_minimap(t_mem *mem, int i, int j, t_vector *vec)
{
	mem->coord.x1 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 1);
	mem->coord.y1 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 1);
	mem->coord.x2 = send_l_vx(mem->level, mem->level->sector[i].linedef[j], 2);
	mem->coord.y2 = send_l_vy(mem->level, mem->level->sector[i].linedef[j], 2);
	vec->tx1 = mem->coord.x1 - mem->level->player.x;
	vec->tx2 = mem->coord.x2 - mem->level->player.x;
	vec->ty1 = mem->coord.y1 - mem->level->player.y;
	vec->ty2 = mem->coord.y2 - mem->level->player.y;
	vec->tz1 = vec->tx1 * mem->cos_angle + vec->ty1 * mem->sin_angle;
	vec->tz2 = vec->tx2 * mem->cos_angle + vec->ty2 * mem->sin_angle;
	vec->tx1 = vec->tx1 * mem->sin_angle - vec->ty1 * mem->cos_angle;
	vec->tx2 = vec->tx2 * mem->sin_angle - vec->ty2 * mem->cos_angle;
	mem->coord.x1 = vec->tx1 + W / 2;
	mem->coord.x2 = vec->tx2 + W / 2;
	mem->coord.y1 = vec->tz1 + H / 2;
	mem->coord.y2 = vec->tz2 + H / 2;
	draw_line(mem);
}
