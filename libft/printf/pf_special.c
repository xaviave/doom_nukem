/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_special.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:13:10 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/28 18:13:10 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../header/libft.h"

int				pf_special(char **format, va_list ap, char **str, int len)
{
	t_flags		flags;

	if (!(**format))
		return (0);
	(*format)++;
	pf_flags(format, &flags);
	if (flags.type == 'p')
		return (pf_p(ap, &flags, str, len));
	else if (flags.type == '%')
		return (pf_percent(&flags, str, len));
	else if (flags.type == 's' || flags.type == 'S')
		return (pf_s(ap, &flags, str, len));
	else if (flags.type == 'c' || flags.type == 'C')
		return (pf_c(ap, &flags, str, len));
	else if (flags.type == 'u' || flags.type == 'U')
		return (pf_u(ap, &flags, str, len));
	else if (flags.type == 'd' || flags.type == 'i' || flags.type == 'D')
		return (pf_d(ap, &flags, str, len));
	else if (flags.type == 'x' || flags.type == 'X' || flags.type == 'O'
			|| flags.type == 'o')
		return (pf_base(ap, &flags, str, len));
	else
		return (pf_no(&flags, str, len, format));
}
