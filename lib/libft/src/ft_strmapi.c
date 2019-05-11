/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:19:41 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:31:08 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			size;
	unsigned int	index;
	char			*str;

	size = ft_strlen((char *)s);
	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (0);
	index = 0;
	while (index < size)
	{
		str[index] = f(index, s[index]);
		index++;
	}
	str[size] = 0;
	return (str);
}
