/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flags.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:12:52 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:12:57 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static void		init_flag(t_flags *flags)
{
	flags->hashtag = 0;
	flags->zero = 0;
	flags->less = 0;
	flags->more = 0;
	flags->space = 0;
	flags->width = -1;
	flags->prec = 0;
	flags->size = -1;
	flags->modif = null;
	flags->type = 0;
}

static void		get_flags(char **format, t_flags *flags)
{
	while (ft_strchr("+- #0*", **format) && **format)
	{
		if (**format == '+')
			flags->more = 1;
		else if (**format == '-')
			flags->less = 1;
		else if (**format == ' ')
			flags->space = 1;
		else if (**format == '#')
			flags->hashtag = 1;
		else
			flags->zero = 1;
		(*format)++;
	}
}

static void		get_widthnprec(char **format, t_flags *flags)
{
	int			point;
	int			value;

	point = 0;
	if (**format == '.')
	{
		point = 1;
		(*format)++;
		flags->prec = 1;
	}
	if (!ft_isdigit(**format))
		return ;
	value = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
	if (point && **format != '.')
		value > flags->size ? flags->size = value : 0;
	else
		value > flags->width ? flags->width = value : 0;
}

static int		get_modifs(char **format, t_flags *flags)
{
	int			i;
	t_modif		save;

	if (**format == 'z' || flags->modif == z)
		flags->modif = z;
	else if (**format == 'j' || flags->modif == j)
		flags->modif = j;
	else if (**format == 'l' || flags->modif == l)
		flags->modif = l;
	save = flags->modif;
	if (**format && ft_strchr("zjl", **format))
		return (1);
	i = 0;
	while (**format == 'h')
	{
		(*format)++;
		i++;
	}
	if (i == 0)
		return (0);
	(*format)--;
	flags->modif = (i % 2 && flags->modif != hh) ? h : hh;
	save != h && save != hh && save != null ? flags->modif = save : 0;
	return (1);
}

int				pf_flags(char **format, t_flags *flags)
{
	init_flag(flags);
	while (**format && ft_strchr("0123456789#+- *.hljz", **format))
	{
		get_flags(format, flags);
		get_widthnprec(format, flags);
		*format += get_modifs(format, flags) ? 1 : 0;
	}
	if (**format && ft_strchr("sSpdDioOuUxXcC%", **format))
	{
		flags->type = **format;
		(*format)++;
	}
	flags->more ? flags->space = 0 : 0;
	return (0);
}
