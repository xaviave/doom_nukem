/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/10 14:36:57 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:25:18 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*str_;
	char	*str;

	size = ft_strlen(s1);
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (0);
	str_ = str;
	while (*s1)
		*(str++) = *(s1++);
	*str = '\0';
	return (str_);
}
