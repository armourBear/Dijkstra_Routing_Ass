#ifndef IMPORTDATA_H
#define IMPORTDATA_H

#include <iostream>
#include <vector>

//router network
typedef struct
{
	int nodeA;				//routerA
	int nodeB;				//routerB 
	int delay;				//propogation delay
	int capacMaxi;			//maximum capacity
	int capacServ;			//load being serviced 
} topology;

typedef struct
{
	double initTime;				//Request initiation time
	int nodeA;						//routerA
	int nodeB;						//routerB
	double servTime;				//Service time of the request
} request;
                                                     
class importData
{
	protected :
		int link;						//Number of links in the topology network
		
		std::vector <topology> data;	//The topology network
		request req;					//The current serviced request
		
	public :
		importData();
		~importData();
		
		void setTopology(char inputLine[]);			//Sets the topology data
		void setRequest(char inputLine[]);			//Sets the request data
		
		bool updateCapacityService(std::vector <int> path, bool incdec);	//Updates topology capacity and returns if request was succesful

		int getNetworkSize();						//Returns the number of links in the network
		
		std::vector<topology> getNetwork();			//Returns the whole topology network
		request getRequest();						//Returns the current request
		
		void showRequest();							//For the purpose of debugging
		void showTopology();						//For the purpose of debugging
};
#endif //IMPORTDATA_H




