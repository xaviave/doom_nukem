/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textures_tools_2.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 11:28:45 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 00:33:00 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void				draw_objects(t_mem *mem, t_vector coor, float zoom, int k)
{
	while (++mem->coord.y2 < zoom)
	{
		while (mem->coord.x1++ < k * zoom)
			if (mem->colorize < 4278190080 && mem->coord.x1 + coor.mx > 0 &&
mem->coord.x1 + coor.mx < W && mem->coord.y1 + mem->coord.y2 + coor.my > 0
	&& mem->coord.y1 + mem->coord.y2 + coor.my < H)
				ft_put_pixel(mem, mem->coord.x1 + coor.mx, mem->coord.y1
	+ mem->coord.y2 + coor.my, set_color(mem->colorize));
		mem->coord.x1 -= zoom;
	}
}
