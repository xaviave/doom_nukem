/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_parsing.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:30:06 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 23:44:18 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void		free_parse2(t_parse *parse)
{
	t_plinedef	*tmp3;
	t_pentity	*tmp4;

	if (parse->linedef)
		while (parse->linedef)
		{
			tmp3 = parse->linedef;
			parse->linedef = parse->linedef->next;
			free(tmp3->heigth);
			free(tmp3->text);
			free(tmp3);
		}
	if (parse->entity)
		while (parse->entity)
		{
			tmp4 = parse->entity;
			parse->entity = parse->entity->next;
			free(tmp4);
		}
}

void			free_parse(t_parse *parse)
{
	t_pvertex	*tmp;
	t_psector	*tmp2;

	if (parse->vertex)
		while (parse->vertex)
		{
			tmp = parse->vertex;
			parse->vertex = parse->vertex->next;
			free(tmp);
		}
	if (parse->sector)
		while (parse->sector)
		{
			tmp2 = parse->sector;
			parse->sector = parse->sector->next;
			free(tmp2->linedef);
			free(tmp2);
		}
	free_parse2(parse);
}

static void		free_level2(t_level *level)
{
	if (level->entity)
		free(level->entity);
	if (level->monsters)
		free(level->monsters);
	if (level->n_sector)
		free(level->n_sector);
}

void			free_level(t_level *level)
{
	int			i;

	if (level->vertex)
		free(level->vertex);
	if (level->linedef && (i = -1))
	{
		while (++i < level->nb_linedef)
		{
			if (level->linedef[i].side.heigth)
				free(level->linedef[i].side.heigth);
			if (level->linedef[i].side.text)
				free(level->linedef[i].side.text);
		}
		free(level->linedef);
	}
	if (level->sector && (i = -1))
	{
		while (++i < level->nb_sector && level->sector[i].nb_linedef)
			free(level->sector[i].linedef);
		i = -1;
		while (++i < level->nb_sector && level->sector[i].nb_neighbors)
			free(level->sector[i].neighbors);
		free(level->sector);
	}
	free_level2(level);
}

void			return_error(int error, t_parse *parse)
{
	if (!error)
		ft_printf("\nError 0 : No args, need a map\n");
	else if (error == 1)
		ft_printf("\nError 1 : Name must finish by .dk & have one char\n");
	else if (error == 2)
		ft_printf("\nError 2 : File doesn't exist or can't be open\n");
	else if (error == 3)
		ft_printf("\nError 3 : Bad vertex init\n");
	else if (error == 4)
		ft_printf("\nError 4 : Bad sector init\n");
	else if (error == 5)
		ft_printf("\nError 5 : Bad player init\n");
	else if (error == 6)
		ft_printf("\nError 6 : Unknown character found\n");
	else if (error == 7)
		ft_printf("\nError 7 : Not enougth vertex or sector\n");
	else if (error == 8)
		ft_printf("\nError 8 : Bad floor or ceiling heigth\n");
	else if (error == 9)
		ft_printf("\nError 9 : Bad linedef or entity init\n");
	else if (error == -1)
		ft_printf("\nError -1 : Bad texture heigth | Player not initialized\n");
	if (parse)
		free_parse(parse);
	exit(0);
}
