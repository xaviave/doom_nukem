/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/09 01:40:23 by mel-akio     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 01:40:31 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		first_screen(t_mem *mem)
{
	ft_bzero(mem->img.data, W * H * 4);
	mlx_string_put(mem->mlx_ptr, mem->win.win_ptr, W / 2 - 100, H / 2, 0xFFFFFF,
	"Attention ! Des ennemis attaquent votre vaisseau ! Tuez les !");
}

void		end_screen(t_mem *mem)
{
	ft_bzero(mem->img.data, W * H * 4);
	mlx_string_put(mem->mlx_ptr, mem->win.win_ptr, W / 2 - 100, H / 2, 0xFFFFFF,
	"Fin.");
}

void		check_mobs(t_mem *mem)
{
	int		i;
	int		c;

	i = -1;
	c = 0;
	while (++i < mem->level->nb_entity)
		if (mem->level->entity[i].text == MOB && mem->level->entity[i].alive)
			c++;
	if (!c)
		mem->end = 1;
}
