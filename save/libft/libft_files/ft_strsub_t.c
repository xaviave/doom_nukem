/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:49 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:49 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	char	*cur;

	if (s)
	{
		if (!(sub = (char *)malloc((len + 1) * sizeof(char))))
			return (NULL);
		cur = (char *)s + start;
		i = 0;
		while (cur[i] && (i < len))
		{
			sub[i] = cur[i];
			i++;
		}
		sub[i] = '\0';
		return (sub);
	}
	return (NULL);
}
