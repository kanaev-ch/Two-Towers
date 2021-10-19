#pragma once
#define SFML_NO_DEPRECATED_WARNINGS

#include <SFML/Graphics.hpp>
#include "Data.h"

class End_Game_Text
{
private:
	sf::String win_string;
	sf::String enemy_win_string;

	sf::Font font;

	sf::Text win_text;
	sf::Text enemy_win_text;
public:
	End_Game_Text();
	~End_Game_Text();

	void DRAW(sf::RenderWindow &)const;
};

