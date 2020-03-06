/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_to_level.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 11:12:12 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 19:24:26 by mel-akio    ###    #+. /#+    ###.fr     */
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
					level->sector[j].nb_linedef) > 0)
					add_sector_n(&level->sector[i], level->sector[j].id);
			}
	}
}

void			keys_shortcuts(t_level *level)
{
	ft_bzero(level->player.keys_shortcuts,
		sizeof(level->player.keys_shortcuts));
	level->player.keys_shortcuts[TOUCH_W] = MOVE_UP;
	level->player.keys_shortcuts[TOUCH_S] = MOVE_DOWN;
	level->player.keys_shortcuts[TOUCH_A] = MOVE_LEFT;
	level->player.keys_shortcuts[TOUCH_D] = MOVE_RIGHT;
	level->player.keys_shortcuts[TOUCH_F] = FLY;
	level->player.keys_shortcuts[TOUCH_LEFT] = ROTATE_LEFT;
	level->player.keys_shortcuts[TOUCH_RIGHT] = ROTATE_RIGHT;
	level->player.keys_shortcuts[TOUCH_NUMPAD_LESS] = ZOOM_OUT;
	level->player.keys_shortcuts[TOUCH_NUMPAD_PLUS] = ZOOM_IN;
	level->player.keys_shortcuts[TOUCH_BACKSPACE] = JUMP;
	level->player.keys_shortcuts[TOUCH_ECHAP] = EXIT_GAME;
	level->player.keys_shortcuts[TOUCH_R] = RELOAD;
	level->player.keys_shortcuts[TOUCH_C] = CROUCH;
	level->player.keys_shortcuts[TOUCH_E] = PICKUP;
}

void			parse_to_level(t_parse *parse, t_level *level)
{
	level->player = parse->player;
	keys_shortcuts(level);
	p_to_vertex(level, parse);
	p_to_linedef(level, parse);
	p_to_sector(level, parse);
	p_to_entity(level, parse);
	free_parse(parse);
	sector_neighbors(level);
}
