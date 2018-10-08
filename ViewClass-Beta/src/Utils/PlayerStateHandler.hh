/*
 * PlayerStateHandler.hh
 *      Author: ldea
 */
#ifndef PLAYERSTATE_HH_
#define PLAYERSTATE_HH_

#include "Headers.hh"

enum PlayerState {
	STATE_WALKINGRIGHT,
	STATE_WALKINGRIGHTPOINTUP,
	STATE_WALKINGRIGHTPOITNDOWN,
	STATE_WALKINGLEFT,
	STATE_WALKINGLEFTPOINTUP,
	STATE_WALKINGLEFTPOINTDOWN,
	STATE_STANDING,
	STATE_STANDING_BACK,
	STATE_JUMPINGUP,
	STATE_JUMPINGDOWN,
	STATE_POINTUP,
	STATE_POINTFRONT,
	STATE_POINTBACK,
	STATE_POINTDOWN,
	STATE_POINTBODYTOGROUND,
	STATE_POINTUP_BACK,
	STATE_POINTDOWN_BACK,
	STATE_POINTBODYTOGROUND_BACK,
};

class PlayerStateHandler
{
	public:
//		static const int getMaxAnimations() { return MAX_ANIMATIONS; }
		static string stateToString(PlayerState aState);
		static PlayerState stringToState(string aState);
		static int getDestinationWidth(PlayerState aState);
		static int getDestinationHeight(PlayerState aState);
		static const int MAX_ANIMATIONS = 18;

	private:
};

#endif /* PLAYER_HH_ */
