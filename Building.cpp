#include "Building.h"



Building::Building()
	:x_building_left_corner(600), y_building_top_corner(512)//left top corner coordinates of fort building rectangle string
{
	texture.loadFromFile("Fortress.png");//load texture tiles from file
	sprite.setTexture(texture);//load spriti from texture
}


Building::~Building()
{
}

void Building::DRAW_BUILDING(sf::RenderWindow& window_, float offsetX)
{
	for (int i = 0; i < sizeof(building_string) / sizeof(building_string[0]); ++i)//by height
	{
		for (unsigned int j = 0; j < building_string[0].getSize(); ++j)//by width
		{
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