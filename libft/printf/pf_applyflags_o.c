/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_applyflags_o.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:08 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:09 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static int	pf_size_o(char **str, t_flags *flags, int len)
{
	char		*tmp;
	char		sign[2];
	int			i;

	sign[0] = '\0';
	sign[1] = '\0';
	**str == '+' || **str == '-' || **str == ' ' ? *sign = **str : 0;
	*sign ? *str += 1 : 0;
	*sign ? len -= 1 : 0;
	if (!(tmp = (char*)ft_memalloc((flags->size + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (++i <= flags->size)
	{
		if (len - i >= 0)
			tmp[flags->size - i] = (*str)[len - i];
		else
			tmp[flags->size - i] = '0';
	}
	*sign ? free(*str - 1) : free(*str);
	if (!(*str = ft_strjoin(sign, tmp)))
		return (0);
	free(tmp);
	return (1);
}

static int	pf_width_o(char **str, t_flags *flags, int len)
{
	char	*new;
	int		nb_space;
	int		i;

	if (!(new = (char*)ft_memalloc((flags->width + 1) * sizeof(char))))
		return (0);
	nb_space = flags->width - len;
	i = 0;
	if (!flags->less)
		while (i < nb_space)
			new[i++] = ' ';
	ft_strcat(new, *str);
	if (flags->less)
		while (len + i < flags->width)
			new[len + i++] = ' ';
	free(*str);
	*str = new;
	return (1);
}

static int	pf_hashtag_o(char **str, t_flags *flags)
{
	char		*tmp;

	if (flags->type == 'x')
		if (!(tmp = ft_strjoin("0x", *str)))
			return (0);
	if (flags->type == 'X')
		if (!(tmp = ft_strjoin("0X", *str)))
			return (0);
	if (flags->type == 'O' || flags->type == 'o')
		if (!(tmp = ft_strjoin("0", *str)))
			return (0);
	free(*str);
	*str = tmp;
	return (1);
}

int			pf_applyflags_o(char **str, t_flags *flags)
{
	int		len;

	flags->prec | flags->less ? flags->zero = 0 : 0;
	flags->zero ? flags->size = MAX(flags->size, flags->width) : 0;
	if (flags->prec && (!flags->size || flags->size == -1) && **str == '0')
	{
		free(*str);
		if (!(*str = ft_memalloc(1)))
			return (0);
	}
	len = ft_strlen(*str);
	if (len <= flags->size)
		if (!(pf_size_o(str, flags, len)))
			return (0);
	if (flags->hashtag && **str != '0')
		if (!(pf_hashtag_o(str, flags)))
			return (0);
	len = ft_strlen(*str);
	if (len < flags->width)
		if (!(pf_width_o(str, flags, len)))
			return (0);
	return (1);
}
