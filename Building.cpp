#include "Building.h"



Building::Building()
//	:x_building_left_corner(600), y_building_top_corner(512)	//initializing in Fortress::Fortress
//	:fortress_life(0)
{
	texture.loadFromFile("Fortress.png");//load texture tiles from file
	sprite.setTexture(texture);//load spriti from texture

/*	for (int i = 0; i < sizeof(building_string) / sizeof(building_string[0]); ++i)//by height
	{
		for (unsigned int j = 0; j < building_string[0].getSize(); ++j)//by width
		{
			if (building_string[i][j] != 'O') fortress_life += 100; //each block plus 100, except 'O' (empty)
		}
	}*/
}


Building::~Building()
{
}

/*void Building::CHK_BLOCKS_WITH_LIFES()//this func realized in DRAW
{
	for (int i = 0; i < 5; ++i)//by height
	{
		for (unsigned int j = 0; j < 7; ++j)//by width
		{
			if (!building_tile_lifes_arr[i][j])
				building_string[i][j] = 'O';
		}
	}
}*/

void Building::GRAVITY_BLOCKS()//func of gravity blocks
{
//	for (unsigned int i = 0; i < building_string[0].getSize() - 1; ++i)//by height (5) minus 1, because allready check next string
	for (unsigned int i = 0; i < sizeof(building_string) / sizeof(building_string[0]) - 1; ++i)//by height (5) minus 1, because allready check next string
	{
//		for (int j = 0; j < sizeof(building_string) / sizeof(building_string[0]); ++j)//by width (7)
		for (unsigned int j = 0; j < building_string[0].getSize(); ++j)//by width (7)
		{
			
			if (building_string[i + 1][j] == 'O')//if downer block is empty
			{
				char ex = building_string[i + 1][j];
				building_string[i + 1][j] = building_string[i][j];//change current and downer block by what is inside
				building_string[i][j] = ex;
			}
			if (!building_tile_lifes_arr[i + 1][j])//if downer block is empty by lifes, chk array building_tile_lifes_arr
			{
				int ex = building_tile_lifes_arr[i + 1][j];
				building_tile_lifes_arr[i + 1][j] = building_tile_lifes_arr[i][j];//change current and downer block by what is inside
				building_tile_lifes_arr[i][j] = ex;
			}
		}
	}
}

void Building::DRAW_BUILDING(sf::RenderWindow& window_, float offsetX)
{
	for (int i = 0; i < sizeof(building_string) / sizeof(building_string[0]); ++i)//by height
	{
		for (unsigned int j = 0; j < building_string[0].getSize(); ++j)//by width
		{
			if (!building_tile_lifes_arr[i][j])//chk block with block lifes in arr building_tile_lifes_arr and fill it empty
				building_string[i][j] = 'O';

			if (building_string[i][j] == 'W') sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'w') sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'T') sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'i') sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 't') sprite.setTextureRect(sf::IntRect(128, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'C') sprite.setTextureRect(sf::IntRect(160, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'c') sprite.setTextureRect(sf::IntRect(192, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'K') sprite.setTextureRect(sf::IntRect(224, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'k') sprite.setTextureRect(sf::IntRect(256, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'P') sprite.setTextureRect(sf::IntRect(288, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'Y') sprite.setTextureRect(sf::IntRect(320, 0, 32, 32));//Block of Wall tiles choose in screen sprite
			if (building_string[i][j] == 'O') sprite.setTextureRect(sf::IntRect(352, 0, 32, 32));//Empty tiles choose in screen sprite
			
			float ifl = static_cast<float>(i); float jfl = static_cast<float>(j);
			sprite.setPosition(jfl * 32 - offsetX + x_building_left_corner, ifl * 32 + y_building_top_corner);//set position of tile on screen, offsetX needs for scroll static objects and map
//			sprite_cloud.setPosition(j * 32, i * 32);
//			window_.draw(sprite_cloud);
			window_.draw(sprite);
		}
	}
//	std::cout << sizeof(building_string) / sizeof(building_string[0]) << " " << building_string[0].getSize()/* / sizeof(building_string[0][0]) - sizeof(building_string[0][0])*/ << std::endl;
}