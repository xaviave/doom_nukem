/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_applyflags_nb.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:08 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:08 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static int	pf_size_nb(char **str, t_flags *flags, int len)
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

static int	pf_width_nb(char **str, t_flags *flags, int len)
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

static int	pf_more_nb(char **str, t_flags *flags)
{
	char		*tmp;

	tmp = *str;
	if ((*str)[0] != '-')
	{
		if (!(*str = ft_strjoin(" ", *str)))
		{
			*str = tmp;
			return (0);
		}
		free(tmp);
		flags->more ? (*str)[0] = '+' : 0;
	}
	return (1);
}

int			pf_applyflags_nb(char **str, t_flags *flags)
{
	int		len;
	char	zero;

	flags->prec | flags->less ? flags->zero = 0 : 0;
	zero = (**str == '0') ? 1 : 0;
	if (flags->more | flags->space)
		if (!(pf_more_nb(str, flags)))
			return (0);
	if ((**str == '+' || **str == '-' || **str == ' ') && flags->zero)
		flags->width--;
	flags->zero ? flags->size = MAX(flags->size, flags->width) : 0;
	if (flags->prec && (!flags->size || flags->size == -1) && zero)
		(*str)[flags->more | flags->space ? 1 : 0] = '\0';
	len = ft_strlen(*str);
	if (len <= flags->size)
		if (!(pf_size_nb(str, flags, len)))
			return (0);
	len = ft_strlen(*str);
	if (len < flags->width)
		if (!(pf_width_nb(str, flags, len)))
			return (0);
	return (1);
}
