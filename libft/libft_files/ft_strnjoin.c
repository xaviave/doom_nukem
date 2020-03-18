/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnjoin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:43 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:43 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	char	*new;

	if (!(s1 && s2))
		return (NULL);
	if (!(new = ft_memalloc((len + ft_strlen(s2)) + 1)))
		return (NULL);
	ft_strncat(new, s1, len);
	ft_strcat(new, s2);
	return (new);
}
