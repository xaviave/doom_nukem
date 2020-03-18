/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:44 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:44 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (len == 0)
		return (0);
	i = 0;
	str = (char *)haystack;
	if (!(ft_strlen(needle)))
		return (str);
	while (haystack[i] && (i < len))
	{
		j = 0;
		while ((needle[j] == haystack[i + j]) && ((i + j) < len))
		{
			if (needle[j + 1] == '\0')
				return (str);
			j++;
		}
		str++;
		i++;
	}
	return (NULL);
}
