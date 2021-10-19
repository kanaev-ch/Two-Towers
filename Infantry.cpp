#include "Infantry.h"



Infantry::Infantry()
	:timer_born_unit(0), timer_born_unit_enemy(0)
{
	texture.loadFromFile("warrior.png");
	timer_born_unit = static_cast<float>(rand() % 15000) + 5000;//start timer for born

	texture_enemy.loadFromFile("orc.png");
	timer_born_unit_enemy = static_cast<float>(rand() % 15000) + 5000;//start timer for born

/*	squad.push_back(Unit (texture, 500, 640));
	squad.push_back(Unit(texture, 550, 640));
	squad.push_back(Unit(texture, 600, 640));*/

	sword_fight_buffer.loadFromFile("sword_fight.ogg");//load buffer of sound from file
	sword_fight_sound.setBuffer(sword_fight_buffer);//set sound
}


Infantry::~Infantry()
{
}

void Infantry::BORN_UNIT(float time_)//fucn for rand upload units
{
	timer_born_unit -= time_;
	if (timer_born_unit <= 0)
	{
		squad.push_back(Unit(texture, 150, 640));
		timer_born_unit = static_cast<float>(rand() % 15000) + 5000;
	}

	timer_born_unit_enemy -= time_;
	if (timer_born_unit_enemy <= 0)
	{
		squad_enemy.push_back(Unit_Enemy (texture_enemy, 1250, 640));
		timer_born_unit_enemy = static_cast<float>(rand() % 15000) + 5000;
	}
}

void Infantry::DEATH_UNIT()//func for death anime of unit, change anime to death anime, remove unit from vector
{
	for (unsigned int i = 0; i < squad.size(); i++)
	{
		squad[i].DEATH();//IMPORTANT, chk flag unit live, change anime to death
		if (!squad[i].live && squad[i].currentFrame > 10)//remove unit from vector
			squad.erase(squad.begin() + i);
	}

	for (unsigned int i = 0; i < squad_enemy.size(); i++)
	{
		squad_enemy[i].DEATH();//IMPORTANT, chk flag unit live, change anime to death
		if (!squad_enemy[i].live && squad_enemy[i].currentFrame > 10)//remove unit from vector
			squad_enemy.erase(squad_enemy.begin() + i);
	}
}

void Infantry::UPDATE_FRAME(float time_)//update all units frames in vector
{
	for (unsigned int i = 0; i < squad.size(); i++)
	{
		squad[i].UPDATE_FRAME(time_);
	}

	for (unsigned int i = 0; i < squad_enemy.size(); i++)
	{
		squad_enemy[i].UPDATE_FRAME(time_);
	}
}

int Infantry::MELEE(float time_)//func of melee combat between units
{
	if (squad.size())//if only vector not empty
	{
		for (unsigned int i = 0; i < squad.size(); i++)//chk all OUR vector
		{
			if (squad_enemy.size())//if only vector not empty
			{
				for (unsigned int j = 0; j < squad_enemy.size(); j++)//chk all ENEMY vector
				{
//					if (squad[i].X() + 32 >= squad_enemy[j].X() - 5 && squad[i].X() + 32 <= squad_enemy[j].X() + 5)//chk collision between units
					if (squad[i].X() + 32 >= squad_enemy[j].X() + 10 && squad[i].X() + 32 <= squad_enemy[j].X() + 20)//chk collision between units
					{
						squad[i].melee = true;//flag ON melee
						squad_enemy[j].melee = true;//flag ON melee

						squad[i].fight = true;//flag ON fight
						squad_enemy[j].fight = true;//flag ON fight

						squad[i].FIGHT(time_, squad_enemy[j].live);//func of fight, in argument opponent live, flag of fight MUST be enabled before
						squad_enemy[j].FIGHT(time_, squad[i].live);//func of fight, change anime to fight, push damage, in argument opponent live, flag of fight MUST be enabled before

						//blk of sound
//						if (time_for_melee > time_ * 100)//for one time play melee sound, DEBUG
						if (time_for_melee > time_ * 1500)//for one time play melee sound, RELEASE
						{
							sword_fight_sound.play();//play sound of fight on swords
							time_for_melee = 0;//reset timer of melee sound
//							std::cout << "Sound" << std::endl;
						}

						return 1;//exit from this func immediately, because next block OFF fight and melee
					}
				}
			}
		}

		for (unsigned int i = 0; i < squad.size(); i++)//chk all OUR vector
		{
			for (unsigned int j = 0; j < squad_enemy.size(); j++)//chk all ENEMY vector
			{
				squad[i].melee = false;//flag OFF melee
				squad[i].fight = false;//flag OFF melee

				squad_enemy[j].melee = false;//flag OFF melee
				squad_enemy[j].fight = false;//flag OFF melee
			}
		}
	}
	return 0;
}

void Infantry::COLLISION(Fortress& fort_, Fortress_Enemy& fort_enemy_, float time_)//chk collision of units
{
//	bool die_near_blk = false;
//	float die_near_blk_coords = 0;

	//Block for OUR Units
	for (unsigned int i = 0; i < squad.size(); i++)//chk all vector
	{
		if (fort_.X_CIR() > squad[i].X() - 32 && fort_.X_CIR() < squad[i].X() + 64 && fort_.Y_CIR() > 650)//kill units SPLASH in range of 32 pixel to left-right by CIR when it down on earth
			squad[i].live = 0;
		if (fort_enemy_.X_CIR() > squad[i].X() - 32 && fort_enemy_.X_CIR() < squad[i].X() + 64 && fort_enemy_.Y_CIR() > 650)//kill units SPLASH in range of 32 pixel to left-right by CIR when it down on earth
			squad[i].live = 0;
		if (!squad[i].melee)//Only if not in melee
		{
			//block of chk cross unit with building blocks
			for (int k = 0; k < sizeof(fort_enemy_.building.building_string) / sizeof(fort_enemy_.building.building_string[0]); ++k)//by height
			{
				for (unsigned int j = 0; j < fort_enemy_.building.building_string[0].getSize(); ++j)//by width
				{
					if (squad[i].X() + 32 >= j * 32 + fort_enemy_.building.x_building_left_corner && //chk crossing by X
						squad[i].Y() == k * 32 + fort_enemy_.building.y_building_top_corner &&		 //chk crossing by Y
						fort_enemy_.building.building_string[k][j] != 'O')//chk cross unit with left corner of block
					{
						float die_near_blk_coords = j * 32 + fort_enemy_.building.x_building_left_corner;//temp memory coords of destroyed block

						squad[i].fight = true;//begin fight with block

						//die_near_blk is temp var flag for check to kill all unitis near destroyed block
						bool die_near_blk = squad[i].FIGHT(time_, fort_enemy_.building.building_tile_lifes_arr[k][j]);//func of fight, change anime to fight, push damage, in argument opponent live, flag of fight MUST be enabled before

						//blk of sound
//						if (time_for_melee > time_ * 100)//for one time play melee sound, DEBUG
						if (time_for_melee > time_ * 1500)//for one time play melee sound, RELEASE
						{
							sword_fight_sound.play();//play sound of fight on swords
							time_for_melee = 0;//reset timer of melee sound
//							std::cout << "Sound" << std::endl;
						}
						
						if (die_near_blk)//blk kill all units near destroyed block
						{
							for (unsigned int i = 0; i < squad.size(); i++)//chk all vector
							{
								if (squad[i].X() >= die_near_blk_coords - 32)//if coords of unit and destroyed block are the same
									squad[i].live = 0;//kill em all
							}
						}

					}
					//				if (fort_enemy_.building.building_string[k][j] == 'O')//not freeze units if block is empty
					//					squad[i].fight = false;
					if (squad[i].X() + 32 >= fort_enemy_.X_CATAPULT())//collision unit with catapult and OUR win
						end_game_flag = 1;
				}
			}
		}
	}
/*	if (die_near_blk)//blk kill all units near destroyed block
	{
		for (unsigned int i = 0; i < squad.size(); i++)//chk all vector
		{
			if (squad[i].X() >= die_near_blk_coords - 32)//if coords of unit and destroyed block are the same
				squad[i].live = 0;//kill em all
		}
	}*/
//	std::cout << fort_.EXPLODE_LIVE() << std::endl;


	//Block for Enemy Units
	for (unsigned int i = 0; i < squad_enemy.size(); i++)//chk all vector
	{
		if (fort_.X_CIR() > squad_enemy[i].X() - 32 && fort_.X_CIR() < squad_enemy[i].X() + 64 && fort_.Y_CIR() > 650)//kill units SPLASH in range of 32 pixel to left-right by CIR when it down on earth
			squad_enemy[i].live = 0;
		if (fort_enemy_.X_CIR() > squad_enemy[i].X() - 32 && fort_enemy_.X_CIR() < squad_enemy[i].X() + 64 && fort_enemy_.Y_CIR() > 650)//kill units SPLASH in range of 32 pixel to left-right by CIR when it down on earth
			squad_enemy[i].live = 0;

		if (!squad_enemy[i].melee)//Only if not in melee
		{
			//block of chk cross unit with building blocks
			for (int k = 0; k < sizeof(fort_.building.building_string) / sizeof(fort_.building.building_string[0]); ++k)//by height
			{
				for (unsigned int j = 0; j < fort_.building.building_string[0].getSize(); ++j)//by width
				{
					if (squad_enemy[i].X() <= j * 32 + fort_.building.x_building_left_corner + 32 && //chk crossing by X
						squad_enemy[i].Y() == k * 32 + fort_.building.y_building_top_corner &&	//chk crossing by Y
						fort_.building.building_string[k][j] != 'O')//chk cross unit with left corner of block
					{
						float die_near_blk_coords = j * 32 + fort_.building.x_building_left_corner;//begin fight with block

						squad_enemy[i].fight = true;//begin fight with block

						//die_near_blk is temp var flag for check to kill all unitis near destroyed block
						bool die_near_blk = squad_enemy[i].FIGHT(time_, fort_.building.building_tile_lifes_arr[k][j]);//IMPORTANT, change anime to fight, lowing lifes of block which load into like a link in argument

						//blk of sound
//						if (time_for_melee > time_ * 100)//for one time play melee sound, DEBUG
						if (time_for_melee > time_ * 1500)//for one time play melee sound, RELEASE
						{
							sword_fight_sound.play();//play sound of fight on swords
							time_for_melee = 0;//reset timer of melee sound
//							std::cout << "Sound" << std::endl;
						}

						if (die_near_blk)//blk kill all units near destroyed block
						{
							for (unsigned int i = 0; i < squad_enemy.size(); i++)//chk all vector
							{
								if (squad_enemy[i].X() <= die_near_blk_coords + 64)//if coords of unit and destroyed block are the same
									squad_enemy[i].live = 0;//kill em all
							}
						}

					}
					//				if (fort_.building.building_string[k][j] == 'O')//not freeze units if block is empty
					//					squad_enemy[i].fight = false;
					if (squad_enemy[i].X() <= fort_.X_CATAPULT() + 64)//collision enemy unit with catapult and ENEMY win
						end_game_flag = 2;
				}
			}
		}
	}
}

int Infantry::DONT_ENEMY_FIRE_NEAR_FORT()//func of don't enemy fire near OUR fort, because frendly fire
{
	for (unsigned int i = 0; i < squad_enemy.size(); i++)
	{
		if (squad_enemy[i].X() <= 448)//border where enemy don't fire
		{
			enemy_fire_near_fort = true;
			return 1;
		}
		else enemy_fire_near_fort = false;
	}
	return 0;
}

void Infantry::MOVE(float time_)//move units
{
	for (unsigned int i = 0; i < squad.size(); i++)
	{
		squad[i].MOVE(time_);
	}

	for (unsigned int i = 0; i < squad_enemy.size(); i++)
	{
		squad_enemy[i].MOVE(time_);
	}
}

void Infantry::DRAW(sf::RenderWindow& window_)
{
	for (unsigned int i = 0; i < squad.size(); i++)
	{
		squad[i].DRAW(window_);
	}

	for (unsigned int i = 0; i < squad_enemy.size(); i++)
	{
		squad_enemy[i].DRAW(window_);
	}
//	std::cout << squad.size() << std::endl;
//	std::cout << timer_born_unit << std::endl;
}
