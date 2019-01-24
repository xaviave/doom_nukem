/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtoupper.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:51 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:51 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strtoupper(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_islower(s[i]))
			s[i] = ft_toupper(s[i]);
		i++;
	}
	return (s);
}
