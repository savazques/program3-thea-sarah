#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_

#include <string>
#include <iostream>

typedef std::pair<int, int>   Value;

class TeamData {

 public:
 	TeamData(std::string filename);
 	int numPlayers() const;
 	double winPercentages(int i, int j) const { return  1/*winPercentages_[i][j]*/; }

 private:
	// TODO: decide the type of this variable.
	 
	int numPlayers_;

};  // class TeamData

#endif  // _TEAMDATA_H_