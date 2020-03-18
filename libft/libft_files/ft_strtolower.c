/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtolower.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:50 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:50 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strtolower(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_isupper(s[i]))
			s[i] = ft_tolower(s[i]);
		i++;
	}
	return (s);
}
