/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   int_check.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 18:28:21 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 19:32:15 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int		double_int(int *tab, int nu, int nb)
{
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (tab[i] == nu)
			return (0);
	}
	return (1);
}
