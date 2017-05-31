#include "ShortHopPath.h"

ShortHopPath::ShortHopPath()
{
	Optcost = INT_MAX;
	Hopcost = INT_MAX;
};


ShortHopPath::~ShortHopPath()
{
};


bool ShortHopPath::SearchNearest(int Start, int currentNode, std::vector<topology> topo, bool trigger)
{	
	int DelaySum = 0;		//Sum of total delay
	int CurrentSearch = 0;
	bool flag_hascostchanged = false;

	//Initialisation
	if (currentNode == Start)
	{
		hoppath.NodeCost[currentNode - 65] = 0;
	}
	
	for (size_t i = 0;i < topo.size();i++)		
	{
		if ((currentNode == topo[i].nodeA) || (currentNode == topo[i].nodeB))
		{
			if (currentNode == topo[i].nodeA)	//Checks if first or second node
			{   
				CurrentSearch = topo[i].nodeB;
			} else {
				CurrentSearch = topo[i].nodeA;
			}
			
			for (int j = 0;j < ALPHABET;j++)
			{
				if (hoppath.NodeReference[j] != previous)
				{
					if (CurrentSearch == hoppath.NodeReference[j])
					{
						if (hoppath.NodeCost[j] > (hoppath.NodeCost[currentNode - 65] + LINKVALUE))
						{		
							//update CurrentSearch with currentPath and update Path
							hoppath.NodeCost[j] = hoppath.NodeCost[currentNode - 65] + LINKVALUE;
							hoppath.NodeValue[j] = hoppath.NodeValue[currentNode - 65] + topo[i].delay;
							flag_hascostchanged = true;
							for(int k = 0;k < ALPHABET;k++)
							{	
								if (hoppath.Path[currentNode - 65][k] != 0)
								{
									hoppath.Path[CurrentSearch - 65][k] = hoppath.Path[currentNode - 65][k];
								} else {
									hoppath.Path[CurrentSearch - 65][k] = currentNode;
									break;
								}
							} 
						}
					}
				}
			}
		}
	}
	return flag_hascostchanged;
};


int ShortHopPath::MoveToNode(int Start)
{
   int Next = 0;
   int checkCost = INT_MAX;

	for (int i = 0;i < ALPHABET; i++)
	{
		if (Start != hoppath.NodeReference[i])
		{
			if (hoppath.Visited[i] != 1)
			{
				if (hoppath.NodeCost[i] < checkCost)
				{	
					checkCost = hoppath.NodeCost[i];
					Next = hoppath.NodeReference[i];
				}
			}
		} 
	}
	hoppath.Visited[Start - 65] = 1;
	previous = Start;
	return Next;
};


void ShortHopPath::ConnectCircuit(request req, std::vector<topology> topo, std::vector <int>* pathing)
{
		
	//Initialisations 
	int CurrentLink = req.nodeA;
	previous=0;

	for (int i = 0;i < ALPHABET;i++)
	{
		hoppath.NodeReference[i] = 65 + i;		//Reference Node
		hoppath.NodeCost[i] = INT_MAX;
		hoppath.NodeValue[i] = 0;
		hoppath.Visited[i] = 0;
		for (int j = 0;j < ALPHABET;j++) 
		{
			hoppath.Path[i][j] = 0;
		}
	}
		
	while (SearchNearest(req.nodeA,CurrentLink,topo, true))	//Search till map has been minimised
	{	
		CurrentLink = MoveToNode(CurrentLink);
	}

	for (int i = 0;i < ALPHABET;i++)
	{
		if (hoppath.NodeReference[i] == req.nodeB)
		{
			if (hoppath.Path[i][0] != 0)
			{
				Optcost = hoppath.NodeCost[i];
				Hopcost = hoppath.NodeValue[i];
				for (int j = 0; j < ALPHABET; j++)
				{
					if (hoppath.Path[i][j] != 0)
					{
						pathing->push_back(hoppath.Path[i][j]);
					}
				}
				pathing->push_back(req.nodeB);
			}
		}
	}
};


int ShortHopPath::getOptCost()
{
	return Optcost;
};


int ShortHopPath::getHopCost()
{
	return Hopcost;
};



