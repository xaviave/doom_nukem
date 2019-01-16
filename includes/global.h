/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   global.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 14:44:33 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 16:36:20 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdio.h>
# include <stdlib.h>
# include "fcntl.h"
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include "../libft/header/libft.h"

/*
** Structures & Binary tree
*/

typedef struct			s_vertex
{
	int					x;
	int					y;
	int					id;
}						t_vertex;

typedef struct			s_coord
{
	int					x1;
	int					y1;
	int					x2;
	int					y2;
}						t_coord;

typedef struct			s_player
{
	int					x;
	int					y;
	int					vx;
	int					vy;
	float				angle;
	int					keys_shortcuts[256];
	int					keyspressed;
}						t_player;

typedef struct			s_sidedef
{
	int					*text;
	int					*heigth;
	int					nb_text;
}						t_sidedef;

typedef struct			s_linedef
{
	int					id;
	t_sidedef			side;
	int					id_v1;
	int					id_v2;
	int					nb_neigboors;
}						t_linedef;

typedef struct			s_sector
{
	int					id;
	int					h_floor;
	int					h_ceil;
	int					tex_floor; // no initialise
	int					tex_ceil; // no initialise
	int					nb_vertex;
	int					nb_linedef;
	int					*linedef;
	int					nb_neighbors;
	int					*neighbors;
}						t_sector;

typedef struct			s_level
{
	int					nb_vertex;
	t_vertex			*vertex;
	int					nb_linedef;
	t_linedef			*linedef;
	int					nb_sector;
	t_sector			*sector;
	t_player			player;
	struct s_level		*next;
}						t_level;

/*
** keyboard touch value
*/

# define MOUSE_ZOOM_IN 5
# define MOUSE_ZOOM_OUT 4
# define TOUCH_1 18
# define TOUCH_2 19
# define TOUCH_3 20
# define TOUCH_4 21
# define TOUCH_5 23
# define TOUCH_6 22
# define TOUCH_7 26
# define TOUCH_8 28
# define TOUCH_9 25
# define TOUCH_0 29
# define TOUCH_Q 12
# define TOUCH_W 13
# define TOUCH_E 14
# define TOUCH_R 15
# define TOUCH_T 17
# define TOUCH_Y 16
# define TOUCH_A 0
# define TOUCH_S 1
# define TOUCH_D 2
# define TOUCH_F 3
# define TOUCH_G 5
# define TOUCH_Z 6
# define TOUCH_X 7
# define TOUCH_C 8
# define TOUCH_V 9
# define TOUCH_B 11
# define TOUCH_ECHAP 53
# define TOUCH_ENTER 36
# define TOUCH_LEFT 123
# define TOUCH_RIGHT 124
# define TOUCH_DOWN 125
# define TOUCH_UP 126
# define TOUCH_NUMPAD_0 82
# define TOUCH_NUMPAD_1 83
# define TOUCH_NUMPAD_2 84
# define TOUCH_NUMPAD_3 85
# define TOUCH_NUMPAD_4 86
# define TOUCH_NUMPAD_5 87
# define TOUCH_NUMPAD_6 88
# define TOUCH_NUMPAD_7 89
# define TOUCH_NUMPAD_8 91
# define TOUCH_NUMPAD_9 92
# define TOUCH_NUMPAD_POINT 65
# define TOUCH_NUMPAD_ENTER 76
# define TOUCH_NUMPAD_PLUS 69
# define TOUCH_NUMPAD_LESS 78
# define TOUCH_NUMPAD_TIMES 67
# define TOUCH_NUMPAD_DIVIDE 75
# define TOUCH_NUMPAD_NUM 71
# define TOUCH_NUMPAD_INSERT 114
# define TOUCH_NUMPAD_END 119
# define TOUCH_NUMPAD_DELL 117
# define TOUCH_NUMPAD_PAGEUP 116
# define TOUCH_NUMPAD_PAGEDOWN 121
# define TOUCH_NUMPAD_HOME 115
# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6

// Define of actions

# define MOVE_UP (1 << 0)
# define MOVE_DOWN (1 << 1)
# define MOVE_LEFT (1 << 2)
# define MOVE_RIGHT (1 << 3)
# define ROTATE_LEFT (1 << 4)
# define ROTATE_RIGHT (1 << 5)
# define EXIT_GAME (1 << 6)
# define ZOOM_IN (1 << 7)
# define ZOOM_OUT (1 << 8)

#endif
