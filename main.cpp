#include "importData.h"
#include "ShortestPathDelay.h"
#include "ShortHopPath.h"
#include "leastLoadedPath.h"
#include "statistics.h"
#include "activeCon.h"

#include <fstream>
#include <istream>
#include <string>
#include <stdio.h>
#include <string.h>


int main (int argc, char* argv[])
{
	importData* service = new importData();
	ShortestPathDelay* spd = new ShortestPathDelay();
	ShortHopPath* shp = new ShortHopPath();
	LeastLoadedPath* llp = new LeastLoadedPath();
	Statistics* stats = new Statistics();
	ActiveConnections* actcon = new ActiveConnections();

	std::vector <int> determinedPath;
	int determinedDelay = 0;

	std::string protocol = argv[1];

	std::string inFile;
	std::ifstream readTopology;
	std::ifstream readWorkload;

		
	readTopology.open(argv[2]);	//Read in Topology from topology text file
	{
		while(!readTopology.eof())
		{
			std::getline(readTopology, inFile);
			char * input = new char[inFile.length() + 1];
			strcpy(input,inFile.c_str());
			service->setTopology(input);
			delete input;
		}
	}
	readTopology.close();	//Finish building the topology network, close file.
	
	readWorkload.open(argv[3]);	//Read in each request one at a time from WorkLoad
	{
		while(!readWorkload.eof())
		{
			std::getline(readWorkload, inFile);		//Get the request and import it into usable data
			char * input = new char[inFile.length() + 1];
			strcpy(input,inFile.c_str());
			service->setRequest(input);
			delete input;

			stats->updateTotalReq();
			determinedPath.clear();
			
			//Check the connections to see if any connections have expired
			actcon->checkConnections(service->getRequest().initTime, service);

			if (protocol == "SHP")
			{
				shp->ConnectCircuit(service->getRequest(), service->getNetwork(), &determinedPath);
				determinedDelay = shp->getHopCost();
			} else if (protocol == "SPD") {
				spd->ConnectCircuit(service->getRequest(), service->getNetwork(), &determinedPath);
				determinedDelay = spd->getOptCost();
			} else if (protocol == "LLP") {
				llp->ConnectCircuit(service->getRequest(), service->getNetwork(), &determinedPath);
				determinedDelay = llp->getOptCost();
			} else {
				std::cout << "Undefined Protocol" << std::endl;
				return 0;
			}

			if (service->updateCapacityService(determinedPath, true))
			{
				stats->updatetotalHops(determinedPath);		//Update statistics
				stats->updatetotalPropDelay(determinedDelay);
				stats->updateSucessfulReq();
				//Update the current number of active connections
				actcon->updateConnections(&determinedPath, (double)(service->getRequest().initTime + service->getRequest().servTime));
			} else {
				stats->updateBlockedReq();	//Confirm a blocked request
			}
		}
	}

	readWorkload.close();	//Finished running all requests close and clean up and print out stats
	stats->showStats();
	delete service, spd, shp, llp, stats, actcon;

	return 0;
}
