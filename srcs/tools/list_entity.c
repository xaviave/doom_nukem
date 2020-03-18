/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_entity.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 20:34:01 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 21:08:36 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static t_pentity		*new_list_e(char *str)
{
	int					i;
	t_pentity			*new;

	i = 0;
	if (!(new = (t_pentity *)malloc(sizeof(t_pentity))))
		return (NULL);
	new->id = ft_atoi(str);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	i += pass_digit_space(&str[i]);
	new->x = ft_atoi(&str[i]);
	i += pass_digit_space(&str[i]);
	new->y = ft_atoi(&str[i]);
	i += pass_digit_space(&str[i]);
	new->z = ft_atoi(&str[i]);
	i += pass_digit_space(&str[i]);
	new->text = ft_atoi(&str[i]);
	new->next = NULL;
	return (new);
}

void					add_list_e(t_pentity **entity, char *str)
{
	t_pentity			*tmp;

	if (!(*entity))
		*entity = new_list_e(str);
	else
	{
		tmp = *entity;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_list_e(str);
	}
}
