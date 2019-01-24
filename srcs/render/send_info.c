/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   send_info.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:38:22 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 16:39:09 by xamartin    ###    #+. /#+    ###.fr     */
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
