/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   p_to_level.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 17:13:17 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 20:02:02 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			p_to_vertex(t_level *level, t_parse *parse)
{
	int			i;
	t_pvertex	*tmp;

	level->nb_vertex = list_len_v(parse->vertex);
	if (!(level->vertex = (t_vertex *)malloc(sizeof(t_vertex)
		* level->nb_vertex)))
		return ;
	i = 0;
	tmp = parse->vertex;
	while (tmp)
	{
		level->vertex[i].x = tmp->x;
		level->vertex[i].y = tmp->y;
		level->vertex[i].id = tmp->id;
		i++;
		tmp = tmp->next;
	}
}

void			p_to_linedef(t_level *level, t_parse *parse)
{
	int			i;
	t_plinedef	*tmp;

	level->nb_linedef = list_len_l(parse->linedef);
	if (!(level->linedef = (t_linedef *)malloc(sizeof(t_linedef)
		* level->nb_linedef)))
		return ;
	i = 0;
	tmp = parse->linedef;
	while (tmp)
	{
		level->linedef[i].id = tmp->id;
		level->linedef[i].side.heigth = copy_int(tmp->heigth, tmp->nb_text);
		level->linedef[i].side.text = copy_int(tmp->text, tmp->nb_text);
		level->linedef[i].side.nb_text = tmp->nb_text;
		level->linedef[i].id_v1 = tmp->id_v1;
		level->linedef[i].id_v2 = tmp->id_v2;
		level->linedef[i].nb_neigboors = 0;
		tmp = tmp->next;
		i++;
	}
}

void			p_to_sector(t_level *level, t_parse *parse)
{
	int			i;
	t_psector	*tmp;

	level->nb_sector = list_len_s(parse->sector);
	if (!(level->sector = (t_sector *)malloc(sizeof(t_sector)
		* level->nb_sector)))
		return ;
	i = 0;
	tmp = parse->sector;
	while (tmp)
	{
		level->sector[i].h_ceil = tmp->ceiling;
		level->sector[i].h_floor = tmp->ground;
		level->sector[i].id = tmp->id;
		level->sector[i].nb_linedef = tmp->nb_vertex;
		level->sector[i].nb_vertex = tmp->nb_linedef;
		level->sector[i].linedef = copy_int(tmp->linedef, tmp->nb_linedef);
		level->sector[i].nb_neighbors = 0;
		i++;
		tmp = tmp->next;
	}
}

void		p_to_spawn(t_level *level, t_parse *parse)
{
	level->spawn.x = parse->player.x;
	level->spawn.y = parse->player.y;
	level->spawn.z = parse->player.z;
	level->spawn.camX = 1600;
	level->spawn.camY = 0;
	level->spawn.angle = parse->player.angle;
	return ;
}
