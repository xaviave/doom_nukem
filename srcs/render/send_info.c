/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   send_info.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:38:22 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/14 13:02:36 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int send_vx(t_level *level, int id)
{
	int i;

	i = -1;
	while (++i < level->nb_vertex)
	{
		if (level->vertex[i].id == id)
			return (level->vertex[i].x);
	}
	return (0);
}

int send_vy(t_level *level, int id)
{
	int i;

	i = -1;
	while (++i < level->nb_vertex)
	{
		if (level->vertex[i].id == id)
			return (level->vertex[i].y);
	}
	return (0);
}

int send_l_vx(t_level *level, int id_l, int vertex)
{
	int i;

	i = -1;
	while (++i < level->nb_linedef)
	{
		if (id_l == level->linedef[i].id)
			break;
	}
	if (vertex == 1)
		return (send_vx(level, level->linedef[i].id_v1));
	else
		return (send_vx(level, level->linedef[i].id_v2));
}

int send_l_vy(t_level *level, int id_l, int vertex)
{
	int i;

	i = -1;
	while (++i < level->nb_linedef)
	{
		if (id_l == level->linedef[i].id)
			break;
	}
	if (vertex == 1)
		return (send_vy(level, level->linedef[i].id_v1));
	else
		return (send_vy(level, level->linedef[i].id_v2));
}

int send_l_id(t_mem *mem, int id)
{
	int i;

	i = -1;
	while (++i < mem->level->nb_linedef)
	{
		if (mem->level->linedef[i].id == id)
			return (i);
	}
	return (0);
}

void fill_n_sector(t_mem *mem, int i)
{
	int j;

	j = -1;
	while (++j < mem->level->sector[send_s_id(mem, mem->level->n_sector[i])].nb_neighbors)
	{
		if (double_int(mem->level->n_sector, mem->level->sector[send_s_id(mem, mem->level->n_sector[i])].neighbors[j], mem->level->n))
		{
			mem->level->n_sector[mem->level->n] = mem->level->sector[send_s_id(mem, mem->level->n_sector[i])].neighbors[j];
			mem->level->n++;
		}
	}
	if (mem->level->n < mem->level->nb_sector)
		fill_n_sector(mem, ++i);
}

int next_sector(t_mem *mem, int linedef_id, int actual_sector)
{
	int i;
	int j;
	int	this_sector;
	int	next_sector;

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