/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:58:05 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:28:35 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*ptr;

	if (!(str = (char*)ft_memalloc(sizeof(char) * (ft_strlen(s1)
		+ ft_strlen(s2) + 1))))
		return (0);
	ptr = str;
	while (*s1 || *s2)
		*ptr++ = (*s1) ? *s1++ : *s2++;
	return (str);
}
