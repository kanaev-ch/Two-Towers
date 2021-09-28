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
	sf::String building_string[5] = {
		"OPOPOPO",
		"OkOkOkO",
		"OKOKOKO",
		"TYiYiYt",
		"CWwwwWc"
	};
	float x_building_left_corner;//left top corner coordinates of fort building rectangle string
	float y_building_top_corner;//left top corner coordinates of fort building rectangle string

	Building();
	~Building();

	void DRAW_BUILDING(sf::RenderWindow&, float);
};

