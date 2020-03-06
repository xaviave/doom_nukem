/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw2.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 21:23:50 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 00:52:43 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void			draw_to_line(t_coord *coord, t_mem *mem)
{
	t_line		line;

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

void			ft_put_tex(t_mem *mem, int x, int y)
{
	int			bpp1;
	int			bpp2;
	int			dst;

	bpp1 = mem->img.bpp >> 3;
	bpp2 = mem->wall.bpp >> 3;
	dst = (int)(round(mem->tex_y) * bpp2 + mem->wall.sizeline *
	((round(mem->tex_x) / (mem->h_wall * mem->max_x)))) * 32;
	if (dst == 0)
		dst = 1;
	dst = rgb(mem->wall.data[(int)dst + 3], mem->wall.data[(int)dst + 2],
	mem->wall.data[(int)dst + 1], mem->wall.data[(int)dst]);
	if ((x > 0 && x < mem->win.width) && (y > 0 && y < mem->win.height))
		ft_put_pixel(mem, x, y, set_color(dst));
}

void			fill_column_2(int x, int sect, t_mem *mem)
{
	t_color		floor;
	t_color		step;

	floor.r = sect * 10;
	step.b = 0;
	mem->tex_y = 0;
	while (mem->p3.y1 < mem->p3.y2)
	{
		if (mem->p3.y1 >= 0 && mem->p3.y1 < H && mem->color.r != 255 &&
		mem->color.g != 0 && mem->color.b != 0)
			ft_put_tex(mem, x, mem->p3.y1);
		mem->p3.y1++;
		mem->tex_y += mem->step_y;
	}
	while (mem->p4.y1 < mem->p4.y2)
	{
		if (mem->p4.y1 >= 0 && mem->p4.y1 < H)
			ft_put_pixel(mem, x, mem->p4.y1, step);
		mem->p4.y1++;
	}
	mem->p3.y1 = mem->p4.y1;
	if (mem->level->sector[sect - 1].h_floor < (int)mem->level->player.z + 10)
		while (mem->p3.y1++ < H)
			if (mem->p3.y1 >= 0 && mem->p3.y1 < H)
				ft_put_pixel(mem, x, mem->p3.y1, floor);
}

void			fill_column(int x, int sect, t_mem *mem)
{
	t_color		ceil;
	int			i;

	i = 0;
	sect += 1;
	ceil.g = sect * 10;
	ceil.b = sect * 20;
	if (x >= 0 && x < W)
		mem->fill_screen[x] = 1;
	if (mem->level->sector[sect - 1].h_ceil > (int)mem->level->player.z - 10)
		while (i < mem->p3.y1)
		{
			if (i >= 0 && i < H)
				ft_put_pixel(mem, x, i, ceil);
			i++;
		}
	while (mem->p5.y1 < mem->p5.y2)
	{
		if (mem->p5.y1 >= 0 && mem->p5.y1 < H)
			ft_put_pixel(mem, x, mem->p5.y1, ceil);
		mem->p5.y1++;
	}
	fill_column_2(x, sect, mem);
}
