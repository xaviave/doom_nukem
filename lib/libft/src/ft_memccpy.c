/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/21 13:06:21 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:18:29 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n-- > 0)
		if (*(unsigned char *)src == (unsigned char)c &&
			*(unsigned char *)src &&
			(*(unsigned char *)dest++ = *(unsigned char *)src++))
			return (dest);
		else
			*(unsigned char *)dest++ = *(unsigned char *)src++;
	return (0);
}
