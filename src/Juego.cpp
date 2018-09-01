#include "Juego.h"
#include "Encabesados.h"

SDL_Rect srcR,desR;


Juego::Juego(){
    enEjecucion=true;
    cnt = 0;
}

Juego::~Juego(){}

void Juego::juegoInicializacion(){

    if( SDL_Init(SDL_INIT_EVERYTHING) == 0 ){
        std::cout << "Se inicio correctamente el SDL"<<std::endl;
        //Create window
        window = SDL_CreateWindow("Synergy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window){
            std::cout<<"Se creo la ventana"<<std::endl;
        }
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer){
            std::cout<<"Se creo el renderer"<<std::endl;
            SDL_SetRenderDrawColor(renderer,255,0,0,200);
        }

        enEjecucion=true;
    }else{
        std::cout << " Fallo al iniciar el SDL "<<std::endl;
        enEjecucion=false;
    }

    SDL_Surface* superficieTemp = IMG_Load("imagenes/personaje.png");
    personajeTextura = SDL_CreateTextureFromSurface(renderer,superficieTemp);
    SDL_FreeSurface(superficieTemp);
    desR.h = 64;
    desR.w = 64 ;
    desR.x = 40;
    desR.y = 40;
}

void Juego::eventosManejo(){
    SDL_Event evento;
    SDL_PollEvent(&evento);

    if(evento.type == SDL_QUIT){ enEjecucion = false ;}

    switch(evento.key.keysym.sym){
        case SDLK_ESCAPE:
            enEjecucion= false;
            break;
        case SDLK_UP:
            desR.y = desR.y - 4 ;
            break;
        case SDLK_LEFT:
            desR.x = desR.x-4;
            break;
        case SDLK_RIGHT:
             desR.x = desR.x+4;
            break;
        case SDLK_DOWN:
            desR.y = desR.y + 4;
            break;
        default:
            break;
    }
}

void Juego::actualizar(){
    cnt++;
}

void Juego::renderizar(){

    //LIMPIA EL RENDER ENTERO CON EL COLOR QUE SE LE DIO
    SDL_RenderClear(renderer);
    //Copy a portion of the texture to the current rendering target.
    SDL_RenderCopy(renderer,personajeTextura,NULL,&desR);
    //ACTUALIZA LA PANTALLA CON EL RENDER REALIZADO
    SDL_RenderPresent(renderer);
}

void Juego:: limpiar(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
