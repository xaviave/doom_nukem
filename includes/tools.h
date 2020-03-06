/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 17:02:03 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 18:20:14 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "parse.h"

int						check_int(char *tmp);
int						pass_digit_space(char *str);
int						pass_space_digit(char *str);
int						*copy_int(int *vertex, int nu);
int						count_int(char *str);
int						*create_vertex(char *str);
void					create_sidedef(t_sidedef *side, char *str);
void					add_list_v(t_pvertex **vertex, char *y,
	char *x, char *id);
void					add_list_l(t_plinedef **linedef, char *str);
void					add_list_s(t_psector **sector, char *str);
void					add_list_e(t_pentity **entity, char *str);
int						list_len_l(t_plinedef *list);
int						list_len_s(t_psector *list);
int						list_len_v(t_pvertex *list);
int						list_len_e(t_pentity *list);
void					print_bits(int n);
int						double_int(int *tab, int nu, int nb);

#endif
