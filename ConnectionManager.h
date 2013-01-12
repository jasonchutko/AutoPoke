//
//  ConnectionManager.h
//  AutoPoke
//
//  Created by Jason Chutko on 2012-12-22.
//  Copyright 2012. All rights reserved.
//

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <string>
#include <curl/curl.h> 

class ConnectionManager
{
private:
	CURL* curl;
	std::string responseContents;
	void curlSetup();
	
public:
	ConnectionManager();
	~ConnectionManager();
	bool successfulConnection();
	bool successfulAuthentication();
	std::string getResponseContents();
	void pokeUser(std::string url);
	void loadPokeData();
	bool facebookLogin(std::string email, std::string password);
};

#endif