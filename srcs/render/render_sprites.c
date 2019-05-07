/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_sprites.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 13:35:02 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			render_sprites(t_mem *mem, int sect)
{
	int			i;
	t_vector	vec;

	i = -1;
	while (++i < mem->level->nb_monsters)
		if (mem->level->monsters[i].sector == sect)
		{
			vec.mx = mem->level->monsters[i].x - mem->level->player.x;
			vec.my = mem->level->monsters[i].y - mem->level->player.y;
			vec.mz1 = vec.mx * mem->cos_angle + vec.my * mem->sin_angle;
			vec.mx1 = vec.mx * mem->sin_angle - vec.my * mem->cos_angle;
			intersect(vec, &vec.ix1, &vec.iz1);
			if (vec.mz1 >= 0)
			{
				vec.mx = -vec.mx1 * 800 / vec.mz1 + W * 0.5;
				vec.my = H * (mem->level->player.z - mem->level->sector
[sect].h_floor) / vec.mz1 + H * 0.5 + mem->level->player.recoil;
				if (vec.mx > 0 && vec.mx < W)
					put_img_to_img(mem, &mem->monster, vec.mx, vec.my,
(H * 0.02) / mem->level->monsters[i].distance);
			}
		}
}
