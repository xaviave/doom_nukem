/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sector_infos.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 18:19:10 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 18:45:30 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void			search_sector(t_mem *mem, int id, int ok)
{
	int			i;
	int			j;

	i = -1;
	j = -1;
	while (++i < mem->level->nb_sector)
	{
		if (mem->level->sector[i].id == id)
			break ;
	}
	while (++j < mem->level->sector[i].nb_neighbors)
	{
		if (double_int(mem->level->n_sector,
			mem->level->sector[i].neighbors[j], mem->level->n))
		{
			mem->level->n_sector[mem->level->n] =
				mem->level->sector[i].neighbors[j];
			mem->level->n++;
		}
	}
	if (mem->level->n < mem->level->nb_sector)
		search_sector(mem, mem->level->n_sector[ok], ok + 1);
}

void			fill_n_sector(t_mem *mem, int i)
{
	int			j;

	j = -1;
	while (++j < mem->level->sector[send_s_id(mem,
		mem->level->n_sector[i])].nb_neighbors)
	{
		if (double_int(mem->level->n_sector, mem->level->sector[send_s_id(mem,
			mem->level->n_sector[i])].neighbors[j], mem->level->n))
		{
			mem->level->n_sector[mem->level->n] =
				mem->level->sector[send_s_id(mem,
				mem->level->n_sector[i])].neighbors[j];
			mem->level->n++;
		}
	}
	if (mem->level->n < mem->level->nb_sector)
		fill_n_sector(mem, ++i);
}

int				next_sector(t_mem *mem, int linedef_id, int actual_sector)
{
	int			i;
	int			j;
	int			this_sector;
	int			next_sector;

	this_sector = -1;
	next_sector = -1;
	i = -1;
	while (++i < mem->level->nb_sector)
	{
		j = -1;
		while (++j < mem->level->sector[i].nb_linedef)
		{
			if (linedef_id == mem->level->sector[i].linedef[j])
			{
				if (actual_sector == i)
					this_sector = i;
				else
					next_sector = i;
				if (this_sector != -1 && next_sector != -1)
					return (next_sector);
			}
		}
	}
	return (-1);
}
