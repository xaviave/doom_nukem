/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   send_ids.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 18:12:35 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 18:40:53 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

int			send_s_id(t_mem *mem, int id)
{
	int		i;

	i = -1;
	while (++i < mem->level->nb_sector)
	{
		if (mem->level->sector[i].id == id)
			return (i);
	}
	return (0);
}

int			send_v_id(t_mem *mem, int id)
{
	int		i;

	i = -1;
	while (++i < mem->level->nb_vertex)
	{
		if (mem->level->vertex[i].id == id)
			return (i);
	}
	return (0);
}

int			send_l_id(t_mem *mem, int id)
{
	int		i;

	i = -1;
	while (++i < mem->level->nb_linedef)
	{
		if (mem->level->linedef[i].id == id)
			return (i);
	}
	return (0);
}
