#include "Juego.h"
#include "Encabesados.h"
#include "Personaje.h"

SDL_Rect srcR,desR;

Personaje* Gio;
Uint32 frameStart=0 , frameTiempo , frameEspera;

Juego::Juego(){ enEjecucion=true;}

Juego::~Juego(){}

void Juego::juegoInicializacion(){

    if( SDL_Init(SDL_INIT_EVERYTHING) == 0 ){
        std::cout << "Se inicio correctamente el SDL"<<std::endl;
        //Create window
        window = SDL_CreateWindow("Synergy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window){
            std::cout<<"Se creo la ventana"<<std::endl;
        }

        //SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer){
            std::cout<<"Se creo el renderer"<<std::endl;
            SDL_SetRenderDrawColor(renderer,255,255,255,200);
        }

        enEjecucion=true;
    }else{
        std::cout << " Fallo al iniciar el SDL "<<std::endl;
        enEjecucion=false;
    }

    Gio = new Personaje("imagenes/espera1.png",renderer);
}

void Juego::eventosManejo(){


	SDL_Event evento;

	frameStart++;

    while(SDL_PollEvent(&evento)){

    	if(evento.type == SDL_QUIT){ enEjecucion = false ;}
    	Gio->eventos(evento);
    	frameStart = 0;
   }

    if(frameStart > 50) {
    	Gio->actualizar();
    	SDL_Delay(100);
    }

}

void Juego::actualizar(){

}

void Juego::renderizar(){

    //LIMPIA EL RENDER ENTERO CON EL COLOR QUE SE LE DIO
    SDL_RenderClear(renderer);
    //Copy a portion of the texture to the current rendering target.
    Gio->renderizar();
    //ACTUALIZA LA PANTALLA CON EL RENDER REALIZADO
    SDL_RenderPresent(renderer);
}

void Juego:: limpiar(){
	Gio-> limpiar();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
