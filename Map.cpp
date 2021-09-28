#include "Map.h"



Map::Map()
{
	texture.loadFromFile("PixelAtlas.png");//load texture tiles from file
	sprite.setTexture(texture);//load spriti from texture
//	sprite_cloud.setTexture(texture);
//	sprite_cloud.setTextureRect(sf::IntRect(0, 64, 32, 32));
}


Map::~Map()
{
}

void Map::DRAW_MAP(sf::RenderWindow& window_)
{
	for (int i = 0; i < H_by_TILES; ++i)//by height
	{
		for (int j = 0; j < W_by_TILES; ++j)//by width
		{
			if (map[i][j] == 'C') sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));//Cloud tiles choose in screen sprite
			if (map[i][j] == 'S') sprite.setTextureRect(sf::IntRect(32, 64, 32, 32));//Sky tiles choose in screen sprite
			if (map[i][j] == 'g') sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));//Grass tiles choose in screen sprite
			if (map[i][j] == 'G') sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));//Ground tiles choose in screen sprite
			if (map[i][j] == 'T')
			{
				sprite.setTextureRect(sf::IntRect(32, 64, 32, 32));//Sky tiles choose in screen sprite
				float ifl = static_cast<float>(i); float jfl = static_cast<float>(j);
				sprite.setPosition(jfl * 32 - offsetX, ifl * 32);//Under Tree draw grass tiles, offsetX needs for scroll static objects and map
				window_.draw(sprite);

				sprite.setTextureRect(sf::IntRect(0, 128, 32, 32));//Tree tiles choose in screen sprite
			}
			float ifl = static_cast<float>(i); float jfl = static_cast<float>(j);
			sprite.setPosition(jfl * 32 - offsetX, ifl * 32);//set position of tile on screen, offsetX needs for scroll static objects and map
//			sprite_cloud.setPosition(j * 32, i * 32);
//			window_.draw(sprite_cloud);
			window_.draw(sprite);
		}
	}
}