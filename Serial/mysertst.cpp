// Test of simple serial comms, using Thierry Schneider's
// Tserial class

#include <iostream>
#include <string>
#include <ctime>
#include <assert.h>
#include "Tserial.h"

using namespace std;

// the com port we use
Tserial *com;

// Read a string from the serial port if at least one char
// is available, otherwise wait for up to timeout seconds
// for something to show up.
string readSerial(int timeout=1) {
	const int SLEEPTIME = 100;  // milliseconds
	int maxtries = 1000*timeout/SLEEPTIME;
	int ntries = 0;
	int nchars = 0;
	string response;
	
	while ( !(nchars=com->getNbrOfBytes()) && (ntries<maxtries)) {
		ntries++;
		_sleep(100);
	}

	for(int i=0; i<nchars; i++) {
		response.push_back(com->getChar());
	}
	return response;
}

	
// nasty little loop to try it out
int main()
{
	com = new Tserial();
	assert(com);	
	com->connect("COM9", 9600, spNONE);
	
	string cmd;	   
	for(;;) {
		cout << "command or R to read or Q to quit->" ;
		cin >> cmd;
		cout << endl;
	
		if (cmd == "R") {
			cout << "response was->"<< readSerial() << "<-"<< endl;
		} else if (cmd == "Q") {
			return 0;
		} else {
			com->sendArray((char*)cmd.c_str(), cmd.size());
			com->sendChar('\n');		
			cout << "response was->"<< readSerial() << "<-"<< endl;
		}	 
  	}	
}

