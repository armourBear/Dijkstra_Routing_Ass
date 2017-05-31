#ifndef LEASTLOADEDPATH_H
#define LEASTLOADEDPATH_H

#include "importData.h"
#include <iostream>
#include <math.h>

#define ALPHABET 26
#define LINKVALUE 1

typedef struct
{
	int NodeReference[ALPHABET];
	bool Visited[ALPHABET];
	int NodeCost[ALPHABET];
	double LoadingRatio[ALPHABET];
	int Path[ALPHABET][ALPHABET];
} LeastPath;

class LeastLoadedPath 
{		
	protected:
		LeastPath leastpath;

		int Optcost;
		int previous;
		
	public:
		LeastLoadedPath();
		~LeastLoadedPath();
		
		bool SearchNearest(int Start, int currentNode, std::vector<topology> topo);
		
		void ConnectCircuit(request req, std::vector<topology> topo,  std::vector <int>* pathing);
		
		int MoveToNode(int Start);
		int getOptCost();
}; 
#endif //LEASTLOADEDPATH_H
