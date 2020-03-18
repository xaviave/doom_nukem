/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_graph.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/08 15:06:44 by flombard     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 15:32:35 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	render_error(int error, t_level *level)
{
	if (error == 10)
		ft_printf("Error 10 : SDL initialisation didn't work\n");
	else if (error == 11)
		ft_printf("Error 11 : Window couldn't be created\n");
	else if (error == 12)
		ft_printf("Error 12 : Renderer couldn't be created\n");
	free_level(level);
	exit(EXIT_FAILURE);
}
