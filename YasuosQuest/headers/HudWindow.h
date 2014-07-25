#pragma once
#include "SFML\Graphics.hpp"

class Entity;
class FocusedAttributesWindow;
class PlayerAttributesWindow;

class HudWindow : public sf::RectangleShape{

public:
	HudWindow(int width, int height);
	~HudWindow();

	void draw(sf::RenderWindow* graphics);
	void setSelectedEntityWindow(Entity* selected_entity);
	void setPlayerAttributesWindow(Entity* player);
	void clearSelectedEntityWindow();

private:
	
	FocusedAttributesWindow* player_attributes_window;
	FocusedAttributesWindow* selected_entity_window;
	bool has_selection;
};

