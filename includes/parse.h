/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 14:42:52 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 17:24:12 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "global.h"

/*
**	Parsing functions & Stucture
*/

typedef struct			s_pvertex
{
	int					x;
	int					y;
	int					id;
	struct s_pvertex	*next;
}						t_pvertex;

typedef struct			s_plinedef
{
	int					id;
	int					*text;
	int					*heigth;
	int					nb_text;
	int					id_v1;
	int					id_v2;
	struct s_plinedef	*next;
}						t_plinedef;

typedef struct			s_psector
{
	int					id;
	int					ceiling;
	int					ground;
	int					tex_ground; // no initialise
	int					tex_ceil; // no initialise
	int					*linedef;
	int					nb_linedef;
	int					nb_vertex;
	struct s_psector	*next;
}						t_psector;

typedef struct			s_parse
{
	t_pvertex			*vertex;
	t_plinedef			*linedef;
	t_psector			*sector;
	t_player			player;
	int					nb;
}						t_parse;

void					parse_map(int aac, char **av, t_parse *parse);
void					parse_vertex(t_parse *parse, char *str);
void					parse_linedef(t_parse *parse, char *str);
void					parse_sector(t_parse *parse, char *str);

/*
**	Parse info to level structure
*/

void					parse_to_level(t_parse *parse, t_level *level);
void					p_to_vertex(t_level *level, t_parse *parse);
void					p_to_linedef(t_level *level, t_parse *parse);
void					p_to_sector(t_level *level, t_parse *parse);

/*
**	Error case & free
*/

void					free_parse(t_parse *parse);
void					free_level(t_level *level);
void					return_error(int error, t_parse *parse);

void					aff_debug(t_level *level);

#endif
