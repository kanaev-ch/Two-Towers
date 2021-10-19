#include "Wind.h"



Wind::Wind()
	:period(0), /*wind_speed(0)*/ wind_speed(.0f)//wind_speed -0.03f <-> 0.03f
{
	for (int i = 0; i < sizeof(snowflake) / sizeof(sf::CircleShape); i++)//init start parameters of snowflakes
	{
		snowflake[i].setRadius(3.f);
		snowflake[i].setFillColor(sf::Color::White);
//		snowflake[i].setPosition(static_cast<float>(rand() % 32 * W_by_TILES), static_cast<float>(rand() % H_int));
		snowflakeX[i] = static_cast<float>(rand() % ((32 * W_by_TILES) + 2000)) - 1000;//init rand coord by X, 2000 and 1000 needs for drawing fare then edges of screen
		snowflakeY[i] = static_cast<float>(rand() % H_int);////init rand coord by Y
	}
}


Wind::~Wind()
{
}

float Wind::WIND_SPEED()const
{
	return wind_speed;
}

void Wind::SET_WIND_AND_MOVE_SNOWFLAKES(float time_)//func of move and draw snowflakes
{
	period += time_;//every time increase period
	if (period > 20000) period = 0;//reset period if more than 20000, its time for change direction of wind

	if (!period) 
		wind_speed = (static_cast<float>(rand() % 400) - 200) / 10000;//when reset period, update by rand wind speed, wind_speed -0.03f <-> 0.03f

	for (int i = 0; i < sizeof(snowflake) / sizeof(sf::CircleShape); i++)//cycle update coord of snowflakes
	{
//		snowflakeX[i] += wind_speed * 100;//update coord by X from wind speed
		snowflakeX[i] += wind_speed * 10 * time_;//update coord by X from wind speed
		snowflakeY[i] += 0.05F * time_;//update coord by Y, fall down snowflakes

		if (snowflakeY[i] > H_by_TILES * 32 - 4 * 32 - 3)//reset coords to top of screen if fall to ground
		{
			snowflakeX[i] = static_cast<float>(rand() % ((32 * W_by_TILES) + 2000)) - 1000;//rand by X
			snowflakeY[i] = 0;//by Y top of screen
		}
	}
//	std::cout << period << " " << wind_speed << std::endl;
}

void Wind::DRAW_SNOWFLAKES(sf::RenderWindow& window_)
{
	for (int i = 0; i < sizeof(snowflake) / sizeof(sf::CircleShape); i++)
	{
		snowflake[i].setPosition(snowflakeX[i] - offsetX, snowflakeY[i]);//set current position with offset for scrolling
		window_.draw(snowflake[i]);
	}
}