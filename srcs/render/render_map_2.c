/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map_2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 13:00:28 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			shoot(t_mem *mem, char frame)
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

void			draw_minimap(t_mem *mem)
{
	int			i;
	int			j;
	t_vector	vec;

	change_color(&mem->color, 0xffffff);
	i = -1;
	while (++i < mem->level->nb_sector)
	{
		j = -1;
		while (++j < mem->level->sector[i].nb_linedef)
		{
			calc_minimap(mem, i, j, &vec);
			draw_circle(mem);
		}
	}
	mem->coord.x1 = W / 2;
	mem->coord.y1 = H / 2;
	mem->coord.x2 = W / 2;
	mem->coord.y2 = H / 2 + 30;
	draw_circle(mem);
	draw_line(mem);
}

t_line			line_init(t_fcoord p)
{
	t_line		line;

	line.dx = abs((int)p.x2 - (int)p.x1);
	line.sx = ((int)p.x1 < (int)p.x2) ? 1 : -1;
	line.dy = abs((int)p.y2 - (int)p.y1);
	line.sy = ((int)p.y1 < (int)p.y2) ? 1 : -1;
	line.err = ((line.dx > line.dy) ? line.dx : -line.dy) * 0.5;
	line.e2 = line.err;
	return (line);
}

void			paint_linedef(t_fcoord p1, t_fcoord p2, t_fcoord step, t_fcoord top, int sect, t_mem *mem)
{
	int			i;
	t_render	coor;

	coor.p1 = p1;
	coor.p2 = p2;
	coor.step = step;
	coor.top = top;
	i = 0;

	mem->line = line_init(p1);
	mem->line2 = line_init(p2);
	mem->line3 = line_init(step);
	mem->line4 = line_init(top);
	while ((int)coor.p1.x1 != (int)coor.p1.x2)
	{
		mem->line.e2 = mem->line.err;
		mem->line2.e2 = mem->line2.err;
		mem->line3.e2 = mem->line3.err;
		mem->line4.e2 = mem->line4.err;
		if (i++)
		{
			calc_linedef_one(&coor, mem);
			calc_linedef_two(&coor, mem);
		}
		if (((int)coor.p1.x1 >= 0 && (int)coor.p1.x1 < W))
		{
			set_column(coor, mem);
			fill_column((int)coor.p1.x1, sect, mem);
		}
	}
}

void			event_loop(t_mem *mem)
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
