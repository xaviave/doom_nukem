/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 15:01:45 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:31:29 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	size;
	size_t	i;
	char	*str;

	size = ft_strlen((char *)s);
	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (0);
	i = 0;
	while (i < size)
	{
		str[i] = f(s[i]);
		i++;
	}
	str[size] = 0;
	return (str);
}
