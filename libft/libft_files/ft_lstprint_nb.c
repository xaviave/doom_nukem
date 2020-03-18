/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstprint_nb.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:27:29 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:27:29 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

void	ft_lstprint_nb(t_list *lst)
{
	while (lst)
	{
		ft_printf("%d ", *(int*)lst->content);
		lst = lst->next;
	}
}
