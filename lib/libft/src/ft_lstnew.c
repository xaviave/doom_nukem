/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 19:03:25 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 07:59:58 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(const void *content, size_t size)
{
	t_list	*new_list;

	if (!(new_list = (t_list *)ft_memalloc(sizeof(struct s_list) + 1)))
		return (0);
	if (!content)
		return (new_list);
	if (!(new_list->content = (void *)ft_memalloc(size)))
		ft_memdel((void **)&new_list);
	ft_memcpy(new_list->content, content, size);
	new_list->size = size;
	return (new_list);
}
