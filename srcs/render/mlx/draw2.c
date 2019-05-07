/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw2.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 21:23:50 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 18:38:57 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void		draw_to_line(t_coord *coord, t_mem *mem)
{
	t_line	line;

	line.dx = abs(coord->x2 - coord->x1);
	line.sx = coord->x1 < coord->x2 ? 1 : -1;
	line.dy = abs(coord->y2 - coord->y1);
	line.sy = coord->y1 < coord->y2 ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) >> 1;
	line.e2 = line.err;
	while (!(coord->x1 == coord->x2 && coord->y1 == coord->y2))
	{
		if (coord->x1 > 0 && coord->x1 < W &&
			coord->y1 > 0 && coord->y1 < H)
			ft_put_pixel(mem, coord->x1, coord->y1, mem->color);
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			coord->x1 += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			coord->y1 += line.sy;
		}
	}
}

void		fill_column(int x, int sect, t_mem *mem)
{
	int		i;
	t_color	floor;
	t_color	ceil;
	t_color	step;

	i = 0;
	sect += 1;
	ceil.g = sect * 10;
	ceil.b = sect * 10;
	floor.r = sect * 10;
	floor.g = sect * 10;
	step.r = 35 * sect;
	step.b = 15 * sect;
	step.g = 0;

	if (x >= 0 && x < W)
		mem->fill_screen[x] = 1;
	// cette partie dessine les plafond (hauteur murs  sur haut de l'ecran)
	if (mem->level->sector[sect - 1].h_ceil > (int)mem->level->player.z)
		while (i < mem->p3.y1)
		{
			if (i >= 0 && i < H)
				ft_put_pixel(mem, x, i, ceil);
			i++;
		}
	// cette partie dessine les "contres plafonds"
	while (mem->p5.y1 < mem->p5.y2)
	{
		if (mem->p5.y1 >= 0 && mem->p5.y1 < H)
			ft_put_pixel(mem, x, mem->p5.y1, step);
		mem->p5.y1++;
	}
	// cette partie dessine les murs
	while (mem->p3.y1 < mem->p3.y2)
	{
		if (mem->p3.y1 >= 0 && mem->p3.y1 < H && mem->color.r != 255 && mem->color.g != 0 && mem->color.b != 0)
			ft_put_pixel(mem, x, mem->p3.y1, step);
		mem->p3.y1++;
		}
	// cette partie dessine les contres marches
	while (mem->p4.y1 < mem->p4.y2)
	{
		if (mem->p4.y1 >= 0 && mem->p4.y1 < H)
		ft_put_pixel(mem, x, mem->p4.y1, step);
		mem->p4.y1++;
	}
	// cette partie dessine le sol
	mem->p3.y1 = mem->p4.y1;
	if (mem->level->sector[sect - 1].h_floor < (int)mem->level->player.z + 6)
		while (mem->p3.y1 < H)
		{
			if (mem->p3.y1 >= 0 && mem->p3.y1 < H)
				ft_put_pixel(mem, x, mem->p3.y1, floor);
			mem->p3.y1++;
		}
}