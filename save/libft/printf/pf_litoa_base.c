/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_litoa_base.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:09 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:09 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

static long		ft_len_n(long n, int len_base)
{
	int		len;

	len = (n >= 0 ? 1 : 2);
	n = (n >= 0 ? n : -n);
	while (n >= len_base)
	{
		n /= len_base;
		len++;
	}
	return (len);
}

char			*pf_litoa_base(long n, char *base)
{
	char	*str;
	int		i;
	int		len;
	int		len_base;

	len_base = ft_strlen(base);
	if (len_base != 10)
		return (pf_luitoa_base(n, base));
	if ((unsigned long)n == 0x8000000000000000)
		return (ft_strdup("-9223372036854775808"));
	len = ft_len_n(n, len_base);
	if (!(str = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[0] = '-';
	n = (n > 0 ? n : -n);
	i = len - 1;
	while (n >= len_base)
	{
		str[i--] = base[n % len_base];
		n /= len_base;
	}
	str[i] = base[n];
	return (str);
}
