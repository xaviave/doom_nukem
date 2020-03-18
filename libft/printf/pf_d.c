/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_d.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:09 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:09 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

int			pf_d(va_list ap, t_flags *flags, char **str, int len)
{
	int		ret;
	char	*next;
	char	*tmp;

	flags->type == 'D' ? flags->modif = l : 0;
	if (flags->modif == null)
		next = pf_litoa_base(va_arg(ap, int), "0123456789");
	else if (flags->modif == h)
		next = pf_litoa_base((short)va_arg(ap, int), "0123456789");
	else if (flags->modif == hh)
		next = pf_litoa_base((char)va_arg(ap, int), "0123456789");
	else
		next = pf_litoa_base(va_arg(ap, long), "0123456789");
	if (!next)
		return (-1);
	if (!(pf_applyflags_nb(&next, flags)))
		return (-1);
	ret = ft_strlen(next);
	tmp = *str;
	if (!(*str = ft_strnjoin(*str, next, len)))
		return (-1);
	free(tmp);
	free(next);
	return (ret);
}
