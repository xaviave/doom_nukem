/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 19:03:25 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 23:16:20 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "./libft.h"

t_list				*ft_lstnew(const void *content, size_t size)
{
	t_list			*new_list;

	if (!(new_list = (t_list *)ft_memalloc(sizeof(t_list))))
		return (0);
	if (!(new_list->content = (void *)ft_memalloc(size)))
		return (new_list);
	ft_memcpy(new_list->content, content, size);
	new_list->size = size;
	return (new_list);
}
