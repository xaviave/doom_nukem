/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 11:27:29 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 11:27:29 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		new->content = (NULL);
		new->content_size = 0;
	}
	else
	{
		new->content = ft_memalloc(content_size);
		ft_memmove(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = (NULL);
	return (new);
}
