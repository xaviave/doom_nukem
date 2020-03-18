/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_line.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 14:42:02 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 22:46:43 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

static int				count_text(char *str)
{
	int					i;
	int					max;

	i = pass_digit_space(&str[0]);
	max = 0;
	while (i < (int)ft_strlen(str))
	{
		while (str[i] && (str[i] >= '1' && str[i] <= '9'))
			i++;
		i++;
		max++;
		i += pass_digit_space(&str[i]);
	}
	return (max);
}

static void				fill_sidedef(t_plinedef *list, char *str)
{
	int					i;
	int					j;
	int					max;

	j = 0;
	max = count_text(str);
	max += (max == 0) ? 1 : 0;
	list->nb_text = max;
	if (!(list->text = (int *)malloc(sizeof(int) * max)))
		return ;
	if (!(list->heigth = (int *)malloc(sizeof(int) * max)))
		return ;
	list->text[j] = ft_atoi(str);
	list->heigth[j] = -1;
	i = pass_digit_space(str);
	while (++j < max)
	{
		ft_printf("%s | %d | %d\n", &str[i], i, max);
		list->heigth[j] = ft_atoi(&str[i]);
		while (str[i] && (str[i] >= '0' && str[i] <= '9'))
			i++;
		i++;
		list->text[j] = ft_atoi(&str[i]);
		i += pass_digit_space(&str[i]);
	}
}

static t_plinedef		*new_list_l(char *str)
{
	int					i;
	t_plinedef			*new;

	i = 0;
	if (!(new = (t_plinedef *)malloc(sizeof(t_plinedef))))
		return (NULL);
	new->id = ft_atoi(str);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	i += pass_digit_space(&str[i]);
	new->id_v1 = ft_atoi(&str[i]);
	i += pass_digit_space(&str[i]);
	new->id_v2 = ft_atoi(&str[i]);
	i += pass_digit_space(&str[i]);
	fill_sidedef(new, &str[i]);
	new->next = NULL;
	return (new);
}

void					add_list_l(t_plinedef **linedef, char *str)
{
	t_plinedef			*tmp;

	if (!(*linedef))
		*linedef = new_list_l(str);
	else
	{
		tmp = *linedef;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_list_l(str);
	}
}
