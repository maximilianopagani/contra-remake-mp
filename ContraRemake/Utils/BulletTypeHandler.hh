/*
 * BulletTypeHandler.hh
 *      Author: ldea
 */
#ifndef BULLETTYPE_HH_
#define BULLETTYPE_HH_

#include <string>

using namespace std;

enum BulletType {
	MACHINEGUN,
	SPREAD,
	RIFLE,
	LASER
};

class BulletTypeHandler
{
	public:
		static int getCooldown (BulletType type);
		static int getDistance (BulletType type);

	private:
};

#endif /* BULLETTYPE_HH_ */
