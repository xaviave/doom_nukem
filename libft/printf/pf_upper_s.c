/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_upper_s.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:11 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:21 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static char	*recup_next(unsigned int *wstr, t_flags *flags)
{
	char		*str;
	int			i;
	char		*tmp;
	char		*new;

	if (!wstr)
		return (ft_strdup("(null)"));
	if (!(str = ft_memalloc(1)))
		return (NULL);
	i = -1;
	while (wstr[++i] && (flags->size == -1 || i < flags->size))
	{
		tmp = str;
		if (!(new = pf_unicode(wstr[i])))
		{
			free(str);
			return (NULL);
		}
		if (!(str = ft_strjoin(str, new)))
			return (NULL);
		free(tmp);
		free(new);
	}
	return (str);
}

static void	modif_size(char *next, t_flags *flags)
{
	while (-128 <= next[flags->size] && next[flags->size] <= -65 &&
			flags->size > 0)
		flags->size--;
}

int			pf_upper_s(va_list ap, t_flags *flags, char **str, int len)
{
	unsigned int	*wstr;
	char			*next;
	char			*tmp;
	int				ret;

	if (flags->prec && flags->size == -1)
		flags->size = 0;
	wstr = va_arg(ap, unsigned int*);
	if (!(next = recup_next(wstr, flags)))
		return (-1);
	if (flags->size < (int)ft_strlen(next))
		modif_size(next, flags);
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
