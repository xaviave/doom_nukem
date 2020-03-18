/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 15:08:38 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 14:07:34 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*troncon;
	unsigned int	i;
	unsigned int	y;

	i = start;
	y = 0;
	if (s == NULL)
		return (NULL);
	if ((troncon = ft_strnew(len)) == NULL)
		return (NULL);
	while (i < (start + len))
	{
		troncon[y] = s[i];
		i++;
		y++;
	}
	troncon[y] = '\0';
	return (troncon);
}
