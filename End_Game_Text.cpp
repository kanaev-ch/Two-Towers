#include "End_Game_Text.h"



End_Game_Text::End_Game_Text()
	:win_string("You Win! Congratulations! press Esc for exit"), enemy_win_string("Die, Looser! press Esc for exit")
{
	font.loadFromFile("Xolonium-Regular.otf");

	win_text.setString(win_string);
	win_text.setFont(font);
	win_text.setCharacterSize(40);
	win_text.setColor(sf::Color::Red);
	win_text.setPosition(200, 200);

	enemy_win_text.setString(enemy_win_string);
	enemy_win_text.setFont(font);
	enemy_win_text.setCharacterSize(40);
	enemy_win_text.setColor(sf::Color::Red);
	enemy_win_text.setPosition(200, 200);
}


End_Game_Text::~End_Game_Text()
{
}


void End_Game_Text::DRAW(sf::RenderWindow& window_)const
{
	if (end_game_flag == 1)
		window_.draw(win_text);
	if (end_game_flag == 2)
		window_.draw(enemy_win_text);
}
