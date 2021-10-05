#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Building
{
private:
/*	sf::String building[3] = {
		"WWW",
		"WWW",
		"WWW"
	};*/
//	float x_building_left_corner;
//	float y_building_top_corner;

	sf::Texture texture;
	sf::Sprite sprite;
public:
	int fortress_life;//lifes of fort building
	sf::String building_string[5] = {
		"OPOPOPO",
		"OkOkOkO",
		"OKOKOKO",
		"TYiYiYt",
		"CWwwwWc"
	};

	//arr of lifes of each block of building
	int building_tile_lifes_arr[5][7] = {
		{3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3}
	};

	float x_building_left_corner;//left top corner coordinates of fort building rectangle string, initializing in Fortress::Fortress
	float y_building_top_corner;//left top corner coordinates of fort building rectangle string, initializing in Fortress::Fortress

	Building();
	~Building();

	void GRAVITY_BLOCKS();

	void DRAW_BUILDING(sf::RenderWindow&, float);
};

