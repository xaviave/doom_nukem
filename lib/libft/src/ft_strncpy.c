/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/22 12:20:05 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/29 14:47:54 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	char	*dest_;

	dest_ = dest;
	while (n-- > 0)
		if (*src != '\0')
			*dest++ = *src++;
		else
			*dest++ = '\0';
	return (dest_);
}
