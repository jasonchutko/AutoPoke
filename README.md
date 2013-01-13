AutoPoke
========

An autopoker for Facebook written in C++.  Bug your friends by poking them back in under 5 seconds!

Compilation
========
To compile AutoPoke, the only non-standard dependency is ```libcurl```.
Once you have installed libcurl, simply `cd` into the AutoPoke directory and run `make`.
Lastly, run `./AutoPoke` where you will be prompted for your Facebook username and password.

The program will then run indefinitely until you hit `CTRL+C` on the terminal window running AutoPoke.

Todo
========

*   Have a statistics manager to output names of who was poked and how many times (through Facebook Graph)
*   Make the program into a daemon process
*   GUI version eventually
*   Windows support (maybe someday)
