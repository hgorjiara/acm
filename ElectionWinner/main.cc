#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
/**
Problem: Election.
Decide the winner of an election for a given list of votes.
For case when number of votes are the same, the winner should be determined
based on the reverse alphabet orders.


Algorithm:
Add each vote: O(V)
	to each candidate in its set O(1)
sort vector based with custom comparator function. C*long(C)

Order of Algorithm = Max(V + C*log(C))
*/

class Candidate{
public:
	Candidate(string n): name(n), vote(0){} 
	string name;
	int vote;
};

struct candidateCompareName{
	bool operator() (const Candidate* c1, const Candidate* c2) {
		return c1->name < c2->name;
	}
};

struct candidateCompareVotes{
	bool operator() (const Candidate *c1, const Candidate *c2){
		return c1->vote > c2->vote || (c1->vote == c2->vote && c1->name > c2->name);
	}
};

string getElectionWinner(vector<string> &votes){
	set<Candidate*, candidateCompareName> candidateSet;
	for(int i=0; i< votes.size(); i++){
		Candidate tmp(votes[i]);
		set<Candidate*>::iterator it = candidateSet.find(&tmp);
		Candidate *c;
		if(it == candidateSet.end() ){ //Candidate doesn't exist
			c = new Candidate(votes[i]);
			candidateSet.insert(c);
		} else{
			c = *it;
		}
		c->vote++;
	}
	vector<Candidate *> candidates(candidateSet.begin(), candidateSet.end());
	//for(int i=0; i< candidates.size(); i++){
	//	cout << candidates[i]->name << " : " << candidates[i]->vote << endl;
	//}
	sort(candidates.begin(), candidates.end(), candidateCompareVotes());
	string result = candidates[0]->name;
	for(int i=0; i< candidates.size(); i++){
		delete candidates[i];
	}
	return result;
}


int main (){
	string line;
	vector<string> votes;
	while(getline(cin,line)){
		votes.push_back(line);
	}
	cout << getElectionWinner(votes) << endl;
	return 0;
}
