#include "statistics.h"

#include <math.h>
#include <iostream>

Statistics::Statistics()
{
		totalReq = 0;
		succeReq = 0;
		blockReq = 0;
		totalHop = 0;
		totalDel = 0;
};


Statistics::~Statistics()
{
};


void Statistics::updateTotalReq()
{
	totalReq++;
};


void Statistics::updateSucessfulReq()
{
	succeReq++;
};


void Statistics::updateBlockedReq()
{
	//std::cout<<"BLOCKED!!!"<<std::endl<<std::endl<<std::endl;
	blockReq++;
};


void Statistics::updatetotalHops(std::vector <int> optPath)
{
	//The number of nodes inside the path less 1 is the number of hops required
	//to perform that path
	totalHop = totalHop + (optPath.size() - 1);

};


void Statistics::updatetotalPropDelay(int cost)
{
	//The delay for SHP would be 1 and delay for SDP would be the actual delay,
	//this function can be double up on both uses, in the case of SHP the final
	//cumualtive average delay would be the same as the hop statistic.
	totalDel = totalDel + (double)cost;
};


void Statistics::showStats()
{
	double perSuccess = ((double)(succeReq)/(double)totalReq) * 100.0;
	perSuccess = perSuccess - (double)((perSuccess * 100.0) - (int)(perSuccess * 100.0))/100.0;

	double perBlocked = ((double)(blockReq)/(double)totalReq) * 100.0;
	perBlocked = perBlocked - (double)((perBlocked * 100.0) - (int)(perBlocked * 100.0))/100.0; 

	double avgHops = (double)totalHop/(double)succeReq;
	avgHops = avgHops - (double)((avgHops * 100.0) - (int)(avgHops * 100.0))/100.0; 
	
	double avgDelay = (double)totalDel/(double)succeReq;
	avgDelay = avgDelay - (double)((avgDelay * 100.0) - (int)(avgDelay * 100.0))/100.0; 

	std::cout << "total number of virtual circuit requests: " << totalReq << std::endl;
	std::cout << "number of successfully routed requests: " << succeReq << std::endl;
	std::cout << "percentage of successfully routed request: " << perSuccess << std::endl;
	std::cout << "number of blocked requests: " << blockReq << std::endl;
	std::cout << "percentage of blocked requests: " << perBlocked << std::endl;
	std::cout << "average number of hops per circuit: " << avgHops << std::endl;
	std::cout << "average cumulative propagation delay per circuit: " << avgDelay << std::endl;
};
