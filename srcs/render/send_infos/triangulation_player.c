/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangulation_player.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 18:18:06 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 20:24:42 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/doom.h"

int				in_box(t_mem *mem, int nb)
{
	int			i;

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
	if ((mem->level->player.x > mem->coord.x1 && mem->level->player.x <
		mem->coord.x2) || (mem->level->player.x == mem->coord.x1
		|| mem->level->player.x == mem->coord.x2))
		i++;
	if ((mem->level->player.y > mem->coord.y1 && mem->level->player.y <
		mem->coord.y2) || (mem->level->player.y == mem->coord.y1
		|| mem->level->player.y == mem->coord.y2))
		i++;
	return (i);
}

int				is_inside(t_vertex v1, t_vertex v2, t_vertex v3, t_vertex m)
{
	t_inside	i;

	i.s1 = v3.y - v1.y;
	i.s2 = v3.x - v1.x;
	i.s3 = v2.y - v1.y;
	i.s4 = m.y - v1.y;
	i.w1 = (v1.x * i.s1 + i.s4 * i.s2 - m.x * i.s1) /
		(i.s3 * i.s2 - (v2.x - v1.x) * i.s1);
	i.w2 = (i.s4 - i.w1 * i.s3) / i.s1;
	return (i.w1 >= 0 && i.w2 >= 0 && (i.w1 + i.w2) <= 1);
}

int				check_in_sector(t_mem *mem, int l1, int l2, int save)
{
	t_vertex	vertex;

	if (send_v_id(mem, save) == send_v_id(mem, l1)
		|| send_v_id(mem, save) == send_v_id(mem, l2))
		return (0);
	vertex.x = mem->level->player.x;
	vertex.y = mem->level->player.y;
	if (is_inside(mem->level->vertex[send_v_id(mem, save)],
			mem->level->vertex[send_v_id(mem, l1)],
			mem->level->vertex[send_v_id(mem, l2)], vertex))
		return (1);
	return (0);
}

static void		suite_sector(t_mem *mem, int i, int save)
{
	int			j;

	j = 0;
	while (++j < mem->level->sector[i].nb_linedef)
		if (check_in_sector(mem, mem->level->linedef[send_l_id(mem,
			mem->level->sector[i].linedef[j])].id_v1,
			mem->level->linedef[send_l_id(mem,
			mem->level->sector[i].linedef[j])].id_v2, save))
			mem->level->player.sector = mem->level->sector[i].id;
}

int				player_sector(t_mem *mem, int prev)
{
	int			i;
	int			save;

	i = -1;
	if (mem->level->player.sector != -1)
		mem->level->player.prev_sector = mem->level->player.sector;
	mem->level->player.sector = -1;
	while (++i < mem->level->nb_sector)
	{
		save = mem->level->linedef[send_l_id(mem,
			mem->level->sector[i].linedef[0])].id_v1;
		if (in_box(mem, i) == 2)
			suite_sector(mem, i, save);
	}
	if (prev)
		return (mem->level->player.sector);
	mem->level->n = 1;
	mem->level->n_sector[0] = mem->level->player.sector;
	fill_n_sector(mem, 0);
	return (mem->level->player.sector);
}
