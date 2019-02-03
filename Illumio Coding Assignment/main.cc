#include <iostream>
#include "firewall.h"


int main(){
	Firewall *fw = new Firewall("rules.csv");
	
	delete fw;
}
