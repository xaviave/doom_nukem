# Doom_nukem

## Introduction

> Doom Nukem is a game created by @mel-akio and me (@xamartin) who is an Doom and Duke Nukem inspired.
We've recreate our own 3D engine ( jk ) who use the raycasting tech like the one of Duke Nukem. 

## Code Samples

>  Our map generator is simple to use and do everything you want but if you really want to do your own map from scratch, here a diy to do this map                            
 (https://github.com/xaviave/doom_nukem/blob/master/data/test.dk) :

First you have to put on paper the grid of the rooms of the map, in this case there are nine points arranged as it is:

1 2 3
4 5 6
7 8 9

it is important to arrange them from left to right and then from top to bottom.

To write these points in .dk format, follow this example:
v 0 0;1 5;2 10;3
v 5 0;4 5;5 10;6
v 10 0;7 5;8 10;9

v to indicate that it is a vertex line (one dot).
0 indicates the y-position of this point.
0;1 indicates the x position of the point, then its index in the list of points.
5;2 and 10;3 also.
...

Then you have to connect all these points to get the linedef.
A linedef is a plot between two points, which will determine the space between these two points.
It can be a wall, or an invisible linedef to cross it as if it were a void.
...

In this example, I've listed the linedef as such:

l 1 1 2 12
l 2 2 3 2
l 3 3 6 1
l 4 2 5 0
l 5 1 4 1
l 6 4 5 0
l 7 5 6 0
l 8 6 9 1
l 9 5 8 0
l 10 4 7 1
l 11 7 8 1
l 12 8 9 1

l to indicate that it is a linedef.
1 to indicate its index in the list of linedef.
1 2 to indicate the two points composing this linedef, in this case, linedef number 1 is between vertex 1 and vertex 2.
And the last number (12) indicates the texture of the linedef (for example: 0 for transparent, which can be crossed).

It is now necessary to inform the sectors, which will determine the different areas of the map.
In my case, I will create 4 zones to have 4 squares in my 3x3 grid:

s 1 0 12 1 4 6 5
s 2 0 12 2 3 7 4
s 3 0 12 6 9 11 10
s 4 0 12 7 8 12 9

s indicates that it is a sector.
1 indicates the index of this sector in the list of sectors.
0 indicates the height (z-position) of the floor of the sector.
12 indicates the ceiling height.
1 4 6 5 indicates the outline of this sector in this way:
a sector must be convex,
have a minimum of 3 walls (you cannot create a room with two walls),
In order to determine what its walls will be, we indicate, as in the example, the indexes of the linedef with which we want to create the sector.
These linedef must be indicated, in relation to their position on the map. (it is strongly advised to draw the map on paper in order to better visualize the position of its elements).
IMPORTANT: The lines must be run (to indicate) clockwise through the linedef.

In this example, sector 1 is equivalent to connecting vertex 1 2 5 4 (starting at the top left of the map, then clockwise).
So linedef 1, (since linedef 1 = vertex 1 + vertex 2), linedef 4 (v2, v5), linedef 6 (v5, v4), and linedef 5 (v4, v1) represent the contours of sector 1.


The draw on paper of the map:

v1 ---l1--- v2 ---l2--- v3
|           |           |
l5    s1    l4    s2    l3
|           |           |
v4 ---l6--- v5 ---l7--- v6
|           |           |
l10   s3    l9    s4    l8
|           |           |
v7 ---l11-- v8 ---l12-- v9



ENJOY ! (Go see map.dk for a fully functionnal map)

## Installation

> To play the game, test the engine or just create a map, clone the repo then make and tap ./doom_nukem for the game, ./engine and ./map_generator
