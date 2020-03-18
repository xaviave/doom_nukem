/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_base.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:09 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:09 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static int		get_base(char **b, char type)
{
	if (type == 'x' || type == 'p')
		*b = ft_strdup("0123456789abcdef");
	else if (type == 'X')
		*b = ft_strdup("0123456789ABCDEF");
	else
		*b = ft_strdup("01234567");
	if (!(*b))
		return (0);
	return (1);
}

static char		*recup_next(va_list ap, t_flags *flags)
{
	char		*tmp;
	char		*next;

	if (!(get_base(&tmp, flags->type)))
		return (NULL);
	if (flags->modif == null && flags->type != 'O')
		next = pf_luitoa_base(va_arg(ap, unsigned int), tmp);
	else if (flags->modif == h && flags->type != 'O')
		next = pf_luitoa_base((unsigned short)va_arg(ap, unsigned int), tmp);
	else if (flags->modif == hh && flags->type != 'O')
		next = pf_luitoa_base((unsigned char)va_arg(ap, unsigned int), tmp);
	else
		next = pf_luitoa_base(va_arg(ap, unsigned long), tmp);
	free(tmp);
	return (next);
}

int				pf_base(va_list ap, t_flags *flags, char **str, int len)
{
	int		ret;
	char	*next;
	char	*tmp;

	if (!(next = recup_next(ap, flags)))
		return (-1);
	tmp = *str;
	if (flags->type == 'x' || flags->type == 'X' || flags->type == 'p')
	{
		if (!(pf_applyflags_x(&next, flags)))
			return (-1);
	}
	else if (!(pf_applyflags_o(&next, flags)))
		return (-1);
	ret = ft_strlen(next);
	if (!(*str = ft_strnjoin(*str, next, len)))
		return (-1);
	free(next);
	free(tmp);
	return (ret);
}
