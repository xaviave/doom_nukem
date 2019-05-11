/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_striteri.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 14:59:13 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:29:09 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void				ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	index;

	index = 0;
	while (*str)
		f(index++, str++);
	return ;
}
