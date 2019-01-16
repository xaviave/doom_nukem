/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_applyflags_str.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:09 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:09 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static int		pf_size_str(char **str, t_flags *flags)
{
	char	*tmp;
	int		i;

	if (!(tmp = (char*)malloc((flags->size + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (i < flags->size)
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = 0;
	free(*str);
	*str = tmp;
	return (1);
}

static int		pf_width_str(char **str, t_flags *flags, int len)
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
			new[i++] = flags->zero ? '0' : ' ';
	ft_strcat(new, *str);
	if (flags->less)
		while (len + i < flags->width)
			new[len + i++] = flags->zero ? '0' : ' ';
	free(*str);
	*str = new;
	return (1);
}

int				pf_applyflags_str(char **str, t_flags *flags)
{
	int		len;

	flags->less ? flags->zero = 0 : 0;
	len = ft_strlen(*str);
	if (flags->size != -1 && flags->size < len)
		if (!(pf_size_str(str, flags)))
			return (0);
	len = ft_strlen(*str);
	if (flags->width > len)
		if (!(pf_width_str(str, flags, len)))
			return (0);
	return (1);
}
