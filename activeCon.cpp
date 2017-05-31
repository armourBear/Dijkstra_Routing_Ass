#include "activeCon.h"

ActiveConnections::ActiveConnections()
{
};


ActiveConnections::~ActiveConnections()
{
};


void ActiveConnections::updateConnections(std::vector <int>* conPath, double endTime)
{
	connection current;
	current.path = *conPath;
	current.closeTime = endTime;

	active.push_back(current);
};


void ActiveConnections::checkConnections(double curTime, importData* ser)
{
	//---------------------------------DEBUG--------------------------------------------------------------------------
	/*std::cout << "------------------ACTIVE CONNECTIONS LIST------------------" << std::endl;
	std::cout << "CURRENT TIME : " << curTime << "s" << std::endl;
	for ( size_t i = 0; i < active.size(); i++ )
	{
		std::cout << i << "." << "Time :  " << active[i].closeTime << " s Path : ";
		for ( size_t j = 0; j < active[i].path.size(); j++ )
		{
			std::cout << (char)active[i].path[j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "--------------------------------END-----------------------" << std::endl;*/
	//----------------------------------------------------------------------------------------------------------------
	
	for(size_t i = 0; i < active.size(); i++)
	{
		if (active[i].closeTime < curTime) //If the closeTime has expired, erase it from active connections and update traffic
		{	

			//---------------------------------DEBUG--------------------------------------------------------------------------
			/*std::cout << "REMOVED : ";
			for ( size_t j = 0; j < active[i].path.size(); j++ )
			{
				std::cout << (char)active[i].path[j] << " ";
			}
			std::cout << " as Current Time :" << curTime << " exceeds Close Time : " << active[i].closeTime << std::endl;*/
			//----------------------------------------------------------------------------------------------------------------

			ser->updateCapacityService(active[i].path, false);
			active.erase(active.begin() + i); 
		}
	}
};
