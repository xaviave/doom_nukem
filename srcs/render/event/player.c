/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: izoukhai <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 16:31:40 by izoukhai     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 16:31:43 by izoukhai    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void				on_shoot(t_mem *mem)
{
	int				i;
	float			zoom;
	t_vertex		lim;

	i = -1;
	while (++i < mem->level->nb_entity)
	{
		if (!mem->level->entity[i].alive ||
		mem->level->entity[i].text != MOB)
			continue ;
		zoom = (H * 0.02) / mem->level->entity[i].distance;
		lim.x = (365 * zoom * 0.5);
		lim.y = (285 * zoom) * 1.5;
		if ((W / 2 >= mem->level->entity[i].s_x - lim.x && W / 2 <=
					mem->level->entity[i].s_x + lim.x) &&
				(H / 2 >= mem->level->entity[i].s_y - lim.y - mem->camera_y &&
				H / 2 <= mem->level->entity[i].s_y - mem->camera_y))
			mem->level->entity[i].alive = 0;
	}
}

static void			pickup(t_mem *mem, t_entity *e)
{
	if (!e->alive)
		return ;
	if (e->text == HEALTH_BOX)
	{
		mem->level->player.hp = 100;
		e->alive = 0;
	}
	if (e->text == AMMO_BOX)
	{
		mem->level->player.magazine++;
		e->alive = 0;
	}
}

static void			check_collision(t_mem *mem, t_entity *e)
{
	if (e->distance <= 10)
		pickup(mem, e);
}

void				on_collision(t_mem *mem)
{
	int				i;

	i = -1;
	while (++i < mem->level->nb_entity)
		check_collision(mem, &mem->level->entity[i]);
}

void				on_reload(t_mem *mem)
{
	if (!mem->level->player.magazine || mem->level->player.ammos == 30)
		return ;
	play_audio(mem->level->sounds.reload);
	mem->level->player.magazine--;
	mem->level->player.ammos = 30;
}
