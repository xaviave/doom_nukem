/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mob_infos.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 18:27:30 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 23:42:22 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void				sort_dist_monsters(t_mem *mem)
{
	int				i;
	t_entity		swap;

	i = 0;
	while (i < mem->level->nb_entity)
	{
		mem->level->entity[i].distance = distance(mem->level->entity[i].x,
			mem->level->entity[i].y, mem->level->player.x,
			mem->level->player.y);
		i++;
	}
	i = 1;
	while (i < mem->level->nb_entity)
	{
		if (mem->level->entity[i].distance
			> mem->level->entity[i - 1].distance)
		{
			swap = mem->level->entity[i];
			mem->level->entity[i] = mem->level->entity[i - 1];
			mem->level->entity[i - 1] = swap;
			i = 1;
		}
		else
			i++;
	}
}

static void			entity_define_sector(t_mem *mem, int i, int save, int e)
{
	int				j;

	j = 0;
	while (++j < mem->level->sector[i].nb_linedef)
		if (check_in_sector(mem, mem->level->linedef[send_l_id(mem,
			mem->level->sector[i].linedef[j])].id_v1,
			mem->level->linedef[send_l_id(mem,
			mem->level->sector[i].linedef[j])].id_v2, save))
			mem->level->entity[e].sector = mem->level->sector[i].id - 1;
}

void				entity_sector(t_mem *mem)
{
	int				i;
	int				e;
	int				save;
	t_player		save_p;

	e = -1;
	save_p = mem->level->player;
	while (++e < mem->level->nb_entity)
	{
		mem->level->player.x = mem->level->entity[e].x;
		mem->level->player.y = mem->level->entity[e].y;
		i = -1;
		while (++i < mem->level->nb_sector)
		{
			save = mem->level->linedef[send_l_id(mem,
				mem->level->sector[i].linedef[0])].id_v1;
			if (in_box(mem, i) == 2)
				entity_define_sector(mem, i, save, e);
		}
	}
	mem->level->player = save_p;
	mem->level->player = save_p;
}
