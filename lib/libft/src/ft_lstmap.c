/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 20:38:49 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 00:18:17 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new;
	t_list		*list;

	list = (*f)(lst);
	new = list;
	while ((lst = lst->next))
	{
		if (!(list->next = (*f)(lst)))
		{
			free(list->next);
			return (0);
		}
		list = list->next;
	}
	return (new);
}
