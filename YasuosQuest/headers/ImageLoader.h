#pragma once
#include "SFML/Graphics.hpp"

class ImageLoader {

public:
	ImageLoader();
	virtual ~ImageLoader();

	void addTexture(sf::Texture& texture);
	sf::Texture& getTexture(int);

private:

	std::vector<sf::Texture> image_list;

};


