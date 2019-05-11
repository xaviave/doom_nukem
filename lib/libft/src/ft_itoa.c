/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/10 18:40:42 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 22:47:39 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa(int value)
{
	char			*it;
	const char		buff[10] = "0123456789";
	long			nb;
	int				n;
	size_t			size;

	n = value < 0 ? 1 : 0;
	nb = value < 0 ? (long)value*-1 : (long)value;
	size = value != 0 ? 0 : 1;
	while (nb)
	{
		size++;
		nb /= 10;
	}
	size += n;
	if (!(it = (char*)ft_memalloc(sizeof(char)*size + 1)))
		return (0);
	it[0] = '0';
	it[size+1] = 0;
	nb = value < 0 ? (long)value*-1 : (long)value;
	while (nb)
	{
		it[--size] = buff[nb % 10];
		nb /= 10;
	}
	it[0] = value < 0 ? '-' : it[0];
	return (it);
}
