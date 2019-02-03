#ifndef FIREWALL_H
#define FIREWALL_H
#include<string>
#include<set>
#include<vector>
using namespace std;

class Firewall{
public:
	Firewall(string input);
	bool accept_packet(string direction, string protocol, int port, string ip);
private:
	void getAllPorts(string portstr, vector<int> &ports);
	void generateIPSequence(string begin, string end, vector<string> &ips);
	void getAllIPs(string ipstr, vector<string> &ips);
	long encode(string direction, string protocol, int port, string ip);
	uint encodeIP(string ip);
	set<long> rules;
};

#endif
