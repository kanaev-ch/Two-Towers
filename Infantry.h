#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Fortress.h"
#include "Fortress_Enemy.h"
#include "Unit.h"
#include "Unit_Enemy.h"
#include "Data.h"

class Infantry
{
private:
//	std::vector <Unit> squad;

	sf::Texture texture;//load texture
	sf::Texture texture_enemy;//load texture

	float timer_born_unit;//timar when units upload an map
	float timer_born_unit_enemy;//timar when units upload an map

	//Block of sound
	sf::SoundBuffer sword_fight_buffer;//buffer sound of sword fight
	sf::Sound sword_fight_sound;//sound of sword fight

public:
	std::vector <Unit> squad;//dynamic arr vector for units
	std::vector <Unit_Enemy> squad_enemy;//dynamic arr vector for units

	Infantry();
	~Infantry();

	void BORN_UNIT(float);
	void DEATH_UNIT();

	void UPDATE_FRAME(float);

	int MELEE(float);

	void COLLISION(Fortress&, Fortress_Enemy&, float);

	void MOVE(float);

	int DONT_ENEMY_FIRE_NEAR_FORT();

	void DRAW(sf::RenderWindow&);
};

