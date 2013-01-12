//
//  PokeManager.h
//  AutoPoke
//
//  Created by Jason Chutko on 2012-12-22.
//  Copyright 2012. All rights reserved.
//

#ifndef POKEMANAGER_H
#define POKEMANAGER_H

#include <curl/curl.h>
#include "ConnectionManager.h"
#include <string>

class PokeManager
{
private:
	ConnectionManager *connectionManager;
	std::string email, password;
	bool loggedIn;
public:
	PokeManager(std::string email, std::string password);
	~PokeManager();
	void loadPokeList();
	bool isLoggedIn();
	void startAutoPoker();
	void setPassword(std::string password);
};

#endif