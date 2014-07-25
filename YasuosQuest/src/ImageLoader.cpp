#include "../headers/stdafx.h"
#include "../headers/ImageLoader.h"

ImageLoader::ImageLoader() {




}

ImageLoader::~ImageLoader() {

	//Delete all images on the Heap.
	//for(std::vector<sf::Image&>::iterator it = image_list.begin(); it != image_list.end(); ++it) {

	//	delete *it;//Dereferencing iterator pointer to get to Image*

	//}
}


/**
* Adds a image to the ImageLoader
*/
void ImageLoader::addTexture(sf::Texture& text){

	image_list.push_back((text));
}

sf::Texture& ImageLoader::getTexture(int index){

	return image_list[index];
}

