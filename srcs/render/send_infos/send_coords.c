/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   send_coords.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 18:15:16 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 18:42:21 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

void		send_x(t_coord *coord, t_mem *mem, int l)
{
	int		x1;
	int		x2;

	x1 = send_l_vx(mem->level, l, 1);
	x2 = send_l_vx(mem->level, l, 2);
	if (x1 < x2)
	{
		coord->x1 = (coord->x1 == -1 || coord->x1 > x1) ? x1 : coord->x1;
		coord->x2 = (coord->x2 == -1 || coord->x2 < x2) ? x2 : coord->x2;
		return ;
	}
	coord->x1 = (coord->x1 == -1 || coord->x1 > x2) ? x2 : coord->x1;
	coord->x2 = (coord->x2 == -1 || coord->x2 < x1) ? x1 : coord->x2;
}

void		send_y(t_coord *coord, t_mem *mem, int l)
{
	int		y1;
	int		y2;

	y1 = send_l_vy(mem->level, l, 1);
	y2 = send_l_vy(mem->level, l, 2);
	if (y1 < y2)
	{
		coord->y1 = (coord->y1 == -1 || coord->y1 > y1) ? y1 : coord->y1;
		coord->y2 = (coord->y2 == -1 || coord->y2 < y2) ? y2 : coord->y2;
		return ;
	}
	coord->y1 = (coord->y1 == -1 || coord->y1 > y2) ? y2 : coord->y1;
	coord->y2 = (coord->y2 == -1 || coord->y2 < y1) ? y1 : coord->y2;
}

int			send_vx(t_level *level, int id)
{
	int		i;

	i = -1;
	while (++i < level->nb_vertex)
	{
		if (level->vertex[i].id == id)
			return (level->vertex[i].x);
	}
	return (0);
}

int			send_vy(t_level *level, int id)
{
	int		i;

	i = -1;
	while (++i < level->nb_vertex)
	{
		if (level->vertex[i].id == id)
			return (level->vertex[i].y);
	}
	return (0);
}
