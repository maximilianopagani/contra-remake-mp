/*
 * ICollisional.hh
 *
 *  Created on: Sep 20, 2018
 *      Author: pola17
 */

#ifndef ICOLLISIONAL_HH_
#define ICOLLISIONAL_HH_

class ICollisional
{
	public:

		virtual ~ICollisional(){};
		virtual int getLeftLimit() = 0;
		virtual int getRightLimit() = 0;
		virtual int getTopLimit() = 0;
		virtual int getBottomLimit() = 0;

	private:
};

#endif /* ICOLLISIONAL_HH_ */
