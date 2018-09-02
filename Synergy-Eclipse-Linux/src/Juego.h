/*
 * Juego.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */
#ifndef JUEGO_H
#define JUEGO_H
#include "Encabesados.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Juego {
    public:
        Juego();
        virtual ~Juego();
        void juegoInicializacion();
        void eventosManejo();
        void actualizar();
        void renderizar();
        void limpiar();
        bool estado(){return enEjecucion; }

    protected:

    private:

        bool enEjecucion;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* personajeTextura;
};

#endif
