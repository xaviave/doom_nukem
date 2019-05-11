/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putendl.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 13:34:45 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:21:49 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void			ft_putendl(const char *str)
{
	const char	n = '\n';
	const char	*str_ = str;

	while (*str_)
		write(1, str_++, 1);
	write(1, &n, 1);
	return ;
}
