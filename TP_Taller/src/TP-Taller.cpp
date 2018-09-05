#include "Encabesados.h"

Juego* synergy;

int main( int argc, char* args[] )
{
    const int FPS = 60 ;
    const int frameDelay = 1000 / FPS ;

    Uint32 frameStart;
    int frameTiempo;

    synergy = new Juego();

    synergy->juegoInicializacion();

    //CICLO DEL JUEGO
    while(synergy->estado()){

        frameStart = SDL_GetTicks();

        synergy->eventosManejo();
        synergy->actualizar();
        synergy->renderizar();

        frameTiempo = SDL_GetTicks() - frameStart;
        if( frameDelay > frameTiempo){
            SDL_Delay( frameDelay- frameTiempo );
        }
    }

    synergy->limpiar();

	return 0;
}
