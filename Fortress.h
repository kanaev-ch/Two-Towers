#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Data.h"
#include "Explosion.h"
#include "Building.h"

class Fortress
	: public Explosion, public Building//class Explosion is member of Fortress
{
private:
	sf::Texture texture_catapult;//texture of catapult
	sf::Sprite sprite_catapult;//sprite of catapult
	float x_catapult;//coords of catapult by X
	float y_catapult;//coords of catapult by Y

	bool catapult_anime_live;
	float catapult_currentFrame;

	sf::CircleShape circle;//circle of shoot
	float x_cir_speed;//speed of circle by x
	float y_cir_speed;//speed of circle by y
	float x_cir;//coords of circle on screen by X
	float y_cir;//coords of circle on screen by y

	sf::RectangleShape line_catapult_fire;//rect line_of_fire
	float len_line_cat_fire;//length line_of_fire, , from it is counting of x_cir_speed

	bool cir_live;//flag cir live
	float cir_angle;//angle of drawed line_of_fire, from it is counting of y_cir_speed

	int fortress_life;

//	Building building;
public:
//	Building building;

	Fortress(float, float);
	~Fortress();

	void CHANGE_CATAPULT_FRAMES(float);
	void DRAW_CATAPULT(sf::RenderWindow&);

	void CATAPULT_ANIME_LIVE(bool);
	bool CATAPULT_ANIME_LIVE()const;

	void X_CIR_SPEED(float);
	float X_CIR_SPEED()const;
	void Y_CIR_SPEED(float);
	float Y_CIR_SPEED()const;

	void X_CATAPULT(float);
	float X_CATAPULT()const;
	void Y_CATAPULT(float);
	float Y_CATAPULT()const;

	void X_CIR(float);
	float X_CIR()const;
	void Y_CIR(float);
	float Y_CIR()const;

	void LEN_LINE_CAT_FIRE(float);
	float LEN_LINE_CAT_FIRE()const;

	void MOVE_CIRCLE(float);

	int COLLISION_CIR();
	void RESET_CIR_AND_START_EXPLODE();

	void DRAW_CIRCLE(sf::RenderWindow&);

	void UPDATE_LINE_CAT_FIRE(float, float);
	void DRAW_LINE_CATAPULT_FIRE(sf::RenderWindow&);

	void START_FIRE();
};

