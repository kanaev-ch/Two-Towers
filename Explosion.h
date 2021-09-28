#pragma once
#include <SFML/Graphics.hpp>
#include "Data.h"

class Explosion
{
private:
	sf::Texture texture_explode;//texture of explode
	sf::Sprite sprite_explode;//sprite of explode
	float x_explode;//coords of explode by X
	float y_explode;//coords of explode by Y
	bool explode_live;//Flag of exlode live
	float explode_currentFrame;//current frame for animetion
public:
	Explosion();
	~Explosion();

	void X_EXPLODE(float);
	bool X_EXPLODE()const;
	void Y_EXPLODE(float);
	bool Y_EXPLODE()const;

	void EXPLODE_LIVE(bool);
	bool EXPLODE_LIVE()const;

	void EXPLODE_CHANGE_FRAMES(float);
	void EXPLODE_DRAW_FRAME(sf::RenderWindow&);
};

