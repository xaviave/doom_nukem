/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_to_level.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 11:12:12 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/07 17:34:14 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			aff_debug(t_level *level)
{
	int i = -1;
	ft_printf("\n___________________________________________________\n");
	ft_printf("||       y        |        x        |    id      ||\n");
	ft_printf("___________________________________________________\n");
	while (++i < level->nb_vertex)
		printf("|| y = %10f | x = %10f  | id = %5d ||\n", level->vertex[i].y,
			level->vertex[i].x, level->vertex[i].id);
	ft_printf("___________________________________________________\n");
	ft_printf("\n_________________________________________\n");
	ft_printf("|| sector |           vertex           ||\n");
	ft_printf("_________________________________________\n");
	int j;
	i = -1;
	while (++i < level->nb_sector)
	{
		j = -1;
		ft_printf("|| %5d  |", level->sector[i].id);
		while (++j < level->sector[i].nb_vertex)
			ft_printf(" %3d", level->sector[i].vertex[j]);
		ft_printf(" ||\n_________________________________________\n");
		j = -1;
		while (++j < level->sector[i].nb_neighbors)
			ft_printf("// %d //", level->sector[i].neighbors[j]);
		ft_printf(" ||\n_________________________________________\n");
	}
	ft_printf("\nplayer x = %d y = %d", level->player.x, level->player.y);
}

static void		p_to_vertex(t_level *level, t_parse *parse)
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

static int		*copy_int(int	*vertex, int nu)
{
	int			i;
	int			*copy;

	i = -1;
	if (!(copy = (int *)malloc(sizeof(int) * nu)))
		return (NULL);
	while (++i < nu)
		copy[i] = vertex[i];
	return (copy);
}

static void		p_to_sector(t_level *level, t_parse *parse)
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
		level->sector[i].nb_vertex = tmp->nu_vertex;
		level->sector[i].vertex = copy_int(tmp->vertex, tmp->nu_vertex);
		level->sector[i].nb_neighbors = 0;
		i++;
		tmp = tmp->next;
	}
}

static int		count_same_vertex(int *tab1, int *tab2, int nb1, int nb2)
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
			if (i != j && tab1[i] == tab2[j])
				nu++;
	}
	return (nu);
}

static void		add_sector_n(t_sector *sector, int id)
{
	int			i;
	int			*tab;

	if (!(tab = (int *)malloc(sizeof(int) * (sector->nb_neighbors + 1))))
		return ;
	i = -1;
	while (sector->nb_neighbors > 1 && ++i < sector->nb_neighbors + 1)
		tab[i] = sector->neighbors[i];
	if (sector->nb_neighbors > 1)
		free(sector->neighbors);
	sector->neighbors = tab;
	sector->neighbors[i + 1] = id;
	i = -1;
	while (++i < sector->nb_neighbors)
		ft_printf("|||||| %d ", sector->neighbors[i]);
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
				if (count_same_vertex(level->sector[i].vertex,
					level->sector[j].vertex, level->sector[i].nb_vertex,
					level->sector[j].nb_vertex) > 1)
				{
					add_sector_n(&level->sector[i], level->sector[j].id);
					level->sector[i].nb_neighbors++;
				}
			}
	}
}

void			parse_to_level(t_parse *parse, t_level *level)
{
	level->player = parse->player;
	p_to_vertex(level, parse);
	p_to_sector(level, parse);
	free_parse(parse);
	aff_debug(level);
	sector_neighbors(level);
}