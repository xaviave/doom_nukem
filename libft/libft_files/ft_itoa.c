/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:27:11 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:27:11 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "../header/libft.h"

static int		ft_nbdigits(int nb)
{
	int		nb_digits;
	long	n;

	n = (long)nb;
	if (n < 0)
		n *= -1;
	nb_digits = 0;
	while (n /= 10)
		nb_digits++;
	return (nb_digits);
}

char			*ft_itoa(int n)
{
	char	*a_nb;
	int		neg;
	int		i;
	long	nb;

	nb = (long)n;
	neg = 0;
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb < 0)
		nb *= (neg = -1);
	if (!(a_nb = malloc((ft_nbdigits(nb) + 1 + (neg * -1)) * sizeof(char))))
		return (NULL);
	i = 0;
	while (nb)
	{
		a_nb[i++] = '0' + (nb % 10);
		nb /= 10;
	}
	if (neg == -1)
		a_nb[i++] = '-';
	a_nb[i] = '\0';
	return (ft_strrev(a_nb));
}
