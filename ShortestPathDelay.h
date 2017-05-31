#ifndef SHORTESTPATHDELAY_H
#define SHORTESTPATHDELAY_H

#include "importData.h"
#include <iostream>

#define ALPHABET 26

typedef struct
{
	int NodeReference[ALPHABET];
	bool Visited[ALPHABET];
	int NodeCost[ALPHABET];
	int Path[ALPHABET][ALPHABET];
} CostPath;

class ShortestPathDelay 
{		
	protected:
		CostPath costpath;
		int Optcost;
		int previous;
		
	public:
		ShortestPathDelay();
		~ShortestPathDelay();
		
		bool SearchNearest(int Start, int currentNode, std::vector<topology> topo, bool trigger);
		void ConnectCircuit(request req, std::vector<topology> topo,  std::vector <int>* pathing);
		
		int MoveToNode(int Start);
		int getOptCost();

		void show();	//Debugging purposes
}; 
#endif //SHORTESTPATHDELAY_H
