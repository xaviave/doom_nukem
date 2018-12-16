/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 10:14:48 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/16 22:37:18 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

static void	init_parse(t_parse *parse)
{
	parse->sector = NULL;
	parse->sector = NULL;
	parse->player.x = -1;
	parse->player.y = -1;
}

/*
** check coord of the player if his coord aren't in the map
*/

int			main(int ac, char **av)
{
	t_parse	parse;

	init_parse(&parse);
	parse_map(ac, av, &parse);
	free_parse(&parse);
	return (0);
}
