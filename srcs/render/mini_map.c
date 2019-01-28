/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mini_map.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cmerel <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 14:18:50 by cmerel       #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 14:20:20 by cmerel      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void		init(t_mem *mem)
{
	if (mem->b.tz2 <= 0)
	{
		if (mem->b.iz1 > 0)
		{
			mem->b.tx2 = mem->b.ix1;
			mem->b.tz2 = mem->b.iz1;
		}
		else
		{
			mem->b.tx2 = mem->b.ix2;
			mem->b.tz2 = mem->b.iz2;
		}
	}
}

static void		draw(t_mem *mem)
{
	mem->b.j = -1;
	while (++mem->b.j < mem->level->sector[mem->b.i].nb_linedef)
	{
		mem->coord.x1 = send_l_vx(mem->level,
				mem->level->sector[mem->b.i].linedef[mem->b.j], 1) * mem->z;
		mem->coord.y1 = send_l_vy(mem->level,
				mem->level->sector[mem->b.i].linedef[mem->b.j], 1) * mem->z;
		mem->coord.x2 = send_l_vx(mem->level,
				mem->level->sector[mem->b.i].linedef[mem->b.j], 2) * mem->z;
		mem->coord.y2 = send_l_vy(mem->level,
				mem->level->sector[mem->b.i].linedef[mem->b.j], 2) * mem->z;
		mem->b.tx1 = mem->coord.x1 - mem->level->player.x;
		mem->b.tx2 = mem->coord.x2 - mem->level->player.x;
		mem->b.ty1 = mem->coord.y1 - mem->level->player.y;
		mem->b.ty2 = mem->coord.y2 - mem->level->player.y;
		fuck1(mem);
	}
}

static void		draw1(t_mem *mem)
{
	if (mem->b.tz1 > 0 || mem->b.tz2 > 0)
	{
		intersect(mem->b.tx1, mem->b.tz1, mem->b.tx2, mem->b.tz2, -0.0001,
				0.0001, -70, 5, &mem->b.ix1, &mem->b.iz1);
		intersect(mem->b.tx1, mem->b.tz1, mem->b.tx2, mem->b.tz2, 0.0001,
				0.0001, 70, 5, &mem->b.ix2, &mem->b.iz2);
		fuck2(mem);
		init(mem);
		mem->b.x1 = -mem->b.tx1 * 800 / mem->b.tz1 + W / 2;
		mem->b.x2 = -mem->b.tx2 * 800 / mem->b.tz2 + W / 2;
		mem->b.y1a = -H * 5 / mem->b.tz1 + H / 2;
		mem->b.y2a = -H * 5 / mem->b.tz2 + H / 2;
		mem->b.y1b = H * 5 / mem->b.tz1 + H / 2;
		mem->b.y2b = H * 5 / mem->b.tz2 + H / 2;
	}
}

static void		draw_mini(t_mem *mem)
{
	while (++mem->b.j < mem->level->sector[mem->b.i].nb_linedef)
	{
		fuck3(mem);
		draw1(mem);
		change_color(&mem->color, mem->level->c[mem->b.j]);
		fill_form(mem->b.x1, mem->b.x2, mem->b.y1a, mem->b.y2a, mem);
		fill_form(mem->b.x1, mem->b.x2, mem->b.y1b, mem->b.y2b, mem);
	}
}

void			draw_minimap(t_mem *mem)
{
	mem->b.i = -1;
	mem->z = 10;
	mlx_clear_window(mem->mlx_ptr, mem->win.win_ptr);
	while (++mem->b.i < mem->level->nb_sector)
	{
		mem->b.j = -1;
		draw_mini(mem);
	}
	change_color(&mem->color, 0xff);
	mem->b.i = -1;
	while (++mem->b.i < mem->level->nb_sector)
	{
		draw(mem);
	}
	mem->coord.x1 = 150;
	mem->coord.y1 = 150;
	mem->coord.x2 = 150;
	mem->coord.y2 = 150 + 30;
	draw_circle(mem);
	draw_line(mem);
}
