/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   info_debug.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 16:58:28 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 16:59:27 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			aff_debug(t_level *level)
{
	int i = -1;
	ft_printf("\nVERTEX :\n");
	ft_printf("\n___________________________________________________\n");
	ft_printf("||       y        |        x        |    id      ||\n");
	ft_printf("___________________________________________________\n");
	while (++i < level->nb_vertex)
		ft_printf("|| y = %10d | x = %10d  | id = %5d ||\n", level->vertex[i].y,
			level->vertex[i].x, level->vertex[i].id);
	i = -1;
	ft_printf("___________________________________________________\n\n");
	int j;
	ft_printf("\nLINEDEF :\n");
	ft_printf("\n_____________________________________________________________________________________\n");
	ft_printf("||        id         |        v1        |        v2      |       text : heigth     ||\n");
	ft_printf("_____________________________________________________________________________________\n");
	while (++i < level->nb_linedef)
	{
		j = -1;
		ft_printf("||  id = %10d  |   v1 = %10d  |  v2 = %8d \t\t\t   ||\n|| \t\t\t\t\t\t\t\ttext : \t\t   ||\n", level->linedef[i].id,
			level->linedef[i].id_v1, level->linedef[i].id_v2, i);
		while (++j < level->linedef[i].side.nb_text)
			ft_printf("||\t\t\t\t\t\t\t\t| %d : %2d           ||\n", level->linedef[i].side.text[j], level->linedef[i].side.heigth[j]);
	ft_printf("\033[31m_____________________________________________________________________________________\n\033[0m");

	}
	ft_printf("\n\nSECTOR :\n\n____________________________________________________________________\n");
	ft_printf("|| sector |           linedef           |    h_floor - h_ceil     ||\n");
	ft_printf("____________________________________________________________________\n");
	i = -1;
	while (++i < level->nb_sector)
	{
		j = -1;
		ft_printf("|| %5d  |   ", level->sector[i].id);
		while (++j < level->sector[i].nb_linedef)
			ft_printf(" %3d", level->sector[i].linedef[j]);
		ft_printf("          |         %d - %d          ||\n____________________________________________________________________\n// neighbors_id : ", level->sector[i].h_floor, level->sector[i].h_ceil);
		j = -1;
		while (++j < level->sector[i].nb_neighbors)
			ft_printf(" %d //", level->sector[i].neighbors[j]);//bug
		ft_printf("\033[31m\n____________________________________________________________________\n\033[0m");
	}
	ft_printf("\n\nplayer x = %d y = %d", level->player.x, level->player.y);
}