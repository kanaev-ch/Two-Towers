#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Fortress.h"
#include "Fortress_Enemy.h"
#include "Unit.h"

class Infantry
{
private:
//	std::vector <Unit> squad;

	sf::Texture texture;//lead texture

	float timer_born_unit;//timar when units upload an map
public:
	std::vector <Unit> squad;//dynamic arr vector for units

	Infantry();
	~Infantry();

	void BORN_UNIT(float);
	void DEATH_UNIT();

	void UPDATE_FRAME(float);

	void COLLISION(Fortress&, Fortress_Enemy&, float);

	void MOVE(float);

	void DRAW(sf::RenderWindow&);
};

