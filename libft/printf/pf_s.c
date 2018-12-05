/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_s.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:10 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:10 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

int			pf_s(va_list ap, t_flags *flags, char **str, int len)
{
	int		ret;
	char	*next;
	char	*tmp;

	if (flags->modif == l || flags->type == 'S')
		return (pf_upper_s(ap, flags, str, len));
	if (flags->prec && flags->size == -1)
		flags->size = 0;
	tmp = va_arg(ap, char*);
	if (tmp)
		if (!(next = ft_strdup(tmp)))
			return (-1);
	if (!tmp)
		if (!(next = ft_strdup("(null)")))
			return (-1);
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
