/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 16:03:34 by xamartin     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/05 10:18:33 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

/* Define window size */

#define W 1000
#define H 789

/* Define various vision related constants */

#define EyeHeight  6    // Camera height from floor when standing
#define DuckHeight 2.5  // And when crouching
#define HeadMargin 1    // How much room there is above camera before the head hits the ceiling
#define KneeHeight 2    // How tall obstacles the player can simply walk over without jumping
#define hfov (0.73f*H)  // Affects the horizontal field of vision
#define vfov (.2f*H)    // Affects the vertical field of vision
#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1)) // Overlap:  Determine whether the two number ranges overlap.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3)) // IntersectBox: Determine whether two 2D-boxes intersect.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0)) // PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct s_xy) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) }) // Intersect: Calculate the point of intersection between two lines.
#define Yaw(y,z) (y + z*player.yaw)


static SDL_Surface* surface = NULL;

/*
** Struct & functs
*/

typedef struct		s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef struct		s_xyz
{
	float			x;
	float			y;
	float			z;
}					t_xyz;

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */

static struct		sector
{	
    float			floor;
	float			ceil;
    struct s_xy		*vertex; // Each vertex has an x and y coordinate
    signed char		*neighbors;           // Each edge may have a corresponding neighboring sector
    unsigned		npoints;                 // How many vertexes there are
}					*sectors = NULL;

/* Player: location */

static struct		player
{
    struct s_xyz	where;      // Current position
    struct s_xyz	velocity;   // Current motion vector
    float 			angle, anglesin, anglecos, yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned		sector;                        // Which sector the player is currently in
}					player;

void	load_data(unsigned int *NumSectors);

void	draw_screen(unsigned int *NumSectors);

void	unload_data(unsigned int *NumSectors);

void	vline(int x, int y1, int y2, int top, int middle, int bottom);

void	move_player(float dx, float dy);

#endif