/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_len.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 13:02:31 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/18 13:19:48 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

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
