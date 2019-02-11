# Doom_nukem

## Introduction

> Doom Nukem is a game created by @cmerel, @flombard, @mel-akio and me (@xamartin) who is an Doom and Duke Nukem inspired.
We've recreate our own 3D engine ( jk ) who use the raycasting tech like the one of Duke Nukem. 

## Code Samples

>  Our map generator is simple to use and do everything you want but if you really want to do your own map from scratch, here a diy to do this map                            
 (https://github.com/xaviave/doom_nukem/blob/master/test.dk) :

create all your point one by one on a paper an numbered them from the left to the right and from the top to the bottom (0 for the empty space)  :

1-----2-----3   
|0000|0000|   
4-----5-----6   
|0000|0000|      
7-----8-----9  

Then when you got this create your line which begin with a 'v' for vertex, the point Y axe for all the points then reference the x follow by a semi-colon ';' an the id of the point like this : 

v 0 0;1 5;2 10;3   
v 5 0;4 5;5 10;6    
v 10 0;7 5;8 10;9

for the linedef, define the linedef's id then define it with the 2 points' ids who are on the side of the linedef and then the sprite define by the id of the sprite follow by a semi-colon the bottom height of the sprite (know that the first doesn't need the bottom number because it begin with sector floor height) also, it begins with a 'l' (0 define transparent wall wich could be cross):

l 1 1 2 12   
...   
l 5 2 5  0   
...    
l  8 9 1 4;19

 then for the sector, put a 's' at the beginning, the id of the sector, the height of the floor and the ceiling and the list of the linedef's id who define the sector, so :

s 1 0 20 1 2 3 4 6 .    
...    
s  4 10 25 7 9 10 12

ENJOY !

## Installation

> To play the game, test the engine or just create a map, clone the repo then make and tap ./doom_nukem for the game, ./engine and ./map_generator
