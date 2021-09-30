#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data.h"

class Wind
{
private:
	sf::CircleShape snowflake[100];//arr of snowflakes

	float snowflakeX[100];//cord of each snowflake by X
	float snowflakeY[100];//cord of each snowflake by Y

	float period;//period of time when wind is changing
	float wind_speed;//current speed of wind
public:
	Wind();
	~Wind();

	float WIND_SPEED()const;

	void SET_WIND_AND_MOVE_SNOWFLAKES(float);

	void DRAW_SNOWFLAKES(sf::RenderWindow&);
};

