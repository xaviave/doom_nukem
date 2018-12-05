/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_percent.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:10 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:10 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

int		pf_percent(t_flags *flags, char **str, int len)
{
	char	*next;
	char	*tmp;
	int		ret;

	if ((flags->prec && flags->size == -1) || flags->size == 0)
		flags->size = 1;
	if (!(next = (char*)ft_memalloc(2 * sizeof(char))))
		return (-1);
	*next = '%';
	if (!(pf_applyflags_str(&next, flags)))
		return (-1);
	ret = ft_strlen(next);
	tmp = *str;
	if (!(*str = ft_strnjoin(*str, next, len)))
		return (-1);
	free(tmp);
	free(next);
	return (ret);
}
