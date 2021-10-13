#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data.h"

class Unit
{
private:
	float x, y;//coords of unit

//	sf::Texture texture;//texture load from outside
	sf::Sprite sprite;//sprite of unit

//	float currentFrame;

//	bool live;
//	bool frames_death;

//	bool fight;
	int y_on_sprite;//var for choose what coord on sprite choose for anime

public:
	bool fight;//flag of fight
//	bool live;//flag live or not
	int live;//num of lifes of unit
	float currentFrame;//var current frame for anime

	Unit(sf::Texture&, float, float);
	~Unit();

	float X()const;
	float Y()const;

	void UPDATE_FRAME(float);

	void MOVE(float);
//	void FIGHT(float, int&);
	bool FIGHT(float, int&);
	void DEATH();

	void DRAW(sf::RenderWindow&);
};

