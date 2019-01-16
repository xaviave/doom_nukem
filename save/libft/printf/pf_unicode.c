/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_unicode.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:10 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:10 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static char		*pf_simple_char(int i)
{
	char	*str;

	if (!(str = ft_memalloc(2)))
		return (NULL);
	i = i & 0b01111111;
	*str = i;
	return (str);
}

static char		*pf_double_char(int i)
{
	int		p[2];
	char	*str;

	p[0] = i & 0b111111;
	p[0] = p[0] + 0b10000000;
	p[1] = i & 0b11111000000;
	p[1] = p[1] >> 6;
	p[1] = p[1] + 0b11000000;
	if (!(str = ft_memalloc(3)))
		return (NULL);
	str[0] = p[1];
	str[1] = p[0];
	return (str);
}

static char		*pf_triple_char(int i)
{
	int		p[3];
	char	*str;

	p[0] = (i & 0b111111) + 0b10000000;
	p[1] = ((i & 0b111111000000) >> 6) + 0b10000000;
	p[2] = ((i & 0b1111000000000000) >> 12) + 0b11100000;
	if (!(str = ft_memalloc(4)))
		return (NULL);
	str[0] = p[2];
	str[1] = p[1];
	str[2] = p[0];
	return (str);
}

static char		*pf_quad_char(int i)
{
	int		p[4];
	char	*str;

	p[0] = (i & 0b111111) + 0b10000000;
	p[1] = ((i & 0b111111000000) >> 6) + 0b10000000;
	p[2] = ((i & 0b111111000000000000) >> 12) + 0b10000000;
	p[3] = ((i & 0b111000000000000000000) >> 18) + 0b11110000;
	if (!(str = ft_memalloc(sizeof(char) * 5)))
		return (NULL);
	str[0] = p[3];
	str[1] = p[2];
	str[2] = p[1];
	str[3] = p[0];
	return (str);
}

char			*pf_unicode(unsigned int i)
{
	char	*str;

	if (MB_CUR_MAX == 4)
	{
		if (i <= 0x7f)
			return (pf_simple_char(i));
		else if (i <= 0x7ff)
			return (pf_double_char(i));
		else if (0xd800 <= i && i <= 0xdfff)
			return (NULL);
		else if (i <= 0xffff)
			return (pf_triple_char(i));
		else if (i <= 0x10ffff)
			return (pf_quad_char(i));
		return (NULL);
	}
	else if (i > 0xff)
		return (NULL);
	if (!(str = ft_memalloc(2)))
		return (NULL);
	*str = i;
	return (str);
}
