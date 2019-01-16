/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:28:38 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:28:38 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	if (s)
	{
		if (!(new = (char *)malloc((ft_strlen(s) + 1) * sizeof(char))))
			return (NULL);
		i = 0;
		while (s[i])
		{
			new[i] = f(i, (char)(s[i]));
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}
