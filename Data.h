#pragma once
#include <SFML/Graphics.hpp>

extern const int W_int;//width of game screen, map can be much more tiles over screen
extern const int H_int;//height of game screen, map can be much more tiles over screen
extern const float W_float;//width of game screen, map can be much more tiles over screen
extern const float H_float;//height of game screen, map can be much more tiles over screen

extern const int H_by_TILES;//num of tiles of height (32x32) in map
extern const int W_by_TILES;//num of tiles of height (32x32) in map

extern float offsetX;//offset by X fo scrolling picture (map, and other static objects)

extern int end_game_flag;//Flag of winning, if 1 WE, if 2 ENEMY

extern bool enemy_fire_near_fort;//flag of don't enemy fire near OUR fort, because frendly fire

extern float time_for_melee;//var for one time melee sound, timer of it

//extern sf::String MAP[];