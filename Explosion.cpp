#include "Explosion.h"



Explosion::Explosion()
	:x_explode(0), y_explode(0), explode_live(false), explode_currentFrame(0)//start params for explosion
{
	texture_explode.loadFromFile("Explosion.png");
	sprite_explode.setTexture(texture_explode);
}


Explosion::~Explosion()
{
}

void Explosion::X_EXPLODE(float x_)
{
	x_explode = x_;
}

bool Explosion::X_EXPLODE()const
{
	return x_explode;
}

void Explosion::Y_EXPLODE(float y_)
{
	y_explode = y_;
}

bool Explosion::Y_EXPLODE()const
{
	return y_explode;
}

void Explosion::EXPLODE_LIVE(bool l_)
{
	explode_live = l_;
}

bool Explosion::EXPLODE_LIVE()const
{
	return explode_live;
}

void Explosion::EXPLODE_CHANGE_FRAMES(float time_)//func of change frames of explode
{
	explode_currentFrame += .004f * time_;//speed of changing anime frames
	if (explode_currentFrame > 12)//STOP anime, there are 12 frames in sprite sheet
	{
		explode_currentFrame = 0;//reset start frame
		explode_live = false;//not draw explode frames
	}
	sprite_explode.setTextureRect(sf::IntRect(32 * static_cast<int>(explode_currentFrame), 0, 32, 32));//changing frames of explode
	sprite_explode.setPosition(x_explode, y_explode);//every time set position of explode
}

void Explosion::EXPLODE_DRAW_FRAME(sf::RenderWindow& window_)
{
	window_.draw(sprite_explode);
}