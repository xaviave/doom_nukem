/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_c.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:09 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:09 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static char	*width_c(t_flags *flags)
{
	char		*ret;
	int			i;

	if (!(ret = (char*)ft_memalloc(flags->width * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < flags->width - 1)
	{
		ret[i] = flags->zero ? '0' : ' ';
		i++;
	}
	return (ret);
}

static int	pf_common(t_flags *flags, char **str, int len, char **c)
{
	char		*tmp;
	char		*width;

	if (flags->width > 1)
		if (!(width = width_c(flags)))
			return (-1);
	tmp = *str;
	if (!flags->less && flags->width > 1)
	{
		if (!(*str = ft_strnjoin(*str, width, len)))
			return (-1);
		len += flags->width - 1;
	}
	if (!(*str = ft_strnjoin(*str, *c, len)))
		return (-1);
	if (flags->less && flags->width > 1)
		if (!(*str = ft_strnjoin(*str, width, len + 1)))
			return (-1);
	flags->width > 1 ? free(width) : 0;
	free(tmp);
	free(*c);
	return (flags->width < 0 ? 1 : flags->width);
}

int			pf_no(t_flags *flags, char **str, int len, char **format)
{
	char	*c;

	if (**format)
	{
		if (!(c = (char *)ft_memalloc(2)))
			return (-1);
		*c = **format;
		(*format)++;
	}
	else
		return (0);
	return (pf_common(flags, str, len, &c));
}

int			pf_c(va_list ap, t_flags *flags, char **str, int len)
{
	char	*c;

	if (flags->modif == l || flags->type == 'C')
		return (pf_upper_c(ap, flags, str, len));
	if (!(c = (char *)ft_memalloc(2)))
		return (-1);
	*c = (char)va_arg(ap, int);
	return (pf_common(flags, str, len, &c));
}
