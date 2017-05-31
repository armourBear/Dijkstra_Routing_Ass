#include "ShortestPathDelay.h"

ShortestPathDelay::ShortestPathDelay()
{
	Optcost = INT_MAX;
};


ShortestPathDelay::~ShortestPathDelay()
{
};


bool ShortestPathDelay::SearchNearest(int Start, int currentNode, std::vector<topology> topo, bool trigger)
{	
	int DelaySum = 0;		//Sum of total delay
	int CurrentSearch = 0;
	int previousLowestPosition = INT_MAX;
	int currentLowestPosition = INT_MAX;
	int lowestCost = INT_MAX;
	bool flag_hascostchanged = false;

	//Initialisation
	if (currentNode == Start)
	{
		costpath.NodeCost[currentNode - 65] = 0;
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
				if (costpath.NodeReference[j] != previous)
				{
					if (CurrentSearch == costpath.NodeReference[j])
					{
						if (costpath.NodeCost[j] > (costpath.NodeCost[currentNode - 65] + topo[i].delay))
						{		
							//update CurrentSearch with currentPath and update Path
							costpath.NodeCost[j] = costpath.NodeCost[currentNode - 65] + topo[i].delay;
							flag_hascostchanged = true;

							for(int k = 0;k < ALPHABET;k++)
							{	
								if (costpath.Path[currentNode - 65][k] != 0)
								{
									costpath.Path[CurrentSearch - 65][k] = costpath.Path[currentNode - 65][k];
								} else {
									costpath.Path[CurrentSearch - 65][k] = currentNode;
									break;
								}
							} 
						}
					}
				}
			}
		}
	}
	//Search second lowest cost node since dead end has been reached
	if (!flag_hascostchanged && trigger)
	{
		for (size_t i = 0; i < ALPHABET; i++)
		{
			if (costpath.NodeCost[i] < lowestCost )
			{
				previousLowestPosition = currentLowestPosition;
				lowestCost = costpath.NodeCost[i];
				currentLowestPosition = i;
			}
		}

		if ((previousLowestPosition != INT_MAX) && (currentLowestPosition != INT_MAX))	//Guard against failiure
		{
			currentNode = costpath.NodeReference[previousLowestPosition];	//Assign the second lowest node as new search node
			for  (size_t h = 0; h < ALPHABET; h++)
			{
				if (costpath.Path[previousLowestPosition][h] != 0)
				{
					previous = costpath.Path[previousLowestPosition][h];
				}
			}
			flag_hascostchanged = SearchNearest(Start, currentNode, topo, false);
		}
	}
	return flag_hascostchanged;
};


int ShortestPathDelay::MoveToNode(int Start)
{
   int Next = 0;
   int checkDelay = INT_MAX;

	for (int i = 0;i < ALPHABET; i++)
	{
		if (Start != costpath.NodeReference[i])
		{
			if (costpath.Visited[i] != 1)
			{
				if (costpath.NodeCost[i] < checkDelay)
				{	
					checkDelay = costpath.NodeCost[i];
					Next = costpath.NodeReference[i];
				}
			}
		} 
	}
	costpath.Visited[Start - 65] = 1;
	previous=Start;
	return Next;
};


void ShortestPathDelay::ConnectCircuit(request req, std::vector<topology> topo, std::vector <int>* pathing)
{
		
	//Initialisations 
	int CurrentLink = req.nodeA;
	int previous = 0;
	
	for (int i = 0;i < ALPHABET;i++)
	{
		costpath.NodeReference[i] = 65 + i;		//Reference Node
		costpath.NodeCost[i] = INT_MAX;
		costpath.Visited[i] = 0;
		for (int j = 0;j < ALPHABET;j++) 
		{
			costpath.Path[i][j] = 0;
		}
	}
		
	while (SearchNearest(req.nodeA,CurrentLink,topo, true))	//Loop until the whole map has been minimised 
	{	
		CurrentLink = MoveToNode(CurrentLink);
	}

	for (int i = 0;i < ALPHABET;i++)
	{
		if ((costpath.NodeReference[i] == req.nodeB))
		{
			if (costpath.Path[i][0] != 0)
			{
				Optcost = costpath.NodeCost[i];
				for (int j = 0; j < ALPHABET; j++)
				{
					if (costpath.Path[i][j] != 0)
					{
						pathing->push_back(costpath.Path[i][j]);
					}
				}
				pathing->push_back(req.nodeB);
			}
		}
	}
};


int ShortestPathDelay::getOptCost()
{
	return Optcost;
};


