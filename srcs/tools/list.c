/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/10 14:48:24 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 17:47:00 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static t_pvertex		*new_list_v(char *y, char *x, char *id)
{
	t_pvertex			*new;

	if (!(new = (t_pvertex *)malloc(sizeof(t_pvertex))))
		return (NULL);
	new->y = ft_atoi(y);
	new->x = ft_atoi(x);
	new->id = ft_atoi(id);
	new->next = NULL;
	return (new);
}

void					add_list_v(t_pvertex **vertex,
	char *y, char *x, char *id)
{
	t_pvertex			*tmp;

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

static t_psector		*new_list_s(char *str)
{
	int					i;
	t_psector			*new;

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
	new->linedef = create_vertex(&str[i]);
	new->nb_linedef = count_int(&str[i]);
	new->nb_vertex = new->nb_linedef;
	new->next = NULL;
	return (new);
}

void					add_list_s(t_psector **sector, char *str)
{
	t_psector			*tmp;

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
