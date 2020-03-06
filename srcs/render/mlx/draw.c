/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:09 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 21:59:41 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void		draw_line(t_mem *mem)
{
	t_line	line;

	line.dx = abs(mem->coord.x2 - mem->coord.x1);
	line.sx = mem->coord.x1 < mem->coord.x2 ? 1 : -1;
	line.dy = abs(mem->coord.y2 - mem->coord.y1);
	line.sy = mem->coord.y1 < mem->coord.y2 ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) * 0.5;
	line.e2 = line.err;
	while (101)
	{
		ft_put_pixel(mem, mem->coord.x1, mem->coord.y1, mem->color);
		if (mem->coord.x1 == mem->coord.x2 && mem->coord.y1 == mem->coord.y2)
			break ;
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			mem->coord.x1 += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			mem->coord.y1 += line.sy;
		}
	}
}

void		draw_camera(t_mem *mem)
{
	t_color	color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 0;
	ft_put_pixel(mem, (mem->z * 0.01 * mem->level->player.x),
		(mem->z * 0.01 * mem->level->player.y), color);
	mem->coord.x1 = (mem->z * 0.01 * mem->level->player.x);
	mem->coord.y1 = (mem->z * 0.01 * mem->level->player.y);
}

void		draw_square(t_mem *mem)
{
	t_color color;

	color.r = 0;
	color.g = 255;
	color.b = 0;
	color.a = 0;
	ft_put_pixel(mem, mem->coord.x1, mem->coord.y1, color);
}
