#pragma once
#include "MessageWindow.h"
class FocusedAttributesWindow : public MessageWindow{
public:
	FocusedAttributesWindow();
	FocusedAttributesWindow(int x, int y, int width, int height, int size);
	~FocusedAttributesWindow();
	void draw(sf::RenderWindow* window);
	
	void setEntityTypeText(std::string);
	void setHealthText(int, float max);
	void setManaText(int value, float max_value);
	void setChargeText(int value, float max_value);
	void setExperienceText(int);
	void setLevelText(int);
	void setPos(float x, float y);
	void setCoordinates(float x, float y);

	void drawEntityText(sf::RenderWindow* window);
	void drawEntityHealthText(sf::RenderWindow* window);
	void drawEntityManaText(sf::RenderWindow* window);
	void drawEntityChargeText(sf::RenderWindow* window);
	void drawEntityLevelText(sf::RenderWindow* window);
	void drawEntityCoordinatesText(sf::RenderWindow* window);
	void drawEntityXp(sf::RenderWindow* window);

	private:
		
		sf::Text entity_type, health_text, mana_text, charge_text, exp_text, level_txt, coords_text;
};

