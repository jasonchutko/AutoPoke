//
//  ConnectionManager.cpp
//  AutoPoke
//
//  Created by Jason Chutko on 2012-12-22.
//  Copyright 2012. All rights reserved.
//

#include "ConnectionManager.h"
#include <iostream>
#include <sstream>

ConnectionManager::ConnectionManager() {
	curl = curl_easy_init();
	curlSetup();
}

ConnectionManager::~ConnectionManager() {
	curl_easy_cleanup(curl);
}

std::string ConnectionManager::getResponseContents() {
	return responseContents;
}

static size_t writeToString(void *contents, size_t size, size_t nmemb, void *userp)
{
	// append the data from the CURL request to the specified string reference
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void ConnectionManager::curlSetup() {
	// set up some default configurations such as UserAgent, Cookie Location, etc.
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/4.0");
	curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1 );
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseContents);
}

// a helper function easily concatenate the URL parameters
std::string loginData(std::string email, std::string password) {
	std::string temp = "email=";
	temp+=email;
	temp+="&pass=";
	temp+=password;

	return temp;
}

bool ConnectionManager::facebookLogin(std::string email, std::string password) {
	CURLcode res;

	// navigate to login page
	curl_easy_setopt(curl, CURLOPT_URL, "https://m.facebook.com/login.php");

	std::string data = loginData(email, password);

	// perform an HTTP POST with the user's credentials
	// performmd over HTTPS so user details are encrypted
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
	res = curl_easy_perform( curl );

	// a little Facebook hackery below, here's how it works:
	// if you try to view a user's Facebook page unathenticated,
	// it will return a non-200 HTTP Response Code, so we check for that.
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.facebook.com/jrcdude");
	res = curl_easy_perform( curl );

	long http_code = 0;
	curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);

	if (http_code == 200 && res != CURLE_ABORTED_BY_CALLBACK)
	{
		return true;
	}

	return false;
}

void ConnectionManager::loadPokeData() {
	CURLcode res;

	responseContents.clear();

	// navigate to the page where Pokes are listed
	curl_easy_setopt(curl, CURLOPT_URL, "https://m.facebook.com/pokes");
	res = curl_easy_perform( curl );

	long http_code = 0;
	curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);

	if (http_code != 200 || res == CURLE_ABORTED_BY_CALLBACK)
	{
		// user is no longer logged in, so force a quit
		std::cout << "User has been logged out. Please run again." << std::endl;
		abort();
	}
}

void ConnectionManager::pokeUser(std::string url) {
	// simply navigate the the Poke URL specified by the PokeManager
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_perform( curl );
}