/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atol.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:26:56 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:32:51 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

long	ft_atol(const char *str, int *check)
{
	long	nb;
	int		neg;
	int		i;

	nb = 0;
	i = (str[0] == '-' || str[0] == '+' ? 0 : -1);
	while (str[++i])
		if (!ft_isdigit(str[i]))
		{
			*check = 1;
			return (0);
		}
	i = 0;
	neg = (str[i] == '-' ? 1 : 0);
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - 48;
	return (neg ? -nb : nb);
}
