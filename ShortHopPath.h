#ifndef SHORTHOPPATH_H
#define SHORTHOPPATH_H

#include "importData.h"
#include <iostream>

#define ALPHABET 26
#define LINKVALUE 1

typedef struct
{
	int NodeReference[ALPHABET];
	bool Visited[ALPHABET];
	int NodeValue[ALPHABET];
	int NodeCost[ALPHABET];
	int Path[ALPHABET][ALPHABET];
} HopPath;

class ShortHopPath
{		
	protected:
		HopPath hoppath;
		int Optcost;
		int Hopcost;
		int previous;
		
	public:
		ShortHopPath();
		~ShortHopPath();
		
		bool SearchNearest(int Start, int currentNode, std::vector<topology> topo,  bool trigger);
		void ConnectCircuit(request req, std::vector<topology> topo,  std::vector <int>* pathing);
		
		int MoveToNode(int Start);
		int getOptCost();
		int getHopCost();

		void show();	//Debugging purposes
}; 
#endif
