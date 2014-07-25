#include "../headers/stdafx.h"
#include "../headers/LogMessageWindow.h"


LogMessageWindow::LogMessageWindow(int x, int y, int width, int height, int size) : MessageWindow(x, y, width, height, size){

	message_window_background.setFillColor(sf::Color(0,0, 0, 180));
}


LogMessageWindow::~LogMessageWindow(){

}


void LogMessageWindow::addMessage(sf::Text msg){


	if (msg_queue.empty()){
		std::cout << "Msg queue is empty\n";
		//reposition the text to the boundaries of the message log window
		msg.setPosition(sf::Vector2f(this->message_window_background.getPosition().x + 10, 
			this->message_window_background.getPosition().y +  
			message_window_background.getSize().y - 14 ));

	}
	//When the number of messages in the queue reach the height of the message window, clear it.
	else if ( ((int)message_window_background.getSize().y / 14) == msg_queue.size()){//Division by constant, constant is the position of each message

		msg_queue.clear();
		msg.setPosition(sf::Vector2f(this->message_window_background.getPosition().x + 10,
			this->message_window_background.getPosition().y +
			message_window_background.getSize().y - 14));
	}
	else{

		std::cout << "Msg queue is NOT empty\n";
		msg.setPosition(sf::Vector2f(message_window_background.getPosition().x + 10, msg_queue.back().getPosition().y - 14.0f));
	}
	msg_queue.push_back(msg);
}

void LogMessageWindow::draw(sf::RenderWindow* window){
	
	window->draw(message_window_background);
	window->draw(message_window_pic);
	for (std::list<sf::Text>::iterator it = msg_queue.begin(); it != msg_queue.end(); it++){

		window->draw(*it);
	}
}

sf::Vector2f LogMessageWindow::getSize(){

	return message_window_background.getSize();

}
