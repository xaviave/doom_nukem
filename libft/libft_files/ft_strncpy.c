/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:41 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:41 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t			i;

	if (len == 0)
		return ((char *)dst);
	i = 0;
	while (src[i] != '\0' && (i < len))
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
		dst[i++] = '\0';
	return ((char *)dst);
}
