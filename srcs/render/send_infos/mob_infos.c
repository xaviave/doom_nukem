/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mob_infos.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 18:27:30 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 18:34:34 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void			sort_dist_monsters(t_mem *mem)
{
	int			i;
	t_monster	swap;

	i = 0;
	while (i < mem->level->nb_monsters)
	{
		mem->level->monsters[i].distance = distance(mem->level->monsters[i].x,
			mem->level->monsters[i].y, mem->level->player.x,
			mem->level->player.y);
		i++;
	}
	i = 1;
	while (i < mem->level->nb_monsters)
	{
		if (mem->level->monsters[i].distance
			> mem->level->monsters[i - 1].distance)
		{
			swap = mem->level->monsters[i];
			mem->level->monsters[i] = mem->level->monsters[i - 1];
			mem->level->monsters[i - 1] = swap;
			i = 1;
		}
		else
			i++;
	}
}
