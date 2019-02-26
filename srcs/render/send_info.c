/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   send_info.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 16:38:22 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 17:00:19 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int send_s_id(t_mem *mem, int id)
{
	int i;

	i = -1;
	while (++i < mem->level->nb_sector)
	{
		if (mem->level->sector[i].id == id)
			return (i);
	}
	return (0);
}

int send_v_id(t_mem *mem, int id)
{
	int i;

	i = -1;
	while (++i < mem->level->nb_vertex)
	{
		if (mem->level->vertex[i].id == id)
			return (i);
	}
	return (0);
}

void send_x(t_coord *coord, t_mem *mem, int l)
{
	int x1;
	int x2;

	x1 = send_l_vx(mem->level, l, 1);
	x2 = send_l_vx(mem->level, l, 2);
	if (x1 < x2)
	{
		coord->x1 = (coord->x1 == -1 || coord->x1 > x1) ? x1 : coord->x1;
		coord->x2 = (coord->x2 == -1 || coord->x2 < x2) ? x2 : coord->x2;
		return;
	}
	coord->x1 = (coord->x1 == -1 || coord->x1 > x2) ? x2 : coord->x1;
	coord->x2 = (coord->x2 == -1 || coord->x2 < x1) ? x1 : coord->x2;
}

void send_y(t_coord *coord, t_mem *mem, int l)
{
	int y1;
	int y2;

	y1 = send_l_vy(mem->level, l, 1);
	y2 = send_l_vy(mem->level, l, 2);
	if (y1 < y2)
	{
		coord->y1 = (coord->y1 == -1 || coord->y1 > y1) ? y1 : coord->y1;
		coord->y2 = (coord->y2 == -1 || coord->y2 < y2) ? y2 : coord->y2;
		return;
	}
	coord->y1 = (coord->y1 == -1 || coord->y1 > y2) ? y2 : coord->y1;
	coord->y2 = (coord->y2 == -1 || coord->y2 < y1) ? y1 : coord->y2;
}

int in_box(t_mem *mem, int nb)
{
	int i;

	i = -1;
	mem->coord.x1 = -1;
	mem->coord.x2 = -1;
	mem->coord.y1 = -1;
	mem->coord.y2 = -1;
	while (++i < mem->level->sector[nb].nb_linedef)
	{
		send_x(&mem->coord, mem, mem->level->sector[nb].linedef[i]);
		send_y(&mem->coord, mem, mem->level->sector[nb].linedef[i]);
	}
	i = 0;
	if ((mem->level->player.x > mem->coord.x1 && mem->level->player.x < mem->coord.x2) || (mem->level->player.x == mem->coord.x1 || mem->level->player.x == mem->coord.x2))
		i++;
	if ((mem->level->player.y > mem->coord.y1 && mem->level->player.y < mem->coord.y2) || (mem->level->player.y == mem->coord.y1 || mem->level->player.y == mem->coord.y2))
		i++;
	return (i);
}

int is_inside(t_vertex v1, t_vertex v2, t_vertex v3, t_vertex player)
{
	double s1;
	double s2;
	double s3;
	double s4;
	double w1;
	double w2;

	s1 = v3.y - v1.y;
	s2 = v3.x - v1.x;
	s3 = v2.y - v1.y;
	s4 = player.y - v1.y;
	w1 = (v1.x * s1 + s4 * s2 - player.x * s1) / (s3 * s2 - (v2.x - v1.x) * s1);
	w2 = (s4 - w1 * s3) / s1;
	return (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1);
}

int check_in_sector(t_mem *mem, int l1, int l2, int save)
{
	t_vertex vertex;

	if (send_v_id(mem, save) == send_v_id(mem, l1) || send_v_id(mem, save) == send_v_id(mem, l2))
		return (0);
	vertex.x = mem->level->player.x;
	vertex.y = mem->level->player.y;
	if (is_inside(mem->level->vertex[send_v_id(mem, save)],
				  mem->level->vertex[send_v_id(mem, l1)],
				  mem->level->vertex[send_v_id(mem, l2)], vertex))
		return (1);
	return (0);
}

int double_int(int *tab, int nu, int nb)
{
	int i;

	i = -1;
	while (++i < nb)
	{
		if (tab[i] == nu)
			return (0);
	}
	return (1);
}

int player_sector(t_mem *mem)
{
	int i;
	int j;
	int save;

	i = -1;
	while (++i < mem->level->nb_sector)
	{
		save = mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[0])].id_v1;
		if (in_box(mem, i) == 2)
		{
			j = 0;
			while (++j < mem->level->sector[i].nb_linedef)
				if (check_in_sector(mem, mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].id_v1, mem->level->linedef[send_l_id(mem, mem->level->sector[i].linedef[j])].id_v2, save))
					mem->level->player.sector = mem->level->sector[i].id;
		}
	}
	mem->level->n = 1;
	mem->level->n_sector[0] = mem->level->player.sector;
	fill_n_sector(mem, 0);
	return (mem->level->player.sector);
}

void search_sector(t_mem *mem, int id, int ok)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < mem->level->nb_sector)
	{
		if (mem->level->sector[i].id == id)
			break;
	}
	while (++j < mem->level->sector[i].nb_neighbors)
	{
		if (double_int(mem->level->n_sector, mem->level->sector[i].neighbors[j], mem->level->n))
		{
			mem->level->n_sector[mem->level->n] = mem->level->sector[i].neighbors[j];
			mem->level->n++;
		}
	}
	if (mem->level->n < mem->level->nb_sector)
		search_sector(mem, mem->level->n_sector[ok], ok + 1);
}

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
	int this_sector;
	int next_sector;

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

void sort_dist_monsters(t_mem *mem)
{
	int i;
	t_monster swap;

	i = 0;
	while (i < mem->level->nb_monsters)
	{
		mem->level->monsters[i].distance = distance(mem->level->monsters[i].x, mem->level->monsters[i].y, mem->level->player.x, mem->level->player.y);
		i++;
	}
	i = 0;
	while (i < mem->level->nb_monsters)
	{
		if (mem->level->monsters[i].distance < mem->level->monsters[i + 1].distance)
		{
			swap = mem->level->monsters[i];
			mem->level->monsters[i] = mem->level->monsters[i + 1];
			mem->level->monsters[i + 1] = swap;
			i = -1;
		}
		i++;
	}
}