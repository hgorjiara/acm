#include "firewall.h"
#include <fstream>
#include <iostream>
#include <sstream>

template<class T>
void split(string str, vector<T> &vect, char delim){
        stringstream ss(str);
        T i;
        while (ss >> i)
        {
                vect.push_back(i);
                if (ss.peek() == delim){
                        ss.ignore();
                }
        }
}

Firewall::Firewall(string input){
	ifstream file(input);
	if(file.is_open()){
		string line;
		while(getline(file, line)){
			vector<string> row;
			split<string>(line, row, ',');
			vector<int> ports;
			getAllPorts(row[2], ports);
			vector<string> ips;
			getAllIPs(row[3], ips);
			for( int i=0; i < ports.size(); i++){
				for( int j=0; j < ips.size(); j++){	
					long code = encode(row[0], row[1], ports[i], ips[j]);
					rules.insert(code);
				}
			}
		}
	}else{
		cout << input << "cannot be found!" << endl;
	}
	
}

void Firewall::getAllPorts(string portstr, vector<int> &ports){
	if(portstr.find("-") == portstr.npos){
		ports.push_back( atoi(portstr.c_str()) );
	}else{
		vector<int> portRange;
		split<int>(portstr, portRange, '-');
		for(int i=portRange[0]; i <= portRange[1]; i++){
			ports.push_back(i);
		}
	}
}

void Firewall::generateIPSequence(string begin, string end, vector<string> &ips){
	vector<int> beginVec;
	split<int>(begin, beginVec , '.');
	vector<int> endVec;
	split<int>(begin, endVec, '.');
	while(beginVec[0] != endVec[0] && 
		beginVec[1] != endVec[1] &&
		beginVec[2] != endVec[2] &&
		beginVec[3] != endVec[3] ){
		ips.push_back(to_string(beginVec[0]) + "."+ to_string(beginVec[1]) + "." + to_string(beginVec[2]) + "." + to_string(beginVec[3]) );
		beginVec[3]++;
		if(beginVec[3] >= 256){
			beginVec[3] = 0;
			beginVec[2]++;
			if(beginVec[2] >= 256){
				beginVec[2] = 0;
				beginVec[1]++;
				if(beginVec[1] >= 256){
					beginVec[1] = 0;
					beginVec[0]++;
					if(beginVec[0] >= 256){
						beginVec[0] = 0;
					}
				}
			}
		}
	}
	ips.push_back(end);
}

void Firewall::getAllIPs(string ipstr, vector<string> &ips){
	if(ipstr.find("") == ipstr.npos){
		ips.push_back( ipstr.c_str() );
	}else {
		vector<string> ipRange;
		split<string>(ipstr, ipRange, '-');
		generateIPSequence(ipRange[0], ipRange[1], ips);
	}
}


bool Firewall::accept_packet(string direction, string protocol, int port, string ip){
	long code = encode(direction, protocol, port, ip);
	return rules.find(code) != rules.end();
}
long Firewall::encode(string direction, string protocol, int port, string ip){
	long code = direction == "inbound"? 0: 1;
	code << 1;
	code += protocol == "TCP"? 0: 1;
	code << 1;
	code += port;
	code << 16;
	code += encodeIP(ip);
	code << 32;
	return code;
}
uint Firewall::encodeIP(string ip){
	vector<int> ips;
	split(ip, ips, '.');
	uint code=0;
	for(int i=0; i < ips.size(); i++){
		code += ips[i];
		code << 8;
	}
	return code;
}

