/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_sprites.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 10:37:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 00:55:08 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			helper(t_mem *mem, t_vector vec, int i)
{
	if (mem->level->entity[i].text == MOB)
	{
		mem->level->entity[i].s_x = vec.mx;
		mem->level->entity[i].s_y = vec.my;
		if (!mem->level->entity[i].shooting)
		{
			put_img_to_img(mem, &mem->monster, vec,
			(H * 0.02) / mem->level->entity[i].distance);
			mem->level->entity[i].shooting = 0;
		}
		else
			put_img_to_img(mem, &mem->shooting_monster, vec,
			(H * 0.02) / mem->level->entity[i].distance);
	}
	else if (mem->level->entity[i].text == HEALTH_BOX)
		put_img_to_img(mem, &mem->hp_box, vec,
			(H * 0.01) / mem->level->entity[i].distance);
	else
		put_img_to_img(mem, &mem->ammo_box, vec,
		(H * 0.01) / mem->level->entity[i].distance);
}

void			set_vecs(t_vector *vec, t_mem *mem, int i)
{
	mem->level->entity[i].distance = distance(mem->level->entity[i].x,
			mem->level->entity[i].y, mem->level->player.x,
			mem->level->player.y);
	vec->mx = mem->level->entity[i].x - mem->level->player.x;
	vec->my = mem->level->entity[i].y - mem->level->player.y;
	vec->mz1 = vec->mx * mem->cos_angle + vec->my * mem->sin_angle;
	vec->mx1 = vec->mx * mem->sin_angle - vec->my * mem->cos_angle;
}

void			render_sprites(t_mem *mem, int sect)
{
	int			i;
	t_vector	vec;

	i = -1;
	while (++i < mem->level->nb_entity)
	{
		if (!mem->level->entity[i].alive)
			continue;
		if (mem->level->entity[i].sector == sect)
		{
			set_vecs(&vec, mem, i);
			intersect(vec, &vec.ix1, &vec.iz1);
			if (vec.mz1 >= 0)
			{
				vec.mx = -vec.mx1 * 800 / vec.mz1 + W * 0.5;
				vec.my = H * (mem->level->player.z - mem->level->sector
			[sect].h_floor) / vec.mz1 + H * 0.5 + mem->level->player.recoil;
				if (vec.mx > 0 && vec.mx < W)
					helper(mem, vec, i);
			}
		}
	}
}
