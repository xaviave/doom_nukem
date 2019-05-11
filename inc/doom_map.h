/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom_map.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 19:44:01 by augberna     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/11 13:56:36 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _DOOM_MAP_H
# define _DOOM_MAP_H

# include "../lib/minilibx_macos/mlx.h"
# include "../lib/libft/inc/libft.h"
# include "../lib/libhook/inc/libhook.h"
# include "../lib/payload/inc/payload.h"
# include <stdint.h>
# include <math.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define RGBA(r,g,b,a)				(a << 24) | (r << 16) | (g << 8) | (b)

# define CLR_R						0x00FF0000
# define CLR_G						0x0000FF00
# define CLR_B						0x000000FF
# define CLR_A						0xFF000000

# define CLR_BG						0x00002B36
# define CLR_BG_S					0x00001E26
# define CLR_LAYER					0x00CB4B16
# define CLR_ENTITY					0x009A41F4
# define CLR_PLAYER					0x00F44182
# define CLR_SHADOW					0x006C71C4
# define CLR_VAR					0x00D33682
# define CLR_STR					0x002AA198
# define CLR_VERTEX					0x00A0E502
# define CLR_VERTEX_1				0x0041F450

# define WIDTH						1920
# define WIDTH_2					WIDTH*0.5
# define HEIGH						1080
# define HEIGH_2					HEIGH*0.5

# define G_SCALE					10
# define V_BOX						11
# define O_SKETCH					200

# define M_DEG						180.0/M_PI
# define M_RAD						M_PI/180.0

typedef enum
{
	L_EDIT = 1,
	L_VISUAL = 0,
	L_NO_DRAW = -1
}	t_mode;

typedef enum
{
	P_PLAYER = 1,
	P_ENTITY = 2
}	t_pipet;

typedef struct		s_vertex
{
	int				x;
	int				y;
}					t_vertex;

typedef struct		s_gui
{
	int				file;
	t_pipet			pipet;
	t_node			*iterator;
	t_payload		*layer;
}					t_gui;

typedef struct		s_shape
{
	int				floor;
	int				ceil;
	t_node			*iterator;
	t_payload		*vertex;
}					t_shape;

typedef struct		s_image
{
	void			*id;
	void			*win_id;
	void			*mlx_id;
	char			*data;
	int				bpp;
	int				size_l;
	int				endian;
	int				width;
	int				heigh;
}					t_image;

typedef struct		s_layer
{
	t_image			*img;
	t_vertex		*spawn;
	t_vertex		*v_tmp;
	t_shape			*s_tmp;
	t_node			*it_shape;
	t_payload		*shape;
	t_node			*it_entity;
	t_payload		*entity;
	t_mode			mode;
	int				pipet;
	int				scale;
}					t_layer;

typedef struct		s_window
{
	void			*id;
	int				width;
	int				heigh;
	char			*title;
	uint8_t			menu;
}					t_window;

typedef struct		s_framework
{
	void			*id;
	t_window		*win;
	double			frame;
}					t_framework;

typedef struct		s_engine
{
	t_framework		*mlx;
	t_gui			*gui;
	t_keyboard		*keyboard;
	t_mouse			*mouse;
	struct timeval	old;
	struct timeval	cur;
}					t_engine;

typedef struct		s_file
{
	int				v_id;
	int				s_id;
	int				l_id;
	t_node			*v;
	t_node			*s;
	t_node			*l;
	t_vertex		*v_cur;
	t_shape			*s_cur;
	t_layer			*l_cur;
}					t_file;

void				debug_display(t_engine *e);

void				event_refresh(t_engine *e);
void				event_visual(t_mouse *m, t_keyboard *k, t_layer *l);
void				event_gui_manage(t_framework *mlx, t_keyboard *k, t_gui *g);
void				event_gui_mode(t_keyboard *k, t_layer *l, t_gui *g);
void				event_pipet(t_layer *l, t_pipet e, int x, int y);

void				layer_destroy(t_layer *layer);
t_layer				*new_layer(t_image *img, t_mode m);
void				layer_add_entity(t_layer *l, t_vertex *e);
void				layer_init(t_layer *l, t_shape *s);

void				layer_draw(t_layer *layer);
t_shape				*layer_has_vertex(t_layer *layer, int x, int y);
void				layer_add(t_layer *l, t_shape *s);

void				gui_destroy(t_gui *gui);
t_gui				*new_gui(t_layer *background);
void				gui_add_layer(t_gui *gui, t_layer *layer);
void				gui_remove_layer(t_gui *gui);

void				gui_display(t_gui *gui);
void				gui_prev(t_gui *gui);
void				gui_next(t_gui *gui);

t_shape				*new_shape(t_vertex *vertex);
void				shape_destroy(t_shape *shape);

t_vertex			*shape_has_vertex(t_shape *s, int x, int y);
void				shape_add(t_shape *s, t_vertex *v);
void				shape_remove(t_shape *s);
void				shape_draw(t_shape *shape, t_image *img, int pipet);

t_vertex			*new_vertex(int x, int y);
void				vertex_destroy(t_vertex *v);
void				vertex_destroy_elem(void *content);
void				vertex_update(t_vertex *v, int x, int y);
void				vertex_draw(t_image *img, t_vertex *v, int pipet);

t_engine			*new_engine(void);
void				engine_destroy(t_engine *e);

int					destroy_window_hook(t_engine *engine);
void				window_destroy(t_window *win);
t_window			*new_window(void *mlx_id, int width, int heigh,
						char *title);
void				framework_destroy(t_framework *framework);
t_framework			*new_framework(void);

void				image_destroy(t_image *img);
t_image				*new_image(void *mlx_id, void *win_id,
					int width, int heigh);
void				image_attach(t_image *img, t_window *win);

void				image_clear(t_image *img);
void				image_pixel_put(t_image *img, int x, int y, int color);
void				image_fill(t_image *img, int color);
void				image_square(t_image *img, t_vertex *v, int color);
void				image_line(t_image *img, t_vertex *v1, t_vertex *v2, int c);

int					file_save(t_gui *g);
#endif
