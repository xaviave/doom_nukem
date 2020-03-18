/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strndup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:32 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:32 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strndup(char *s1, int len)
{
	char	*s2;

	if (!(s2 = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s2 = ft_strncpy(s2, s1, len);
	return (s2);
}
