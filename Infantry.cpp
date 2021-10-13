#include "Infantry.h"



Infantry::Infantry()
	:timer_born_unit(0)
{
	texture.loadFromFile("warrior.png");
	timer_born_unit = static_cast<float>(rand() % 15000) + 5000;//start timer for born

/*	squad.push_back(Unit (texture, 500, 640));
	squad.push_back(Unit(texture, 550, 640));
	squad.push_back(Unit(texture, 600, 640));*/
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
}

void Infantry::DEATH_UNIT()//func for death anime of unit, change anime to death anime, remove unit from vector
{
	for (unsigned int i = 0; i < squad.size(); i++)
	{
		squad[i].DEATH();//IMPORTANT, chk flag unit live, change anime to death
		if (!squad[i].live && squad[i].currentFrame > 10)//remove unit from vector
			squad.erase(squad.begin() + i);
	}
}

void Infantry::UPDATE_FRAME(float time_)//update all units frames in vector
{
	for (unsigned int i = 0; i < squad.size(); i++)
	{
		squad[i].UPDATE_FRAME(time_);
	}
}

void Infantry::COLLISION(Fortress& fort_, Fortress_Enemy& fort_enemy_, float time_)//chk collision of units
{
	bool die_near_blk = false;
	float die_near_blk_coords = 0;
	for (unsigned int i = 0; i < squad.size(); i++)//chk all vector
	{
		if (fort_.X_CIR() > squad[i].X() - 32 && fort_.X_CIR() < squad[i].X() + 64 && fort_.Y_CIR() > 650)//kill units SPLASH in range of 32 pixel to left-right by CIR when it down on earth
			squad[i].live = 0;

		//block of chk cross unit with building blocks
		for (int k = 0; k < sizeof(fort_enemy_.building.building_string) / sizeof(fort_enemy_.building.building_string[0]); ++k)//by height
		{
			for (unsigned int j = 0; j < fort_enemy_.building.building_string[0].getSize(); ++j)//by width
			{
				if (squad[i].X() + 32 >= j * 32 + fort_enemy_.building.x_building_left_corner && //chk crossing by X
					squad[i].Y() == k * 32 + fort_enemy_.building.y_building_top_corner &&		 //chk crossing by Y
					fort_enemy_.building.building_string[k][j] != 'O')//chk cross unit with left corner of block
				{
					die_near_blk_coords = j * 32 + fort_enemy_.building.x_building_left_corner;

					squad[i].fight = true;//begin fight with block
					die_near_blk = squad[i].FIGHT(time_, fort_enemy_.building.building_tile_lifes_arr[k][j]);//IMPORTANT, change anime to fight, lowing lifes of block which load into like a link in argument

					if (die_near_blk)//blk kill all units near destroyed block
					{
						for (unsigned int i = 0; i < squad.size(); i++)//chk all vector
						{
							if (squad[i].X() >= die_near_blk_coords - 32)//if coords of unit and destroyed block are the same
								squad[i].live = 0;//kill em all
						}
					}

				}
				if (fort_enemy_.building.building_string[k][j] == 'O')//not freeze units if block is empty
					squad[i].fight = false;
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
}

void Infantry::MOVE(float time_)//move units
{
	for (unsigned int i = 0; i < squad.size(); i++)
	{
		squad[i].MOVE(time_);
	}
}

void Infantry::DRAW(sf::RenderWindow& window_)
{
	for (unsigned int i = 0; i < squad.size(); i++)
	{
		squad[i].DRAW(window_);
	}
//	std::cout << squad.size() << std::endl;
//	std::cout << timer_born_unit << std::endl;
}
