/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   math.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:39:18 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 17:10:12 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int fn_cross(float x1, float y1, float x2, float y2)
{
	return ((x1 * y2) - (y1 * x2));
}

void intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *x, float *y)
{
	float det;
	*x = fn_cross(x1, y1, x2, y2);
	*y = fn_cross(x3, y3, x4, y4);
	det = fn_cross(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	*x = fn_cross(*x, x1 - x2, *y, x3 - x4) / det;
	*y = fn_cross(*x, y1 - y2, *y, y3 - y4) / det;
}

int return_min(int x1, int x2)
{
	return ((x1 > x2 ? x2 : x1));
}

float		dot_product(t_vertex a, t_vertex b, t_player p)
{
	return ((float)((a.y - p.y) * (b.x - a.x) - (a.x - p.x) * (b.y - a.y)));
}

/* s = pos in level->sector tab as l in level->sector[se]->l */
float	point_line(t_mem *mem, int s, int l)
{
	t_vertex	a;
	t_vertex	b;
	float		r;
	float		L;

	a.x = send_l_vx(mem->level, mem->level->sector[s].linedef[l], 1);
	a.y = send_l_vy(mem->level, mem->level->sector[s].linedef[l], 1);
	b.x = send_l_vx(mem->level, mem->level->sector[s].linedef[l], 2);
	b.y = send_l_vx(mem->level, mem->level->sector[s].linedef[l], 2);
	L = sqrt(pow((send_l_vx(mem->level, mem->level->sector[s].linedef[l], 2)
		- send_l_vx(mem->level, mem->level->sector[s].linedef[l], 1)), 2)
		+ pow((send_l_vy(mem->level, mem->level->sector[s].linedef[l], 2)
		- send_l_vy(mem->level, mem->level->sector[s].linedef[l], 1)), 2));
	r = dot_product(a, b, mem->level->player) / pow(L, 2);
	if ((r  > 0 && L > 0) || (r < 0 && L < 0))
		return (r * L);
	return (0);
}

int	send_s_id(t_mem *mem, int id)
{
	int	i;

	i = -1;
	while (++i < mem->level->nb_sector)
	{
		if (mem->level->sector[i].id == id)
			return (i);
	}
	return (0);
}

int		player_sector(t_mem *mem)
{
	int		i;
	int		j;
	float	tmp;
	float	dist_min;
	int		sector;
	int		nb_sector_pos;

	i = -1;
	sector = -1;
	dist_min = -1;
	nb_sector_pos = 0;
	while (++i < mem->level->nb_sector)
	{
		j = -1;
		tmp = 0;
		while (++j < mem->level->sector[i].nb_linedef)
			tmp += point_line(mem, i, j);
		if (dist_min < 0 || (tmp > 0 && tmp < dist_min))
		{
			dist_min = tmp;
			sector = mem->level->sector[i].id;
		}
	}
	return (sector);
}