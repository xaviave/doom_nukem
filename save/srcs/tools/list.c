/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/10 14:48:24 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/16 22:14:19 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_pvertex		*new_list_v(char *y, char *x, char *id)
{
	t_pvertex	*new;

	if (!(new = (t_pvertex *)malloc(sizeof(t_pvertex))))
		return (NULL);
	new->y = ft_atoi(y);
	new->x = ft_atoi(x);
	new->id = ft_atoi(id);
	new->next = NULL;
	return (new);
}

void			add_list_v(t_pvertex **vertex, char *y, char *x, char *id)
{
	t_pvertex	*tmp;

	if (!(*vertex))
		*vertex = new_list_v(y, x, id);
	else
	{
		tmp = *vertex;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_list_v(y, x, id);
	}
}

t_psector		*new_list_s(char *str)
{
	int			i;
	t_psector	*new;

	i = 0;
	if (!(new = (t_psector *)malloc(sizeof(t_psector))))
		return (NULL);
	new->id = ft_atoi(str);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	i += pass_digit_space(&str[i]);
	new->ground = ft_atoi(&str[i]);
	i += pass_digit_space(&str[i]);
	new->ceiling = ft_atoi(&str[i]);
	i += pass_digit_space(&str[i]);
	new->vertex = create_vertex(&str[i]);
	new->nu_vertex = count_int(&str[i]);
	new->next = NULL;
	return (new);
}

void			add_list_s(t_psector **sector, char *str)
{
	t_psector	*tmp;

	if (!(*sector))
		*sector = new_list_s(str);
	else
	{
		tmp = *sector;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_list_s(str);
	}
}
