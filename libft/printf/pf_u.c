/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_u.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:10 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:10 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static char	*recup_next(va_list ap, t_flags *flags)
{
	char		*next;

	if (flags->modif == null)
		next = pf_luitoa_base(va_arg(ap, unsigned int), "0123456789");
	else if (flags->modif == h)
		next = pf_luitoa_base((unsigned short)va_arg(ap, int), "0123456789");
	else if (flags->modif == hh)
		next = pf_luitoa_base((unsigned char)va_arg(ap, int), "0123456789");
	else
		next = pf_luitoa_base(va_arg(ap, unsigned long), "0123456789");
	return (next);
}

int			pf_u(va_list ap, t_flags *flags, char **str, int len)
{
	int		ret;
	char	*next;
	char	*tmp;

	flags->type == 'U' ? flags->modif = l : 0;
	if (!(next = recup_next(ap, flags)))
		return (-1);
	flags->more = 0;
	flags->space = 0;
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
