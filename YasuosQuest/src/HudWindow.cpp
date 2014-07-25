#include "../headers/stdafx.h"
#include "../headers/HudWindow.h"
#include "../headers/PlayerAttributesWindow.h"
#include "../headers/Entity.h"


HudWindow::HudWindow(int width, int height){

	player_attributes_window = new FocusedAttributesWindow(8, 0, 128, 128, 16);
	selected_entity_window = new FocusedAttributesWindow(width - 256, 0, 128, 128, 16);
	has_selection = false;
}


HudWindow::~HudWindow(){

}

void HudWindow::draw(sf::RenderWindow* graphics){

	graphics->draw(*this);
	player_attributes_window->draw(graphics);

	if ( has_selection )
		selected_entity_window->draw(graphics);
}

void HudWindow::clearSelectedEntityWindow(){


	selected_entity_window->setEntityTypeText("");
	selected_entity_window->setChargeText(0, 0);
	selected_entity_window->setExperienceText(0);
	selected_entity_window->setLevelText(0);
	selected_entity_window->setHealthText(0, 0);
	selected_entity_window->setManaText(0, 0);
	has_selection = false;
}


void HudWindow::setSelectedEntityWindow(Entity* selected_entity){

	selected_entity_window->setEntityTypeText(selected_entity->getEntityType());
	selected_entity_window->setChargeText(selected_entity->getCharge(), selected_entity->definition.ChargeRate);
	selected_entity_window->setExperienceText(selected_entity->getExperience());
	selected_entity_window->setLevelText(selected_entity->getLevel());
	selected_entity_window->setHealthText(selected_entity->getHealth(), selected_entity->definition.HealthPoints);
	selected_entity_window->setManaText(selected_entity->getMana(), selected_entity->definition.ManaPoints);
	has_selection = true;

}

void HudWindow::setPlayerAttributesWindow(Entity* player){


	player_attributes_window->setEntityTypeText(player->getEntityType());
	player_attributes_window->setChargeText(player->getCharge(), player->definition.ChargeRate);
	player_attributes_window->setExperienceText(player->getExperience());
	player_attributes_window->setLevelText(player->getLevel());
	player_attributes_window->setHealthText(player->getHealth(), player->definition.HealthPoints);
	player_attributes_window->setManaText(player->getMana(), player->definition.ManaPoints);

	player_attributes_window->setCoordinates((player->getPosition().x), (player->getPosition().y));

}
