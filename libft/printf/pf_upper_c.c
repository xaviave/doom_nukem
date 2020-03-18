/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_upper_c.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:10 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:10 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static char	*width_c(t_flags *flags, int len_c)
{
	char		*ret;
	int			i;

	if (!(ret = (char*)ft_memalloc(flags->width * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < flags->width - len_c)
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
	int			len_c;

	len_c = ft_strlen(*c) ? ft_strlen(*c) : 1;
	if (flags->width > len_c)
		if (!(width = width_c(flags, len_c)))
			return (-1);
	tmp = *str;
	if (!flags->less && flags->width > len_c)
	{
		if (!(*str = ft_strnjoin(*str, width, len)))
			return (-1);
		len += flags->width - len_c;
	}
	if (!(*str = ft_strnjoin(*str, *c, len)))
		return (-1);
	if (flags->less && flags->width > len_c)
		if (!(*str = ft_strnjoin(*str, width, len + len_c)))
			return (-1);
	flags->width > len_c ? free(width) : 0;
	free(tmp);
	free(*c);
	return (flags->width < len_c ? len_c : flags->width);
}

int			pf_upper_c(va_list ap, t_flags *flags, char **str, int len)
{
	char	*c;
	int		letter;

	letter = va_arg(ap, unsigned int);
	if (letter)
		c = pf_unicode(letter);
	else
		c = ft_memalloc(2);
	if (!c)
		return (-1);
	return (pf_common(flags, str, len, &c));
}
