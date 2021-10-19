#include "Unit_Enemy.h"



Unit_Enemy::Unit_Enemy(sf::Texture& texture, float x_, float y_)
//Unit_Enemy::Unit_Enemy(float x_, float y_)
	:currentFrame(0), live(1), x(x_), y(y_), y_on_sprite(32), fight(false), melee(false)
{
	texture.loadFromFile("orc.png");
	sprite.setTexture(texture);
}

Unit_Enemy::~Unit_Enemy()
{
}


float Unit_Enemy::X()const
{
	return x;
}

float Unit_Enemy::Y()const
{
	return y;
}


void Unit_Enemy::UPDATE_FRAME(float time_)//func for update frames
{
	if (!live)//for death
	{
		currentFrame += time_ * .005f;
		sprite.setTextureRect(sf::IntRect(32 * int(currentFrame) + 32, y_on_sprite, -32, 32));
		sprite.setPosition(x - offsetX, y);
	}

	if (live)//for live
//	if (live && !fight)//for live
	{
		currentFrame += time_ * .005f;
		if (currentFrame > 10) currentFrame = 0;
		sprite.setTextureRect(sf::IntRect(32 * int(currentFrame) + 32, y_on_sprite, -32, 32));
		sprite.setPosition(x - offsetX, y);
	}
}

void Unit_Enemy::MOVE(float time_)//func changing coords on sprite for walk
{
	if (live && !fight)//if live and not fighting
	{
		y_on_sprite = 32;// changing coords on sprite for walk
//		x -= time_ * .005f;
		x -= time_ * .01f;
//		x -= time_ * .05f;//moving forward
	}
}

//void Unit_Enemy::FIGHT(float time_, int& lifes_)//func for fight
bool Unit_Enemy::FIGHT(float time_, int& lifes_)//func for fight
{
	if (live && fight)//if live and flag fight ON
	{
		y_on_sprite = 64; //changing coords on sprite for fight

/*		currentFrame += time_ * .001f;
		if (currentFrame > 10) currentFrame = 0;
		sprite.setTextureRect(sf::IntRect(32 * int(currentFrame) + 32, y_on_sprite, -32, 32));
		sprite.setPosition(x - offsetX, y);*/

		if (fight && !currentFrame)//if unit is fighting and current frame of fighting reseted to 0, strike and lower lifes which is link in argument
		{
			int chk_kick = rand() % 9;//temp var for random can unit kick or not

			if (chk_kick >= 0 && chk_kick <= 4)//50% that kick or not
//			if (chk_kick >= 0 && chk_kick <= 7)//80% that kick or not
			{
				if (lifes_)
				{
					--lifes_;//lower lifes which is link in argument
//					std::cout << "Enemy Strike!" << std::endl;
				}
				if (!lifes_)
				{
					//live = 0;//unit die if kill
	//				std::cout << lifes_ << std::endl;
					return true;//return true for destriy units near destroyed block
				}
			}

//			std::cout << "Strike!" << std::endl;
//			std::cout << lifes_ << std::endl;
//			return 1;
		}
	}
	return false;//return false means block not destroyed
}

void Unit_Enemy::DEATH()//func of chk live and change to death anime
{
	if (!live)
	{
		y_on_sprite = 96;
	}
}

void Unit_Enemy::DRAW(sf::RenderWindow& window_)
{
	window_.draw(sprite);
}