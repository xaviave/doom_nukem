/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_calculate_2.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 22:49:44 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			calc_linedef(t_fcoord pf1, t_mem *mem)
{
	int			i;
	int			j;

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

t_vector		pre_calc_vec(t_vector vec)
{
	intersect(vec, &vec.ix1, &vec.iz1);
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

void			set_column(t_render coor, t_mem *mem)
{
	mem->p3.y1 = (int)coor.p1.y1 - mem->camera_y + mem->level->player.recoil;
	mem->p3.y2 = (int)coor.p2.y1 - mem->camera_y + mem->level->player.recoil;
	mem->p4.y1 = mem->p3.y2;
	mem->p4.y2 = (int)coor.step.y1 - mem->camera_y + mem->level->player.recoil;
	mem->p5.y1 = (int)coor.top.y1 - mem->camera_y + mem->level->player.recoil;
	mem->p5.y2 = mem->p3.y1;
}

int				pre_render(t_mem *mem, int sect, int i)
{
	int			j;
	t_fcoord	p1;
	t_vector	vec;

	j = -1;
	while (++j < mem->level->sector[sect].nb_linedef)
	{
		vec = calc_wall(mem, vec, sect, j);
		if (vec.tz1 > 0 || vec.tz2 > 0)
		{
			vec = pre_calc_vec(vec);
			p1.x1 = -vec.tx1 * 800 / vec.tz1 + (W >> 1);
			p1.x2 = -vec.tx2 * 800 / vec.tz2 + (W >> 1);
			mem->color.a = 0;
			change_color(&mem->color, mem->level->c
			[mem->level->linedef[send_l_id(mem,
			mem->level->sector[sect].linedef[j])].side.text[0]]);
		}
		if (!(mem->color.r == 255 && mem->color.g == 0 && mem->color.b == 0))
			calc_linedef(p1, mem);
		if (further_sector(mem, sect) != -1)
			return (i);
	}
	return (-1);
}

int				further_sector(t_mem *mem, int sector)
{
	int			i;
	int			j;

	j = 0;
	i = -1;
	while (++i < W)
	{
		if (mem->fill_screen[i])
			j++;
	}
	if (j >= W)
		return (sector);
	else
		return (-1);
}
