/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fucknorm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cmerel <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 13:45:33 by cmerel       #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 14:00:34 by cmerel      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		fuck1(t_mem *mem)
{
	mem->b.tz1 = mem->b.tx1 * cos(mem->level->player.angle) +
		mem->b.ty1 * sin(mem->level->player.angle);
	mem->b.tz2 = mem->b.tx2 * cos(mem->level->player.angle) +
		mem->b.ty2 * sin(mem->level->player.angle);
	mem->b.tx1 = mem->b.tx1 * sin(mem->level->player.angle) -
		mem->b.ty1 * cos(mem->level->player.angle);
	mem->b.tx2 = mem->b.tx2 * sin(mem->level->player.angle) -
		mem->b.ty2 * cos(mem->level->player.angle);
	mem->coord.x1 = mem->b.tx1 + 150;
	mem->coord.x2 = mem->b.tx2 + 150;
	mem->coord.y1 = mem->b.tz1 + 150;
	mem->coord.y2 = mem->b.tz2 + 150;
	draw_circle(mem);
	draw_line(mem);
	draw_circle(mem);
}

void		fuck2(t_mem *mem)
{
	if (mem->b.tz1 <= 0)
	{
		if (mem->b.iz1 > 0)
		{
			mem->b.tx1 = mem->b.ix1;
			mem->b.tz1 = mem->b.iz1;
		}
		else
		{
			mem->b.tx1 = mem->b.ix2;
			mem->b.tz1 = mem->b.iz2;
		}
	}
}

void		fuck3(t_mem *mem)
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
	mem->b.tz1 = mem->b.tx1 * cos(mem->level->player.angle) +
		mem->b.ty1 * sin(mem->level->player.angle);
	mem->b.tz2 = mem->b.tx2 * cos(mem->level->player.angle) +
		mem->b.ty2 * sin(mem->level->player.angle);
	mem->b.tx1 = mem->b.tx1 * sin(mem->level->player.angle) -
		mem->b.ty1 * cos(mem->level->player.angle);
	mem->b.tx2 = mem->b.tx2 * sin(mem->level->player.angle) -
		mem->b.ty2 * cos(mem->level->player.angle);
	mem->coord.x1 = mem->b.tx1 + 150;
	mem->coord.x2 = mem->b.tx2 + 150;
	mem->coord.y1 = mem->b.tz1 + 150;
	mem->coord.y2 = mem->b.tz2 + 150;
}
