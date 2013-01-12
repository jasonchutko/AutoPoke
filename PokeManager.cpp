//
//  PokeManager.cpp
//  AutoPoke
//
//  Created by Jason Chutko on 2012-12-22.
//  Copyright 2012. All rights reserved.
//

#include "PokeManager.h"
#include <iostream>

PokeManager::PokeManager(std::string email, std::string password) : email(email), password(password) {
	// allocate a new ConnectionManager, and attempt to login
	connectionManager = new ConnectionManager();
	loggedIn = connectionManager->facebookLogin(email, password);	
}

PokeManager::~PokeManager() {
	// clean up the memory of the ConnectionManager
	delete connectionManager;
}

bool PokeManager::isLoggedIn() {
	return loggedIn;
}

void PokeManager::setPassword(std::string password) {
	// this method is used when an incorrect password is entered the first time,
	// and thus a new password should be attempted and set.
	this->password = password;
	loggedIn = connectionManager->facebookLogin(email, password);
}

void PokeManager::startAutoPoker() {
	// extra logged in check
	if(loggedIn) {
		while(true) {
		loadPokeList();
		usleep(5000000);
		}
	} else {
		std::cout << "User is not logged in." << std::endl;
	}
}

void PokeManager::loadPokeList() {

	// perform a call to get the HTML data of the Poke page
	connectionManager->loadPokeData();

	std::string responseContents = connectionManager->getResponseContents();


	// parse the HTML to extract Poke-back URLs
	int i = 0;
    while ((i = responseContents.find("/a/notifications.php?poke=", i)) != std::string::npos)
    {
        std::string link = "http://m.facebook.com" + responseContents.substr(i, responseContents.find("\"", i) - i);

		while (link.find("&amp;") != std::string::npos) {
	  		link.replace( link.find("&amp;"), 5, "&");
		}

		std::cout << link << std::endl;

		// once the URL is extracted, visit it to poke them
		connectionManager->pokeUser(link);
        i++;
    }
}