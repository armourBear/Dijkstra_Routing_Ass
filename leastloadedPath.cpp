#include "leastloadedPath.h"

LeastLoadedPath::LeastLoadedPath()
{
	Optcost = INT_MAX;
};


LeastLoadedPath::~LeastLoadedPath()
{
};


bool LeastLoadedPath::SearchNearest(int Start, int currentNode, std::vector<topology> topo)
{	
	int DelaySum=0;		//sum of total delay
	int PredecNode=0;
	int CurrentSearch=0;
	double LoadingCheck = 0;
	bool flag_pathhaschanged = false;
	
	//Initialisation
	if (currentNode == Start)
	{
		leastpath.LoadingRatio[currentNode - 65] = 0;
		leastpath.NodeCost[currentNode - 65] = 0;
	}
	
	for (int i=0;i<topo.size();i++)
	{
		if ((currentNode == topo[i].nodeA) || (currentNode == topo[i].nodeB))
		{
			if (currentNode == topo[i].nodeA) //Checks if it is Node A or Node B
			{   
				CurrentSearch = topo[i].nodeB;
			} else {
				CurrentSearch = topo[i].nodeA;
			}
			
			for (int j = 0;j < ALPHABET; j++)
			{
				if (leastpath.NodeReference[j] != previous)
				{
					if (CurrentSearch == leastpath.NodeReference[j])
					{
						
						LoadingCheck = (1 + (double)topo[i].capacServ) / (double)topo[i].capacMaxi;
						//searching conditions//
						//cmp ratios//
						if (leastpath.LoadingRatio[j] > (leastpath.LoadingRatio[currentNode - 65] + LoadingCheck))
						{		
							
							leastpath.LoadingRatio[j]= (leastpath.LoadingRatio[currentNode - 65] + LoadingCheck);
							leastpath.NodeCost[j] = leastpath.NodeCost[currentNode - 65] + topo[i].delay;
							flag_pathhaschanged = true;
							//update CurrentSearch with currentPath and Path
							for(int k = 0;k < ALPHABET; k++)
							{	
								if (leastpath.Path[currentNode - 65][k] != 0)
								{
									leastpath.Path[CurrentSearch-65][k] = leastpath.Path[currentNode- 65][k];
								} else 
								{
									leastpath.Path[CurrentSearch-65][k] = currentNode;
									break;
								}
							} 
						}
					}
				}
			}
		}
	}
	return flag_pathhaschanged;
};


int LeastLoadedPath::MoveToNode(int Start)
{
   int Next = 0;
   double checkDelay = INT_MAX;

	for (int i = 0;i < ALPHABET; i++)
	{
		if (Start != leastpath.NodeReference[i])
		{
			if (leastpath.Visited[i] != 1)
			{
				if (leastpath.LoadingRatio[i] < checkDelay)
				{	
					checkDelay = leastpath.LoadingRatio[i];
					Next = leastpath.NodeReference[i];
				}
			}
		} 
	}
	leastpath.Visited[Start - 65]=1;
	previous = Start;
	return Next;
};


void LeastLoadedPath::ConnectCircuit(request req, std::vector<topology> topo, std::vector <int>* pathing)
{
		
	//Initialisations 
	previous = 0;
	for (int i = 0;i < ALPHABET; i++)
	{
		//Reference array
		leastpath.NodeReference[i] = 65 + i;
		leastpath.NodeCost[i] = INT_MAX;
		leastpath.LoadingRatio[i] = 1;
		leastpath.Visited[i] = false;
		for (int j = 0;j < ALPHABET; j++) 
		{
			leastpath.Path[i][j] = 0;
		}
	}
		
	int CurrentLink = req.nodeA;
	//Reset cost array in Importdata() and reset Path
	while (SearchNearest(req.nodeA,CurrentLink,topo))
	{	
		CurrentLink=MoveToNode(CurrentLink);
	}

	for (int i=0;i < ALPHABET; i++)
	{
		if (leastpath.NodeReference[i] == req.nodeB)
		{
			if (leastpath.Path[i][0] != 0)
			{
				Optcost = leastpath.NodeCost[i];
				for (int j = 0; j < ALPHABET; j++)
				{
					if (leastpath.Path[i][j] != 0)
					{
						pathing->push_back(leastpath.Path[i][j]);
					}
				}
				pathing->push_back(req.nodeB);
			}
		}
	}
};


int LeastLoadedPath::getOptCost()
{
	return Optcost;
};
