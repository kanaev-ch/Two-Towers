#include "game.h"
#include "Fortress.h"

static float TIME(sf::Clock& c_)//func for binding to time, This func doesn't work or work!!! WHAT A FUCK!!
{
	float time = static_cast<float>(c_.getElapsedTime().asMicroseconds());//time from create sf::Clock
//	std::cout << time << std::endl;
	c_.restart();		//restart time
	time = time / 400;	//change game speed
	return time;
}

static void DRAW_MAIN_RECT(sf::RenderWindow& window_)//func draw white main rect
{
	sf::RectangleShape main_rect(sf::Vector2f(W_float * 1.f, H_float * 1.f));
	main_rect.setFillColor(sf::Color::White);
	main_rect.setPosition(0, 0);
	window_.draw(main_rect);
}

int game(sf::RenderWindow& window_)
{
	sf::Clock clock;//create object of sf::Clock, from this moment counting time

	Map map;	//create Map
	Fortress fort(100, 630);	//create object of fortress

	float offsetX = 0;//temp var offset of scrolling map

	while (window_.isOpen())
	{
		float time = TIME(clock);
/*		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());//time from create sf::Clock
		std::cout << time << std::endl;
		clock.restart();	//restart time
		time = time / 400;  //change game speed
		std::cout << "\t" << time << std::endl;*/

		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				offsetX += 5.f;//temp scroll map
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				offsetX -= 5.f;//temp scroll map
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				fort.UPDATE_LINE_CAT_FIRE(0, -1.f);//rotate line of fire
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				fort.UPDATE_LINE_CAT_FIRE(0, 1.f);//rotate line of fire
			}
/*			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				fort.UPDATE_LINE_CAT_FIRE(1.f, 0);//increase lenght line_of_fire for speed of circle by X
			}*/
/*			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{				
//				fort.START_FIRE();
			}*/
			if (event.type == sf::Event::KeyReleased) //проверка на отпускание
			{
				if (event.key.code == sf::Keyboard::Space) //указываешь кнопку
				{
					fort.START_FIRE();
				}
			}
		}

//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			fort.UPDATE_LINE_CAT_FIRE(.05f, 0);//increase lenght line_of_fire for speed of circle by X
		}

		fort.MOVE_CIRCLE(time);//moving circle, changing it coords by X Y, Block of end circle fly and start explode is inside
		
		if (fort.EXPLODE_LIVE()) fort.EXPLODE_CHANGE_FRAMES(time);

		window_.clear();
		
		DRAW_MAIN_RECT(window_);//draw main empty white window

		map.DRAW_MAP(window_, offsetX);//draw map tiles, VERY HARD CYCLE!!!
		fort.DRAW_CATAPULT(window_);//draw catapult tile

		fort.DRAW_CIRCLE(window_);//draw circle, no matter if he is standing or flying

		fort.DRAW_LINE_CATAPULT_FIRE(window_);//draw line_of_fire rect

		if (fort.EXPLODE_LIVE()) fort.EXPLODE_DRAW_FRAME(window_);

		window_.display();

//		std::cout << fort.X_CIR() << " " << fort.Y_CIR() << std::endl;
//		std::cout << "\t\t" << time << std::endl;
	}
	return 0;
}