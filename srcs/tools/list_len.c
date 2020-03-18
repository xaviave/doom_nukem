/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_len.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 13:02:31 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 21:34:22 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

int				list_len_l(t_plinedef *list)
{
	int			i;
	t_plinedef	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int				list_len_v(t_pvertex *list)
{
	int			i;
	t_pvertex	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int				list_len_s(t_psector *list)
{
	int			i;
	t_psector	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int				list_len_e(t_pentity *list)
{
	int			i;
	t_pentity	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
