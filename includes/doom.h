/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 16:03:34 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 01:42:02 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "tools.h"
# include "../minilibx_macos/mlx.h"

/*
** Test graphique
*/

# define W 1280
# define H 800

typedef struct			s_line
{
	int					dx;
	int					sx;
	int					dy;
	int					sy;
	int					err;
	int					e2;
}						t_line;

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned char		a;
	int					i;
}						t_color;

typedef struct			s_win
{
	void				*win_ptr;
	int					width;
	int					height;
}						t_win;

typedef struct			s_img
{
	void				*ptr;
	char				*data;
	int					sizeline;
	int					bpp;
	int					endian;
	int					w;
	int					h;
}						t_img;

typedef struct			s_hud
{
	t_img				hp;
	t_img				ammo;
	int					x_hp;
	int					y_hp;
	int					x_ammo;
	int					y_ammo;
	int					x_str_hp;
	int					y_str_hp;
	int					x_str_ammo;
	int					y_str_ammo;
	int					x_str_magazine;
	int					y_str_magazine;
	char				*str_ammo;
	char				*str_hp;
	char				*str_magazine;
}						t_hud;

typedef struct			s_vector
{
	float				tx1;
	float				tx2;
	float				ty1;
	float				ty2;
	float				tz1;
	float				tz2;
	float				iz1;
	float				ix1;
	float				iz2;
	float				ix2;
	float				mx;
	float				my;
	float				mz1;
	float				mx1;
}						t_vector;

typedef struct			s_mem
{
	int					first_launch;
	int					end;
	t_win				win;
	t_img				img;
	t_color				color;
	void				*mlx_ptr;
	t_coord				coord;
	t_level				*level;
	t_hud				hud;
	t_coord				step_bot;
	t_img				gun;
	t_img				crosshair;
	t_img				skybox;
	t_img				monster;
	t_img				shooting_monster;
	t_img				hp_box;
	t_img				wall;
	t_img				ammo_box;
	float				cos_angle;
	float				sin_angle;
	int					fps;
	unsigned int		colorize;
	struct timeval		tv1;
	struct timeval		tv2;
	struct timeval		ai1;
	struct timeval		ai2;
	t_line				line;
	t_line				line2;
	t_line				line3;
	t_line				line4;
	t_coord				p3;
	t_coord				p4;
	t_coord				p5;
	t_fcoord			p1;
	t_fcoord			p2;
	t_fcoord			step;
	t_fcoord			top;
	float				z;
	int					x;
	int					y;
	char				*fill_screen;
	int					mouse_x;
	int					mouse_y;
	int					camera_x;
	int					camera_y;
	int					neighbour;
	float				tex_x;
	float				tex_y;
	float				step_x;
	float				step_y;
	float				min_x;
	float				min_y;
	float				max_x;
	float				max_y;
	float				h_wall;
	float				l_wall;
}						t_mem;

void					ft_create_img(t_mem *mem);
void					ft_put_pixel(t_mem *mem, int x, int y, t_color color);
t_color					get_color(int a, t_mem *mem);
void					render_map(t_mem *mem, int sect);
void					render_sprites(t_mem *mem, int sect);
void					draw_line(t_mem *mem);
void					draw_to_line(t_coord *coord, t_mem *mem);
void					fill_column(int x, int sect, t_mem *mem);
void					draw_camera(t_mem *mem);
void					draw_minimap(t_mem *mem);
void					draw_square(t_mem *mem);
void					refresh_screen(t_mem *mem);
void					event_loop(t_mem *mem);
void					change_color(t_color *color, int hex);
t_color					set_color(int a);
void					make_mask(t_mem *mem, t_img *img, char xpm[255]);

/*
** event.c
*/

int						camera_move(t_mem *mem);
int						update_keys(t_mem *mem);

/*
** event2.c
*/

int						mouse_move_hook(int x, int y, t_mem *mem);
int						mouse_click_hook(int k, int x, int y, t_mem *mem);
int						add_key(int k, t_mem *mem);
int						remove_key(int k, t_mem *mem);
int						cross_close(t_mem *mem);

/*
** send_info -------------- dir
*/

typedef struct			s_inside
{
	double				s1;
	double				s2;
	double				s3;
	double				s4;
	double				w1;
	double				w2;
}						t_inside;

/*
** send_coords.c
*/

void					send_x(t_coord *coord, t_mem *mem, int l);
void					send_y(t_coord *coord, t_mem *mem, int l);
int						send_vx(t_level *level, int id);
int						send_vy(t_level *level, int id);

/*
** send_linedef_coords.c
*/

int						send_l_vx(t_level *level, int id_l, int vertex);
int						send_l_vy(t_level *level, int id_l, int vertex);

/*
** send_ids.c
*/

int						send_l_id(t_mem *mem, int id);
int						send_v_id(t_mem *mem, int id);
int						send_s_id(t_mem *mem, int id);

/*
** sector_infos.c
*/

int						next_sector(t_mem *mem, int linedef_id,
	int actual_sector);
void					fill_n_sector(t_mem *mem, int i);

/*
** mob_infos.c
*/

void					sort_dist_monsters(t_mem *mem);
void					entity_sector(t_mem *mem);

/*
** triangulation_player.c
*/

int						check_in_sector(t_mem *mem, int l1, int l2, int save);
int						is_inside(t_vertex v1, t_vertex v2,
	t_vertex v3, t_vertex m);
int						in_box(t_mem *mem, int nb);

/*
** math.c
*/

int						return_min(int x1, int x2);
void					intersect(t_vector vec, float *x, float *y);
void					intersect_down(t_vector vec, float *x, float *y);
int						fn_cross(float x1, float y1, float x2, float y2);
int						player_sector(t_mem *mem, int prev);
void					physics(t_mem *mem);
void					jump(t_mem *mem);
void					player_animation(t_mem *mem);
float					distance(float x1, float y1, float x2, float y2);

/*
** get infos
*/

int						further_sector(t_mem *mem, int sector);

/*
** render calc
*/

t_vector				calc_vec(t_vector vec);
void					calc_linedef_one(t_render *coor, t_mem *mem);
void					calc_linedef_two(t_render *coor, t_mem *mem);
t_vector				calc_wall(t_mem *mem, t_vector vec, int sect, int j);
void					calc_minimap(t_mem *mem, int i, int j, t_vector *vec);
void					calc_linedef(t_fcoord pf1, t_mem *mem);
t_vector				pre_calc_vec(t_vector vec);
void					set_column(t_render coor, t_mem *mem);
int						pre_render(t_mem *mem, int sect, int i);
int						further_sector(t_mem *mem, int sector);
void					shoot(t_mem *mem, char frame);
void					draw_minimap(t_mem *mem);
t_line					line_init(t_fcoord p);
void					paint_linedef(t_render coor, int sect, t_mem *mem);
void					render_calc(t_render *coor, t_vector *vec,
	t_mem *mem, int sect);

/*
** textures process
*/

void					textures_init(t_mem *mem);
void					put_img_to_img(t_mem *mem, t_img *img,
		t_vector coor, float zoom);
void					skybox(t_mem *mem, t_img *img);
unsigned int			rgb(unsigned char o, unsigned char r,
unsigned char g, unsigned char b);
void					set_wall_size(t_mem *mem, t_render coor);
void					set_wall_infos(t_mem *mem);
void					draw_objects(t_mem *mem, t_vector coor,
		float zoom, int k);

/*
** animation
*/

void					shoot(t_mem *mem, char frame);
void					process(t_mem *mem);

/*
** music free
*/

void					init_sound(t_mem *mem);
void					play_music(t_audio m);
void					play_audio(t_audio m);
void					free_audio(t_mem *mem);
void					free_mem(t_mem *mem);

/*
** hud
*/

void					init_hud(t_mem *mem);
void					set_hud(t_mem *mem);

/*
** ai
*/

void					ai_think(t_mem *mem);

/*
** player events
*/

void					on_shoot(t_mem *mem);
void					on_reload(t_mem *mem);
void					on_collision(t_mem *mem);
void					first_screen(t_mem *mem);
void					end_screen(t_mem *mem);
void					check_mobs(t_mem *mem);

#endif
