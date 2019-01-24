/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bubble_sort.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:26:59 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:26:59 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static void		ft_int_swap(int *a, int *b)
{
	int		tmp;

	if (!(a && b))
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int				*ft_bubble_sort(int *tab, int length)
{
	int		*fresh;
	int		i;
	int		j;

	if (!tab)
		return (NULL);
	i = 0;
	if (!(fresh = (int *)ft_memalloc(length * sizeof(int))))
		return (NULL);
	ft_memcpy(fresh, tab, length * sizeof(int));
	i = 0;
	while (i < length)
	{
		j = 0;
		while (j < length - 1 - i)
		{
			if (fresh[j] > fresh[j + 1])
				ft_int_swap(&(fresh[j]), &(fresh[j + 1]));
			j++;
		}
		i++;
	}
	return (fresh);
}
