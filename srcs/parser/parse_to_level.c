/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_to_level.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 11:12:12 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 17:16:05 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static int		count_same_linedef(int *tab1, int *tab2, int nb1, int nb2)
{
	int			i;
	int			j;
	int			nu;

	i = -1;
	nu = 0;
	while (++i < nb1)
	{
		j = -1;
		while (++j < nb2)
		{
			if (tab1[i] == tab2[j])
				nu++;
		}
	}
	return (nu);
}

static void		add_sector_n(t_sector *sector, int id)
{
	int			i;
	int			*tab;

	if (!(tab = (int *)malloc(sizeof(int) * (sector->nb_neighbors + 1))))
		return ;
	i = 0;
	while (i < sector->nb_neighbors)
	{
		tab[i] = sector->neighbors[i];
		i++;
	}
	if (sector->nb_neighbors > 1)
		free(sector->neighbors);
	tab[i] = id;
	sector->neighbors = tab;
	sector->nb_neighbors++;
}

static void		sector_neighbors(t_level *level)
{
	int			i;
	int			j;

	i = -1;
	while (++i < level->nb_sector)
	{
		j = -1;
		while (++j < level->nb_sector)
			if (j != i)
			{
				if (count_same_linedef(level->sector[i].linedef,
					level->sector[j].linedef, level->sector[i].nb_linedef,
					level->sector[j].nb_linedef) > 1)
					add_sector_n(&level->sector[i], level->sector[j].id);
			}
	}
}

void			parse_to_level(t_parse *parse, t_level *level)
{
	level->player = parse->player;
	p_to_vertex(level, parse);
	p_to_linedef(level, parse);
	p_to_sector(level, parse);
	free_parse(parse);
	sector_neighbors(level);
	aff_debug(level);
}
