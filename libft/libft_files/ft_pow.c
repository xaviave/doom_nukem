/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pow.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:27:40 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:27:40 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

int		ft_pow(int n, int pow)
{
	long	result;
	size_t	i;

	i = 0;
	if (pow == 0)
		return (1);
	result = n;
	while ((int)i < pow - 1)
	{
		result *= n;
		i++;
	}
	return ((int)result);
}
