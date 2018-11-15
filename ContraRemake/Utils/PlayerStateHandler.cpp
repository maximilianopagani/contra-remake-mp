/*
 * PlayerStateHandler.cpp
 *
 *      Author: ldea
 */
#include "PlayerStateHandler.hh"

string PlayerStateHandler::stateToString(PlayerState aState)
{
	switch(aState)
	{
		case STATE_WALKINGRIGHT:
			return "STATE_WALKINGRIGHT";
		case STATE_WALKINGRIGHTPOINTUP:
			return "STATE_WALKINGRIGHTPOINTUP";
		case STATE_WALKINGRIGHTPOITNDOWN:
			return "STATE_WALKINGRIGHTPOITNDOWN";
		case STATE_WALKINGLEFT:
			return "STATE_WALKINGLEFT";
		case STATE_WALKINGLEFTPOINTUP:
			return "STATE_WALKINGLEFTPOINTUP";
		case STATE_WALKINGLEFTPOINTDOWN:
			return "STATE_WALKINGLEFTPOINTDOWN";
		case STATE_STANDING:
			return "STATE_STANDING";
		case STATE_STANDING_BACK:
			return "STATE_STANDING_BACK";
		case STATE_JUMPINGUP:
			return "STATE_JUMPINGUP";
		case STATE_JUMPINGDOWN:
			return "STATE_JUMPINGDOWN";
		case STATE_POINTUP:
			return "STATE_POINTUP";
		case STATE_POINTFRONT:
			return "STATE_POINTFRONT";
		case STATE_POINTBACK:
			return "STATE_POINTBACK";
		case STATE_POINTDOWN:
			return "STATE_POINTDOWN";
		case STATE_POINTBODYTOGROUND:
			return "STATE_POINTBODYTOGROUND";
		case STATE_POINTUP_BACK:
			return "STATE_POINTUP_BACK";
		case STATE_POINTDOWN_BACK:
			return "STATE_POINTDOWN_BACK";
		case STATE_POINTBODYTOGROUND_BACK:
			return "STATE_POINTBODYTOGROUND_BACK";
	}
	return "STATE_FREEZED";
}

PlayerState PlayerStateHandler::stringToState(string aState)
{
	if (aState == "STATE_WALKINGRIGHT")
		return STATE_WALKINGRIGHT;
	else if (aState == "STATE_WALKINGRIGHTPOINTUP")
		return STATE_WALKINGRIGHTPOINTUP;
	else if (aState == "STATE_WALKINGRIGHTPOITNDOWN")
		return STATE_WALKINGRIGHTPOITNDOWN;
	else if (aState == "STATE_WALKINGLEFT")
		return STATE_WALKINGLEFT;
	else if (aState == "STATE_WALKINGLEFTPOINTUP")
		return STATE_WALKINGLEFTPOINTUP;
	else if (aState == "STATE_WALKINGLEFTPOINTDOWN")
		return STATE_WALKINGLEFTPOINTDOWN;
	else if (aState == "STATE_STANDING")
		return STATE_STANDING;
	else if (aState == "STATE_STANDING_BACK")
		return STATE_STANDING_BACK;
	else if (aState == "STATE_JUMPINGUP")
		return STATE_JUMPINGUP;
	else if (aState == "STATE_JUMPINGDOWN")
		return STATE_JUMPINGDOWN;
	else if (aState == "STATE_POINTUP")
		return STATE_POINTUP;
	else if (aState == "STATE_POINTFRONT")
		return STATE_POINTFRONT;
	else if (aState == "STATE_POINTBACK")
		return STATE_POINTBACK;
	else if (aState == "STATE_POINTDOWN")
		return STATE_POINTDOWN;
	else if (aState == "STATE_POINTBODYTOGROUND")
		return STATE_POINTBODYTOGROUND;
	else if (aState == "STATE_POINTUP_BACK")
		return STATE_POINTUP_BACK;
	else if (aState == "STATE_POINTDOWN_BACK")
		return STATE_POINTDOWN_BACK;
	else if (aState == "STATE_POINT")
		return STATE_POINTBODYTOGROUND_BACK;
	return STATE_FREEZED;
}

int PlayerStateHandler::getDestinationWidth(PlayerState aState)
{
	switch(aState)
	{
		case STATE_WALKINGRIGHT:
			return 58;
		case STATE_WALKINGRIGHTPOINTUP:
			return 44;
		case STATE_WALKINGRIGHTPOITNDOWN:
			return 48;
		case STATE_WALKINGLEFT:
			return 58;
		case STATE_WALKINGLEFTPOINTUP:
			return 44;
		case STATE_WALKINGLEFTPOINTDOWN:
			return 48;
		case STATE_STANDING:
			return 39;
		case STATE_STANDING_BACK:
			return 39;
		case STATE_JUMPINGUP:
			return 46;
		case STATE_JUMPINGDOWN:
			return 46;
		case STATE_POINTUP:
			return 41;
		case STATE_POINTFRONT:
			return 58;
		case STATE_POINTBACK:
			return 58;
		case STATE_POINTDOWN:
			return 51;
		case STATE_POINTBODYTOGROUND:
			return 74;
		case STATE_POINTDOWN_BACK:
			return 51;
		case STATE_POINTBODYTOGROUND_BACK:
			return 74;
		case STATE_POINTUP_BACK:
			return 41;
		case STATE_FREEZED:
			return 39;
		case STATE_DEAD:
			return 87;
	}
	return 0;
}

int PlayerStateHandler::getDestinationHeight(PlayerState aState)
{
	switch(aState)
	{
		case STATE_WALKINGRIGHT:
			return 87;
		case STATE_WALKINGRIGHTPOINTUP:
			return 87;
		case STATE_WALKINGRIGHTPOITNDOWN:
			return 87;
		case STATE_WALKINGLEFT:
			return 87;
		case STATE_WALKINGLEFTPOINTUP:
			return 87;
		case STATE_WALKINGLEFTPOINTDOWN:
			return 87;
		case STATE_STANDING:
			return 87;
		case STATE_STANDING_BACK:
			return 87;
		case STATE_JUMPINGUP:
			return 87;
		case STATE_JUMPINGDOWN:
			return 87;
		case STATE_POINTUP:
			return 82;
		case STATE_POINTFRONT:
			return 82;
		case STATE_POINTBACK:
			return 82;
		case STATE_POINTDOWN:
			return 85;
		case STATE_POINTBODYTOGROUND:
			return 87;
		case STATE_POINTDOWN_BACK:
			return 85;
		case STATE_POINTBODYTOGROUND_BACK:
			return 87;
		case STATE_POINTUP_BACK:
			return 82;
		case STATE_FREEZED:
			return 87;
		case STATE_DEAD:
			return 28;
	}
	return 0;
}

