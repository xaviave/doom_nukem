/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   p_to_level.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 17:13:17 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 21:41:44 by xamartin    ###    #+. /#+    ###.fr     */
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

void			p_to_entity(t_level *level, t_parse *parse)
{
	int			i;
	t_pentity	*tmp;

	level->nb_entity = list_len_e(parse->entity);
	if (!(level->entity = (t_entity *)malloc(sizeof(t_entity)
		* level->nb_entity)))
		return ;
	i = 0;
	tmp = parse->entity;
	while (tmp)
	{
		level->entity[i].alive = 1;
		level->entity[i].shooting = 0;
		level->entity[i].distance = 0;
		level->entity[i].id = tmp->id;
		level->entity[i].x = tmp->x;
		level->entity[i].y = tmp->y;
		level->entity[i].z = tmp->z;
		level->entity[i].text = tmp->text;
		i++;
		tmp = tmp->next;
	}
}
