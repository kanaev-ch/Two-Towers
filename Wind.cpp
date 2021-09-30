#include "Wind.h"



Wind::Wind()
	:period(0), wind_speed(0)
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
	if (period > 50000) period = 0;//reset period if more than 50000

	if (!period) 
		wind_speed = (static_cast<float>(rand() % 300) - 150) / 100;//when reset period update by rand wind speed

	for (int i = 0; i < sizeof(snowflake) / sizeof(sf::CircleShape); i++)//cycle update coord of snowflakes
	{
		snowflakeX[i] += wind_speed;//update coord by X from wind wpeed
		snowflakeY[i] += 0.05F * time_;//update coord by Y, fall down snowflakes

		if (snowflakeY[i] > H_by_TILES * 32 - 4 * 32 - 3)//reset coords to top of screen if fall to ground
		{
			snowflakeX[i] = static_cast<float>(rand() % ((32 * W_by_TILES) + 2000)) - 1000;//rand by X
			snowflakeY[i] = 0;//by Y top of screen
		}
	}
	std::cout << period << " " << wind_speed << std::endl;
}

void Wind::DRAW_SNOWFLAKES(sf::RenderWindow& window_)
{
	for (int i = 0; i < sizeof(snowflake) / sizeof(sf::CircleShape); i++)
	{
		snowflake[i].setPosition(snowflakeX[i] - offsetX, snowflakeY[i]);//set current position with offset for scrolling
		window_.draw(snowflake[i]);
	}
}