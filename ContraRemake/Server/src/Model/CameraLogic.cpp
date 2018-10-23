/*
 * CameraLogic.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#include "CameraLogic.hh"

CameraLogic::CameraLogic(int x, int y, int w, int h)
{
	camera_x_position = x;
	camera_y_position = y;
	camera_width = w;
	camera_height = h;
	canMove = true;
	border = 0;
}

bool CameraLogic::outOfCameraLimits(int x, int y)
{
	// Esto chequea para la posicion absoluta pasada por parametro, si luego del ajuste del offset queda dentro o fuera de la ventana
	if(outOfCameraLeftLimit(x) || outOfCameraRightLimit(x) || outOfCameraLowerLimit(y) || outOfCameraHigherLimit(y))
		return true;
	else
		return false;
}

CameraLogic::~CameraLogic()
{
	// TODO Auto-generated destructor stub
}

