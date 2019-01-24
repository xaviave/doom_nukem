/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:35 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:35 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*new;

	if (s1 && s2)
	{
		len = (ft_strlen(s1) + ft_strlen(s2));
		if (!(new = ft_memalloc(len + 1)))
			return (NULL);
		ft_strcat(new, s1);
		ft_strcat(new, s2);
		return (new);
	}
	return (NULL);
}
