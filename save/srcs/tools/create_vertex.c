/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   create_vertex.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/14 14:52:04 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/16 22:19:08 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int			count_int(char *str)
{
	int		i;
	int		nu;

	i = 0;
	nu = 0;
	while (i < (int)ft_strlen(str))
	{
		nu++;
		i += pass_digit_space(&str[i]);
	}
	return (nu);
}

int			*create_vertex(char *str)
{
	int		i;
	int		j;
	int		max;
	int		*new;

	j = -1;
	i = 0;
	max = count_int(str);
	if (!(new = (int *)malloc(sizeof(int) * max)))
		return (NULL);
	while (++j < max)
	{
		new[j] = ft_atoi(&str[i]);
		i += pass_digit_space(&str[i]);
	}
	return (new);
}
