//
//  main.cpp
//  AutoPoke
//
//  Created by Jason Chutko on 2012-12-22.
//  Copyright 2012. All rights reserved.
//

#include <iostream>
#include <string>
#include "PokeManager.h"
#include <termios.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
	std::string email, password;

	std::cout << "Email: ";
	std::cin >> email;
	std::cout << "Password: ";

    // trickery to prevent echoing of user's password
    // when being entered into the terminal
 	termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	std::cin >> password;
    std::cout << std::endl;

    // initialize a new PokeManager and attempt to login
    PokeManager pokeManager(email, password);

    // keep prompting for user's password until successful
    // Note: there is a limit of tries per time, and then login won't be possible
    while(!pokeManager.isLoggedIn()) {
    	std::cout << "Incorrect password. Please try again.\n";
    	std::cout << "Password: ";
    	std::cin >> password;
    	std::cout << std::endl;
    	pokeManager.setPassword(password);
    }

    // successfully logged in, thus we can start poking!
    std::cout << "Logged in successfully, AutoPoking will now begin.\n";
    pokeManager.startAutoPoker();

    // reset the terminal to echo input back
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return 0; 
}  
