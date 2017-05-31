#ifndef ACTIVECON_H
#define ACTIVECON_H

#include "importData.h"

#include <math.h>

typedef struct
{
	std::vector <int> path;
	double closeTime;
} connection;

class ActiveConnections
{
	protected :
		std::vector <connection> active;

	public :
		ActiveConnections();
		~ActiveConnections();

		void updateConnections(std::vector <int>* conPath, double endTime);
		void checkConnections(double curTime, importData* ser);
};
#endif //ACTIVECON_H

