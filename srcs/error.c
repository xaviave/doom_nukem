/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:30:06 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/18 13:09:14 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h"

void			free_parse(t_parse *parse)
{
	t_pvertex	*tmp;
	t_psector	*tmp2;

	if (parse->vertex)
	{
		while (parse->vertex)
		{
			tmp = parse->vertex;
			parse->vertex = parse->vertex->next;
			free(tmp);
		}
	}
	if (parse->sector)
	{
		while (parse->sector)
		{
			tmp2 = parse->sector;
			parse->sector = parse->sector->next;
			free(tmp2->vertex);
			free(tmp2);
		}
	}
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
	free_parse(parse);
	exit(0);
}
