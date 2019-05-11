/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/26 19:23:50 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:32:56 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	n;
	char	*s_;

	n = ft_strlen(s);
	s_ = (char *)&s[n];
	while (s_ != s)
		if (*s_-- == (char)c)
			return ((char *)++s_);
	if (*s_ == (char)c)
		return ((char *)s_);
	return (0);
}
