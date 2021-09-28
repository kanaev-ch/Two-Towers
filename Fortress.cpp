#include "Fortress.h"



Fortress::Fortress(float x_cat_, float y_cat_)
	: x_catapult(x_cat_), y_catapult(y_cat_), circle(5.f), x_cir_speed(0), y_cir_speed(0),
	len_line_cat_fire(5.f), cir_live(false), cir_angle(30),//create start parameters of coords, circle size, circle speed, lenght line_of_fire
	catapult_anime_live(false), catapult_currentFrame(0), fortress_life(0)
{
	texture_catapult.loadFromFile("catapult.png");
	sprite_catapult.setTexture(texture_catapult);
	sprite_catapult.setTextureRect(sf::IntRect(0, 0, 64, 46));//start frame of catapult

	//start parameters of circle
	x_cir = x_catapult + 10; 
	y_cir = y_catapult + 30;
	circle.setFillColor(sf::Color::Black);
	circle.setPosition(x_cir, y_cir);

	//start parameters of line_of_fire
	line_catapult_fire.setSize(sf::Vector2f(len_line_cat_fire + 50, 5.f));
	line_catapult_fire.setFillColor(sf::Color(15, 180, 140));
	line_catapult_fire.rotate(-cir_angle);
	line_catapult_fire.setPosition(x_catapult, y_catapult);

	//block of initialising count of fortress life, each block plus 100, except 'O' (empty)
	for (int i = 0; i < sizeof(building_string) / sizeof(building_string[0]); ++i)//by height
	{
		for (unsigned int j = 0; j < building_string[0].getSize(); ++j)//by width
		{
			if (building_string[i][j] != 'O') fortress_life += 100; //each block plus 100, except 'O' (empty)
		}
	}
}


Fortress::~Fortress()
{
}

void Fortress::CHANGE_CATAPULT_FRAMES(float time_)
{
	catapult_currentFrame += .004f * time_;//speed of changing anime frames
	if (catapult_currentFrame > 3)//STOP anime, there are 12 frames in sprite sheet
	{
		catapult_currentFrame = 0;//reset start frame
		catapult_anime_live = false;//not draw explode frames
	}
	sprite_catapult.setTextureRect(sf::IntRect(64 * static_cast<int>(catapult_currentFrame), 0, 64, 46));//changing frames of explode
}

void Fortress::DRAW_CATAPULT(sf::RenderWindow& window_)//draw catapult tile
{
//	sprite_catapult.setTextureRect(sf::IntRect(0, 0, 64, 48));
	sprite_catapult.setPosition(x_catapult - offsetX, y_catapult);//offsetX needs for scroll static objects and map
	window_.draw(sprite_catapult);

	std::cout << fortress_life << std::endl;
}

void Fortress::CATAPULT_ANIME_LIVE(bool l_)
{
	catapult_anime_live = l_;
}

bool Fortress::CATAPULT_ANIME_LIVE()const
{
	return catapult_anime_live;
}

void Fortress::X_CIR_SPEED(float x_)
{
	x_cir_speed = x_;
}
float Fortress::X_CIR_SPEED()const
{
	return x_cir_speed;
}

void Fortress::Y_CIR_SPEED(float y_)
{
	y_cir_speed = y_;
}

float Fortress::Y_CIR_SPEED()const
{
	return y_cir_speed;
}

void Fortress::X_CATAPULT(float x_)
{
	x_catapult = x_;
}
float Fortress::X_CATAPULT()const
{
	return x_catapult;
}

void Fortress::Y_CATAPULT(float y_)
{
	y_catapult = y_;
}

float Fortress::Y_CATAPULT()const
{
	return y_catapult;
}

void Fortress::X_CIR(float x_)
{
	x_cir = x_;
}
float Fortress::X_CIR()const
{
	return x_cir;
}

void Fortress::Y_CIR(float y_)
{
	y_cir = y_;
}

float Fortress::Y_CIR()const
{
	return y_cir;
}

void Fortress::LEN_LINE_CAT_FIRE(float l_)
{
	len_line_cat_fire = l_;
}

float Fortress::LEN_LINE_CAT_FIRE()const
{
	return len_line_cat_fire;
}

void Fortress::MOVE_CIRCLE(float time_)//changing coord of circle at screen
{
	if (cir_live)//Only if circle is live
	{
		x_cir += x_cir_speed * time_;//changing by X with speed and sf::Clock
	//	if (y_cir < 650) y_cir -= y_cir_speed * time_;//changing by Y with speed and sf::Clock
		y_cir -= y_cir_speed * time_;//changing by Y with speed and sf::Clock
//		circle.setPosition(x_cir - offsetX_, y_cir);//set coords in screen with changed parameters
		y_cir_speed -= .00005f * time_;//it's for gravitation of circle, lower speed by Y and changing it vector

		if (x_cir > W_float - 150 && x_cir < 32 * W_by_TILES - 150) offsetX += x_cir_speed * time_;//change offsetX for scroll picture with map and static objects, but no more than size of map
	}

/*	//block end_of fire, reset all values to default
	if (y_cir > 660 && (x_cir != x_catapult + 10))//for not working if circle is at start place of catapult
	{
		//block of start explode
		Explosion::EXPLODE_LIVE(true);
		Explosion::X_EXPLODE(x_cir - 10);
		Explosion::Y_EXPLODE(y_cir - 15);

//		std::cout << Explosion::X_EXPLODE() << " " << x_cir << std::endl;

		//block of reset circle to start position
		x_cir = x_catapult + 10;//reset cir to start coords
		y_cir = y_catapult + 30;//reset cir to start coords
		x_cir_speed = y_cir_speed = 0;//no cir move by X Y
		cir_live = false;//fall flag cur live, needs for one time live cir in time of fily
		line_catapult_fire.setSize(sf::Vector2f(len_line_cat_fire + 50, 5.f));//set default size of line_of_fire

//		offsetX = 0;//reset offsetX for scroll map to start position
//		circle.setPosition(x_cir - offsetX_, y_cir);//set coords in screen with changed parameters

//		std::cout << Explosion::X_EXPLODE() << " " << x_cir << std::endl;
	}*/
}

void Fortress::RESET_CIR_AND_START_EXPLODE()//func reset circle to start position and start explode
{
	//block of start explode
	Explosion::EXPLODE_LIVE(true);
	Explosion::X_EXPLODE(x_cir - 10);
	Explosion::Y_EXPLODE(y_cir - 15);

	//		std::cout << Explosion::X_EXPLODE() << " " << x_cir << std::endl;

	//block of reset circle to start position
	x_cir = x_catapult + 10;//reset cir to start coords
	y_cir = y_catapult + 30;//reset cir to start coords
	x_cir_speed = y_cir_speed = 0;//no cir move by X Y
	cir_live = false;//fall flag cur live, needs for one time live cir in time of fily
	line_catapult_fire.setSize(sf::Vector2f(len_line_cat_fire + 50, 5.f));//set default size of line_of_fire
}

int Fortress::COLLISION_CIR()//func check circle collision with ground or building
{
	//block of chk collision with ground
	if (y_cir > 660 && (x_cir != x_catapult + 10))//for not working if circle is at start place of catapult
	{
		RESET_CIR_AND_START_EXPLODE();
		//block of start explode
/*		Explosion::EXPLODE_LIVE(true);
		Explosion::X_EXPLODE(x_cir - 10);
		Explosion::Y_EXPLODE(y_cir - 15);

		//		std::cout << Explosion::X_EXPLODE() << " " << x_cir << std::endl;

		//block of reset circle to start position
		x_cir = x_catapult + 10;//reset cir to start coords
		y_cir = y_catapult + 30;//reset cir to start coords
		x_cir_speed = y_cir_speed = 0;//no cir move by X Y
		cir_live = false;//fall flag cur live, needs for one time live cir in time of fily
		line_catapult_fire.setSize(sf::Vector2f(len_line_cat_fire + 50, 5.f));//set default size of line_of_fire*/

//		offsetX = 0;//reset offsetX for scroll map to start position
//		circle.setPosition(x_cir - offsetX_, y_cir);//set coords in screen with changed parameters

//		std::cout << Explosion::X_EXPLODE() << " " << x_cir << std::endl;
		return 0;//exit without cheking farer
	}

	//block of chk collision with blocks of building
	for (int i = 0; i < sizeof(building_string) / sizeof(building_string[0]); ++i)//by height
	{
		for (unsigned int j = 0; j < building_string[0].getSize(); ++j)//by width
		{
			if (x_cir + 5 >= j * 32 - offsetX + x_building_left_corner && y_cir + 5 >= i * 32 + y_building_top_corner &&//chk right edge of cir with cross left edge of block
				x_cir <= j * 32 - offsetX + x_building_left_corner + 32 && y_cir <= i * 32 + y_building_top_corner + 32 &&//chk left edge of cir with cross right edge of block
				Building::building_string[i][j] != 'O')//chk if block isn't empty
			{
				Building::building_string[i][j] = 'O';//mark block empty

				RESET_CIR_AND_START_EXPLODE();

				if (!(fortress_life -= 100)) exit(0);//temp end game if fortress life is 0
/*				//block of start explode
				Explosion::EXPLODE_LIVE(true);
				Explosion::X_EXPLODE(x_cir - 10);
				Explosion::Y_EXPLODE(y_cir - 15);

				//block of reset circle to start position
				x_cir = x_catapult + 10;//reset cir to start coords
				y_cir = y_catapult + 30;//reset cir to start coords
				x_cir_speed = y_cir_speed = 0;//no cir move by X Y
				cir_live = false;//fall flag cur live, needs for one time live cir in time of fily
				line_catapult_fire.setSize(sf::Vector2f(len_line_cat_fire + 50, 5.f));//set default size of line_of_fire*/

				return 0;
			}
		}
	}
	return 0;
}

void Fortress::DRAW_CIRCLE(sf::RenderWindow& window_)
{
	circle.setPosition(x_cir - offsetX, y_cir);//offsetX needs for scroll static objects and map
	window_.draw(circle);
}

void Fortress::UPDATE_LINE_CAT_FIRE(float x_, float rotate_)//changing lenght and rotate line_of_fire
{
	if (len_line_cat_fire <= 50) len_line_cat_fire += x_;//changing length of line, no more than 50, it counts from 5 to 50 (x_cir_speed diapazone 0.05 -> 0.5)
	line_catapult_fire.setSize(sf::Vector2f(len_line_cat_fire + 50, 5.f));//set default size of line, +50 needs for more longer length in drawing

	if (cir_angle >= 30 && cir_angle < 45 || cir_angle < 30 && rotate_ < 0 || cir_angle >= 45 && rotate_ > 0)//rotate line_of_fire from 30 to 45 angle (y_cir_speed diapazone 0.1 -> 0.25)
	{
		cir_angle -= rotate_;
		line_catapult_fire.rotate(rotate_);//rotate line_of_fire
//		std::cout << cir_angle << std::endl;
	}
}

void Fortress::DRAW_LINE_CATAPULT_FIRE(sf::RenderWindow& window_)
{
//	line_catapult_fire.setSize(sf::Vector2f(len_line_cat_fire + 50, 5.f));//set new size of line
	line_catapult_fire.setPosition(x_catapult - offsetX, y_catapult);//offsetX needs for scroll static objects and map
	window_.draw(line_catapult_fire);
}

void Fortress::START_FIRE()//func of start cir fly if fire
{
	if (!cir_live)//only if cir not flying now
	{
		cir_live = true;//reset to default flag cir live
		x_cir_speed = len_line_cat_fire / 100.f;//speed by X is modyfied lenght of line_of_fire

//		std::cout << x_cir_speed << " " << y_cir_speed << std::endl;

		len_line_cat_fire = 5.f;//rest to default lenght of line_of_fire

//		y_cir_speed = .1f;
		y_cir_speed = (cir_angle - 20) / 100.f;//speed by Y is modyfied lenght of angle of line_of_fire
//		std::cout << y_cir_speed << std::endl;

	}
}