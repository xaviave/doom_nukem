/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 18:14:20 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:16:12 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_isnotspace(char c)
{
	return (((c != ' ') && (c != '\n') && (c != '\t')) ? 1 : 0);
}

char			*ft_strtrim(char const *s)
{
	char	*ptr_end;

	while (!ft_isnotspace(*s))
		s++;
	if (!*s)
		return (ft_strnew(0));
	ptr_end = (char *)s + ft_strlen(s) - 1;
	while (!ft_isnotspace(*ptr_end))
		ptr_end--;
	return (ft_strsub(s, 0, ptr_end - s + 1));
}
