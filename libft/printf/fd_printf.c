/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fd_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lotoussa <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/21 19:15:13 by lotoussa     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/21 19:15:14 by lotoussa    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

int		fd_printf(const char *format, ...)
{
	va_list			ap;
	int				len;
	int				tmp_len[2];
	char			*str;
	int				fd;

	va_start(ap, format);
	len = 0;
	fd = va_arg(ap, int);
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
	len ? write(fd, str, len) : 0;
	str ? free(str) : 0;
	va_end(ap);
	return (tmp_len[0] == -1 || tmp_len[1] == -1 ? -1 : len);
}
