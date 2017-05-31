#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

class Statistics
{
	protected :
		int totalReq;
		int succeReq;
		int blockReq;
		double totalHop;
		double totalDel;

	public :

		Statistics();
		~Statistics();

		void updateTotalReq();
		void updateSucessfulReq();
		void updateBlockedReq();
		void updatetotalHops(std::vector <int> optPath);
		void updatetotalPropDelay(int cost);

		void showStats();

};
#endif //STATISTICS_H

