/*
 * CameraLogic.hh
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_CAMERALOGIC_HH_
#define MODEL_CAMERALOGIC_HH_

class CameraLogic
{
	public:

		CameraLogic(int x, int y, int w, int h);
		virtual ~CameraLogic();

		int getCameraPosX() { return camera_x_position; }
		int getCameraPosY() { return camera_y_position; }
		int getCameraWidth() { return camera_width; }
		int getCameraHeight() { return camera_height; }
		int getLevel(){return level ;}

		void setLevel(int _level){level = _level;}
		void setCameraPosX(int x) { camera_x_position = x; }
		void setCameraPosY(int y) { camera_y_position = y; }
		void setCameraPosition(int x, int y) { camera_x_position = x; camera_y_position = y; }

		bool outOfCameraHigherLimit(int y) { return ((y - camera_y_position) < 10) ? true : false; } // Chequea para la posicion absoluta del parametro, si luego del ajuste del offset se escapa del borde superior de la ventana
		bool outOfCameraLowerLimit(int y) { return ((y - camera_y_position) > (camera_height - 10)) ? true : false; } // Idem pero para borde inferior
		bool outOfCameraRightLimit(int x) { return ((x - camera_x_position) > (camera_width - 50)) ? true : false; } // Idem pero para borde derecho
		bool outOfCameraLeftLimit(int x) { return ((x - camera_x_position) < 10) ? true : false; } // Idem pero para borde izquierdo

		bool outOfCameraLimits(int x, int y); // Chequea para todas lados (todas las condiciones anteriores juntas). Util para evitar renderizar algo que no salga en la ventana, o para controlar que el movimiento no exceda los limites

	private:

		int camera_x_position, camera_y_position;
		int camera_width, camera_height;
		int level ;
};

#endif /* MODEL_CAMERALOGIC_HH_ */
