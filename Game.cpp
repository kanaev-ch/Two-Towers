#include "Game.h"
//#include "Fortress.h"

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
	srand((unsigned)time(NULL)); rand(); rand();
	sf::Clock clock;//create object of sf::Clock, from this moment counting time

	Map map;	//create Map
	Fortress fort(100, 630);	//create object of fortress with start coord of catapult from wich counting all other coords objects
	Fortress_Enemy fort_enemy(1300, 630);	//create object of fortress with start coord of catapult from wich counting all other coords objects
	Wind wind;

//	Unit unit(500, 640);
//	Unit_Enemy unit(1300, 640);
	Infantry infantry;

	End_Game_Text end_game_text;

//	float offsetX = 0;//temp var offset of scrolling map

	while (window_.isOpen())
	{
		float time = TIME(clock);
/*		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());//time from create sf::Clock
		std::cout << time << std::endl;
		clock.restart();	//restart time
		time = time / 400;  //change game speed
		std::cout << "\t" << time << std::endl;*/
//		if (offsetX > 220) offsetX = 220;

		sf::Event event;

		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			if (!end_game_flag)//if only not end game
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if (!fort.CIR_LIVE() && offsetX < 32 * W_by_TILES - W_float - 4)//don't scroll map over right edge AND in time of flight cir
						offsetX += 10.f;//scroll map
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					if (!fort.CIR_LIVE() && offsetX > 0)//don't scroll map over left edge AND in time of flight cir
						offsetX -= 10.f;//scroll map
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					fort.UPDATE_LINE_CAT_FIRE(0, -1.f);//rotate line of fire

	//				unit.fight = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					fort.UPDATE_LINE_CAT_FIRE(0, 1.f);//rotate line of fire

	//				unit.fight = false;

	//				infantry.squad.erase(infantry.squad.begin() + 1);
	//				infantry.squad[1].live = false;
				}
				/*			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
							{
								fort.UPDATE_LINE_CAT_FIRE(1.f, 0);//increase lenght line_of_fire for speed of circle by X
							}*/
							/*			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
										{
							//				fort.START_FIRE();
										}*/
				if (event.type == sf::Event::KeyReleased) //check for release key
				{
					if (event.key.code == sf::Keyboard::Space) //what key release
					{
						fort.START_FIRE();
						fort.CATAPULT_ANIME_LIVE(true);

						//					fort_enemy.START_FIRE();
						//					fort_enemy.CATAPULT_ANIME_LIVE(true);
					}
				}
			}
		}

//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		if (!end_game_flag)//if only not end game
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				fort.UPDATE_LINE_CAT_FIRE(.05f, 0);//increase lenght line_of_fire for speed of circle by X
			}


			fort.MOVE_CIRCLE(time, wind.WIND_SPEED());//moving circle, changing it coords by X Y, Block of end circle fly and start explode is inside, AND with speed of wind
			fort_enemy.MOVE_CIRCLE(time, wind.WIND_SPEED());//moving circle, changing it coords by X Y, Block of end circle fly and start explode is inside, AND with speed of wind

			fort.COLLISION_CIR(fort_enemy.building);//func check circle collision with ground or buildings: enemy (argument), own building (it's inside)
			fort_enemy.COLLISION_CIR(fort.building);//func check circle collision with ground or buildings: enemy (argument), own building (it's inside)

			if (fort.EXPLODE_LIVE()) fort.EXPLODE_CHANGE_FRAMES(time, true);//explode anime if FLAG is live
			if (fort_enemy.EXPLODE_LIVE()) fort_enemy.EXPLODE_CHANGE_FRAMES(time, false);//explode anime if FLAG is live

			fort_enemy.START_FIRE(wind.WIND_SPEED(), time);//start enemy fire

			if (fort.CATAPULT_ANIME_LIVE()) fort.CHANGE_CATAPULT_FRAMES(time);//anime catapult if FLAG is live
			if (fort_enemy.CATAPULT_ANIME_LIVE()) fort_enemy.CHANGE_CATAPULT_FRAMES(time);//anime catapult if FLAG is live

			wind.SET_WIND_AND_MOVE_SNOWFLAKES(time);

			//		fort.building.CHK_BLOCKS_WITH_LIFES();
			//		fort_enemy.building.CHK_BLOCKS_WITH_LIFES();
			fort.building.GRAVITY_BLOCKS();
			fort_enemy.building.GRAVITY_BLOCKS();

			/*		unit.MOVE(time);
					unit.UPDATE_FRAME(time);*/
					//		unit.FIGHT();
			infantry.BORN_UNIT(time);

			infantry.MELEE(time);
			infantry.COLLISION(fort, fort_enemy, time);

			infantry.DEATH_UNIT();
			infantry.UPDATE_FRAME(time);
			infantry.MOVE(time);
			infantry.DONT_ENEMY_FIRE_NEAR_FORT();//enemy fire near OUR fort and catapult, because frendly fire

			fort.building.GRAVITY_BLOCKS();
			fort_enemy.building.GRAVITY_BLOCKS();

			time_for_melee += time;//increase melee sound, for one time play, inside infantry.melee
		}

		window_.clear();
		
		DRAW_MAIN_RECT(window_);//draw main empty white window

		map.DRAW_MAP(window_);//draw map tiles, VERY HARD CYCLE!!!

		fort.DRAW_CATAPULT(window_);//draw catapult tile
		fort_enemy.DRAW_CATAPULT(window_);//draw catapult tile

		fort.DRAW_CIRCLE(window_);//draw circle, no matter if he is standing or flying
		fort_enemy.DRAW_CIRCLE(window_);//draw circle, no matter if he is standing or flying

		fort.DRAW_LINE_CATAPULT_FIRE(window_);//draw line_of_fire rect

		if (fort.EXPLODE_LIVE()) fort.EXPLODE_DRAW_FRAME(window_);
		if (fort_enemy.EXPLODE_LIVE()) fort_enemy.EXPLODE_DRAW_FRAME(window_);

		fort.building.DRAW_BUILDING(window_, offsetX);
		fort_enemy.building.DRAW_BUILDING(window_, offsetX);

		wind.DRAW_SNOWFLAKES(window_);

		infantry.DRAW(window_);
//		unit.DRAW(window_);

		if (end_game_flag)//end game
		{
			end_game_text.DRAW(window_);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				return 0;
			}
		}

		window_.display();

//		fort.building.GRAVITY_BLOCKS();
//		fort_enemy.building.GRAVITY_BLOCKS();
//		std::cout << fort.X_CIR() << " " << fort.Y_CIR() << std::endl;
//		std::cout << "\t\t" << time << std::endl;
//		std::cout << offsetX << std::endl;
//		std::cout << 32 * W_by_TILES - W_float - 4 << std::endl;
	}
	return 0;
}