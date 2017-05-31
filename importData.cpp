#include "importData.h"
#include <vector>
#include <algorithm>
#include <iostream>

#define PATHSIZE 25

importData::importData()
{
	link = 0;

	req.initTime = 0;
	req.nodeA = 0;
	req.nodeB = 0;
	req.servTime = 0;
};


importData::~importData()
{
};


void importData::setTopology(char inputLine[])
{
	topology setTemp = {0};

	char * token;
	char delim[] = " ,-";
	unsigned int pos = 0;

	token = strtok(inputLine, delim);
	while (token != NULL)
	{
		switch (pos)
		{
			case (0) :
				setTemp.nodeA = (int)(*token);
				pos++;
				break;

			case (1) :
				setTemp.nodeB = (int)(*token);
				pos++;
				break;

			case (2) :
				setTemp.delay = atoi(token);
				pos++;				
				break;

			case (3) :
				setTemp.capacMaxi = atoi(token);
				break;

			default :
			break;
		}
		token = strtok(NULL,delim);
	}
	//Only update if the input line has something in the first place
	if (inputLine != NULL)
	{
		//Set current serviced connections to 0
		setTemp.capacServ = 0;
		//Push through the current topology into the stored vector 
		//and update the number of links available
		data.push_back(setTemp);
		link = data.size();
	}
	delete token;
};


void importData::setRequest(char inputLine[])
{
	char * token;
	char delim[] = " ,-";
	unsigned int pos = 0;

	token = strtok(inputLine, delim);
	while (token != NULL)
	{
		switch (pos)
		{
			case (0) :
				req.initTime = atof(token);
				pos++;
				break;

			case (1) :
				req.nodeA = (int)(*token);
				pos++;
				break;

			case (2) :
				req.nodeB = (int)(*token);
				pos++;				
				break;

			case (3) :
				req.servTime = atof(token);
				break;

			default :
			break;
		}
		token = strtok(NULL,delim);
	}
	delete token;
};


bool importData::updateCapacityService(std::vector <int> path,  bool incdec)
{
	if (path.empty())
	{
		return false;
	}

	int position = 0;	//To record the link found in the topology

	for (std::size_t i = 0; i < (path.size() - 1); i++)
	{
		for (std::size_t m = 0; m < data.size(); m++)	//Find the link
		{
			if ((data[m].nodeA == path[i]) && (data[m].nodeB == path[i+1]))
			{
				position = m;
			} else if ((data[m].nodeB == path[i]) && (data[m].nodeA == path[i+1])) 
			{
				position = m;
			}
		}

		if (incdec)
		{
			if(data[position].capacServ < data[position].capacMaxi) {
				data[position].capacServ++;
			} else {
				return false;	//Cannot be serviced exit immediately and signal failiure
			}
		} else {
			//If we're removing active connections then guard agaisnt possible failiure
			if((data[position].capacServ <= data[position].capacMaxi) && (data[position].capacServ!= 0)) 
			{
				//std::cout << "REMOVED LINK : " << (char)data[position].nodeA << " to " << (char)data[position].nodeB << std::endl;
				data[position].capacServ--;
			}
		}
	}
	return true;	//Return that if the entire has been serviced both inc and dec
};


int importData::getNetworkSize()
{
	return link;
};


std::vector <topology> importData::getNetwork()
{
	return data;
};


request importData::getRequest()
{
	return req;
};


void importData::showRequest()
{
	std::cout << "Current Request" << std::endl;
	std::cout << "Req Time : " << req.initTime << "s Src " << (char)req.nodeA;
	std::cout << " Dst " << (char)req.nodeB << " TTL " << req.servTime << "s";
};


void importData::showTopology()
{
	std::cout << "TOPOLOGY NETWORK" << std::endl;

	for (size_t i = 0; i < data.size(); i++)
	{
		std::cout << "Node A : " << (char)data[i].nodeA << " Node B : " << (char)data[i].nodeB;
		std::cout << " Prop Delay : "<< data[i].delay << " Capcity : " << data[i].capacMaxi;
		std::cout << " Current Service : " << data[i].capacServ << std::endl;
	}
};

