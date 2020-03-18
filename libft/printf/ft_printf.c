/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:08 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:08 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

int		ft_printf(const char *format, ...)
{
	va_list			ap;
	int				len;
	int				tmp_len[2];
	char			*str;

	va_start(ap, format);
	len = 0;
	if (!(str = (char*)ft_memalloc(1)))
		return (-1);
	while (*format)
	{
		tmp_len[0] = pf_str((char**)&format, &str, len);
		if (tmp_len[0] == -1)
			break ;
		tmp_len[1] = pf_special((char**)&format, ap, &str, len + tmp_len[0]);
		if (tmp_len[1] == -1)
			break ;
		len += tmp_len[0] + tmp_len[1];
	}
	if (len)
		write(1, str, len);
	str ? free(str) : 0;
	va_end(ap);
	return (tmp_len[0] == -1 || tmp_len[1] == -1 ? -1 : len);
}
