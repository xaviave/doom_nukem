/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wall_infos.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 23:42:37 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			set_wall_size(t_mem *mem, t_render coor)
{
	mem->line = line_init(coor.p1);
	mem->line2 = line_init(coor.p2);
	mem->line3 = line_init(coor.step);
	mem->line4 = line_init(coor.top);
	mem->min_x = coor.p1.x1;
	mem->max_x = coor.p1.x2;
	mem->tex_x = 0;
}

void			set_wall_infos(t_mem *mem)
{
	mem->tex_y = 0;
	mem->step_y = 32 / fabsf(mem->max_y - mem->min_y);
	mem->step_x = 32 / fabsf(mem->max_x - mem->min_x);
	mem->line.e2 = mem->line.err;
	mem->line2.e2 = mem->line2.err;
	mem->line3.e2 = mem->line3.err;
	mem->line4.e2 = mem->line4.err;
}
