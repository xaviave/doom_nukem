/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_map_2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 22:00:04 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			shoot(t_mem *mem, char frame)
{
	t_coord		coord;

	coord.x1 = W >> 1;
	coord.y1 = H >> 1;
	coord.x2 = W - 340;
	coord.y2 = H - 150;
	if (frame == 2)
	{
		change_color(&mem->color, 0xFF0000);
		draw_to_line(&coord, mem);
	}
	else
	{
		change_color(&mem->color, 0x0000FF);
		draw_to_line(&coord, mem);
	}
	on_shoot(mem);
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
			calc_minimap(mem, i, j, &vec);
	}
	mem->coord.x1 = W / 2;
	mem->coord.y1 = H / 2;
	mem->coord.x2 = W / 2;
	mem->coord.y2 = H / 2 + 30;
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

void			paint_linedef(t_render coor, int sect, t_mem *mem)
{
	int			i;

	i = 0;
	set_wall_size(mem, coor);
	while ((int)coor.p1.x1 != (int)coor.p1.x2)
	{
		set_wall_infos(mem);
		if (i++)
		{
			calc_linedef_one(&coor, mem);
			calc_linedef_two(&coor, mem);
		}
		if (((int)coor.p1.x1 >= 0 && (int)coor.p1.x1 < W))
		{
			set_column(coor, mem);
			mem->min_y = mem->p3.y1;
			mem->max_y = mem->p3.y2;
			mem->h_wall = mem->max_y - mem->min_y;
			mem->l_wall = mem->max_x - mem->min_x;
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
