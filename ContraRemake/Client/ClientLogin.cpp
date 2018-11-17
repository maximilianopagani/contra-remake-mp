/*
 * ClientLogin.cpp
 *
 *  Created on: 14 oct. 2018
 *      Author: nacho
 */

#include "ClientLogin.hh"
#include "ClientParser.hh"

const int BUTTON_POSITION_X = 330;
const int BUTTON_POSITION_Y = 540;
const int BUTTON_WIDTH = 108;
const int BUTTON_HEIGHT = 28;
const int TEXTBOX_POSITION_X = 211;
const int TEXTBOX_WIDTH = 280;
const int TEXTBOX_HEIGHT = 31;
const int USERTEXTBOX_POSITION_Y = 293;
const int PASSWORDTEXTBOX_POSITION_Y = 344;
const int SERVERTEXTBOX_POSITION_Y = 400;
const int PORTTEXTBOX_POSITION_Y = 454;
const int MAX_LENGTH = 18;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font *font = NULL;
TTF_Font *passwordFont = NULL;
Texture splashTexture;
Texture userTexture;
Texture passwordTexture;
Texture serverTexture;
Texture portTexture;
Texture buttonTexture;
Texture promptTexture;

Texture::Texture() {
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture() {
	free();
}

bool Texture::loadFromFile(std::string path) {
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
//		std::cout << "Unable to load image " << path.c_str()
//				<< "! SDL_image Error: " << IMG_GetError() << std::endl;
	} else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE,
				SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
//			std::cout << "Unable to create texture from " << path.c_str()
//					<< "! SDL Error: " << SDL_GetError() << std::endl;
		} else {
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
	return texture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor,
		bool isPassword) {
	free();

	SDL_Surface* textSurface = NULL;
	if (isPassword) {
		textSurface = TTF_RenderText_Solid(passwordFont, textureText.c_str(),
				textColor);
	} else {
		textSurface = TTF_RenderText_Solid(font, textureText.c_str(),
				textColor);
	}
	if (textSurface != NULL) {
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL) {
//			std::cout
//					<< "Unable to create texture from rendered text! SDL Error: "
//					<< SDL_GetError() << std::endl;
		} else {
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	} else {
//		std::cout << "Unable to render text surface! SDL_ttf Error: "
//				<< TTF_GetError() << std::endl;
	}

	return texture != NULL;
}

void Texture::free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle,
		SDL_Point* center, SDL_RendererFlip flip) {

	SDL_Rect renderQuad = { x, y, width, height };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

bool init()
{
	bool success = true;
//	if (SDL_Init( SDL_INIT_VIDEO) < 0) {
//		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError()
//				<< std::endl;
//		success = false;
//	} else {
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
//			std::cout << "Warning: Linear texture filtering not enabled!"
//					<< std::endl;
	}
	window = SDL_CreateWindow("Contra Remake", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (window == NULL) {
//			std::cout << "Window could not be created! SDL Error: "
//					<< SDL_GetError() << std::endl;
		success = false;
	} else {
		renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
//				std::cout << "Renderer could not be created! SDL Error: "
//						<< SDL_GetError() << std::endl;
			success = false;
		} else {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
//					std::cout
//							<< "SDL_image could not initialize! SDL_image Error: "
//							<< IMG_GetError() << std::endl;
				success = false;
			}
			if (TTF_Init() == -1) {
//					std::cout << "SDL_ttf could not initialize! SDL_ttf Error: "
//							<< TTF_GetError() << std::endl;
				success = false;
			}
		}
	}
//	}
	return success;
}

bool loadMedia()
{
	bool success = true;

	splashTexture.loadFromFile("../.images/login/Contra_Splash.png");

	buttonTexture.loadFromFile("../.images/login/button.png");

	font = TTF_OpenFont("../.fonts/Oxygen.ttf", 16);
	if (font == NULL) {
//		std::cout << "Failed to load Oxygen font! SDL_ttf Error: "
//				<< TTF_GetError() << std::endl;
		success = false;
	}

	passwordFont = TTF_OpenFont("../.fonts/Password.ttf", 16);
	if (passwordFont == NULL) {
//		std::cout << "Failed to load Password font! SDL_ttf Error: "
//				<< TTF_GetError() << std::endl;
		success = false;
	}

	return success;
}

void close() {

	splashTexture.free();
	userTexture.free();
	passwordTexture.free();
	serverTexture.free();
	portTexture.free();
	buttonTexture.free();
	promptTexture.free();

	TTF_CloseFont(font);
	TTF_CloseFont(passwordFont);
	font = NULL;
	passwordFont = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	TTF_Quit();
//	IMG_Quit();
//	SDL_Quit();
}

bool clientLogin(ClientHandler* client, Sound* sound)
{
	bool success = false;

	if (!init())
	{
		//std::cout << "Failed to initialize!" << std::endl;
		return success;
	}
	else
	{
		if(!loadMedia())
		{
			//std::cout << "Failed to load media!" << std::endl;
			return success;
		}
		else
		{
			ClientParser* clientParser = new ClientParser();

			if(!clientParser->loadConfiguration())
				return success;

			sound->play(0, 0, 0, 50); // Musica de login y espera de jugadores

			bool quit = false;
			bool userTextBoxEnabled = false;
			bool passwordTextBoxEnabled = false;
			bool serverTextBoxEnabled = false;
			bool portTextBoxEnabled = false;
			SDL_Event e;
			SDL_Color textColor = { 0, 0, 0, 0xFF };
			SDL_Color promptTextColor = { 255, 0, 0, 0xFF };
			std::string userText = "";
			std::string passwordText = "";
			std::string serverText = clientParser->getIP();
			std::string portText = clientParser->getPort();
			std::string promptText = "";
			SDL_StartTextInput();
			while (!quit) {
				bool renderText = true;
				int posicionBotonY = BUTTON_POSITION_Y;
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					} else if (e.type == SDL_KEYDOWN) {
						if (e.key.keysym.sym == SDLK_BACKSPACE) {
							if (userTextBoxEnabled) {
								if (userText.length() > 0) {
									userText.pop_back();
									renderText = true;
								}
							} else if (passwordTextBoxEnabled) {
								if (passwordText.length() > 0) {
									passwordText.pop_back();
									renderText = true;
								}
							} else if (serverTextBoxEnabled) {
								if (serverText.length() > 0) {
									serverText.pop_back();
									renderText = true;
								}
							} else if (portTextBoxEnabled) {
								if (portText.length() > 0) {
									portText.pop_back();
									renderText = true;
								}
							}
						} else if (e.key.keysym.sym
								== SDLK_c&& (SDL_GetModState() & KMOD_CTRL)) {
							if (userTextBoxEnabled) {
								SDL_SetClipboardText(userText.c_str());
							} else if (passwordTextBoxEnabled) {
								SDL_SetClipboardText(passwordText.c_str());
							} else if (serverTextBoxEnabled) {
								SDL_SetClipboardText(serverText.c_str());
							} else if (portTextBoxEnabled) {
								SDL_SetClipboardText(portText.c_str());
							}
						} else if (e.key.keysym.sym
								== SDLK_v&& (SDL_GetModState() & KMOD_CTRL)) {
							if (userTextBoxEnabled) {
								userText = SDL_GetClipboardText();
								renderText = true;
							} else if (passwordTextBoxEnabled) {
								passwordText = SDL_GetClipboardText();
								renderText = true;
							} else if (serverTextBoxEnabled) {
								serverText = SDL_GetClipboardText();
								renderText = true;
							} else if (portTextBoxEnabled) {
								portText = SDL_GetClipboardText();
								renderText = true;
							}
						} else if (e.key.keysym.sym == SDLK_TAB) {
							if (userTextBoxEnabled) {
								userTextBoxEnabled = false;
								passwordTextBoxEnabled = true;
								serverTextBoxEnabled = false;
								portTextBoxEnabled = false;
							} else if (passwordTextBoxEnabled) {
								userTextBoxEnabled = false;
								passwordTextBoxEnabled = false;
								serverTextBoxEnabled = true;
								portTextBoxEnabled = false;
							} else if (serverTextBoxEnabled) {
								userTextBoxEnabled = false;
								passwordTextBoxEnabled = false;
								serverTextBoxEnabled = false;
								portTextBoxEnabled = true;
							} else if (portTextBoxEnabled) {
								userTextBoxEnabled = true;
								passwordTextBoxEnabled = false;
								serverTextBoxEnabled = false;
								portTextBoxEnabled = false;
							} else {
								userTextBoxEnabled = true;
								passwordTextBoxEnabled = false;
								serverTextBoxEnabled = false;
								portTextBoxEnabled = false;
							}
						} else if (e.key.keysym.sym == SDLK_RETURN) {
							posicionBotonY += 5;
							if (userText == "" || passwordText == "") {
								promptText = "DEBE COMPLETAR USUARIO Y CONTRASEÑA";
								renderText = true;
							}
							else {
								if (!client->connectToServer(serverText, atoi(portText.c_str()))) {
									LOGGER_ERROR("Falla al intentar establecer la conexión");
									promptText = "ERROR AL INTENTAR ESTABLECER LA CONEXION";
									renderText = true;
								}
								else {
									LOGGER_DEBUG("Conexión con el servidor establecida. Se inicia ejecución del cliente");
									//ACA TENGO QUE VERIFICAR SI EL USUARIO ES CORRECTO, Y SI ES CORRECTO VERIFICO SI YA ESTÁ CONECTADO
									success = true;
									quit = true;
								}
							}
						}
					} else if (e.type == SDL_TEXTINPUT) {
						if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C')
								&& (e.text.text[0] == 'v'
										|| e.text.text[0] == 'V')
								&& (SDL_GetModState() & KMOD_CTRL))) {
							if (userTextBoxEnabled
									&& userText.length() < MAX_LENGTH) {
								userText += e.text.text;
								renderText = true;
							} else if (passwordTextBoxEnabled
									&& passwordText.length() < MAX_LENGTH) {
								passwordText += e.text.text;
								renderText = true;
							}							//
							else if (serverTextBoxEnabled
									&& serverText.length() < MAX_LENGTH) {
								serverText += e.text.text;
								renderText = true;
							} else if (portTextBoxEnabled
									&& portText.length() < MAX_LENGTH) {
								portText += e.text.text;
								renderText = true;
							}
						}
					} else if (e.type == SDL_MOUSEBUTTONDOWN) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (x > BUTTON_POSITION_X
								&& x < BUTTON_POSITION_X + BUTTON_WIDTH
								&& y > BUTTON_POSITION_Y
								&& y < BUTTON_POSITION_Y + BUTTON_HEIGHT) {
							posicionBotonY += 5;
							if (userText == "" || passwordText == "") {
								promptText = "DEBE COMPLETAR USUARIO Y CONTRASEÑA";
								renderText = true;
							}
							else {
								if (!client->connectToServer(serverText, atoi(portText.c_str()))) {
									LOGGER_ERROR("Falla al intentar establecer la conexión");
									promptText = "ERROR AL INTENTAR ESTABLECER LA CONEXION";
									renderText = true;
								}
								else {
									LOGGER_DEBUG("Conexión con el servidor establecida. Se inicia ejecución del cliente");
									//ACA TENGO QUE VERIFICAR SI EL USUARIO ES CORRECTO, Y SI ES CORRECTO VERIFICO SI YA ESTÁ CONECTADO
									success = true;
									quit = true;
								}
							}
							quit = true;
						} else if (x > TEXTBOX_POSITION_X
								&& x < TEXTBOX_POSITION_X + TEXTBOX_WIDTH
								&& y > USERTEXTBOX_POSITION_Y
								&& y
										< USERTEXTBOX_POSITION_Y
												+ TEXTBOX_HEIGHT) {
							userTextBoxEnabled = true;
							passwordTextBoxEnabled = false;
							serverTextBoxEnabled = false;
							portTextBoxEnabled = false;
						} else if (x > TEXTBOX_POSITION_X
								&& x < TEXTBOX_POSITION_X + TEXTBOX_WIDTH
								&& y > PASSWORDTEXTBOX_POSITION_Y
								&& y
										< PASSWORDTEXTBOX_POSITION_Y
												+ TEXTBOX_HEIGHT) {
							userTextBoxEnabled = false;
							passwordTextBoxEnabled = true;
							serverTextBoxEnabled = false;
							portTextBoxEnabled = false;
						} else if (x > TEXTBOX_POSITION_X
								&& x < TEXTBOX_POSITION_X + TEXTBOX_WIDTH
								&& y > SERVERTEXTBOX_POSITION_Y
								&& y
										< SERVERTEXTBOX_POSITION_Y
												+ TEXTBOX_HEIGHT) {
							userTextBoxEnabled = false;
							passwordTextBoxEnabled = false;
							serverTextBoxEnabled = true;
							portTextBoxEnabled = false;
						} else if (x > TEXTBOX_POSITION_X
								&& x < TEXTBOX_POSITION_X + TEXTBOX_WIDTH
								&& y > PORTTEXTBOX_POSITION_Y
								&& y
										< PORTTEXTBOX_POSITION_Y
												+ TEXTBOX_HEIGHT) {
							userTextBoxEnabled = false;
							passwordTextBoxEnabled = false;
							serverTextBoxEnabled = false;
							portTextBoxEnabled = true;
						} else {
							userTextBoxEnabled = false;
							passwordTextBoxEnabled = false;
							serverTextBoxEnabled = false;
							portTextBoxEnabled = false;
						}
					}
				}

				if (renderText) {
					if (userText == "")
						userTexture.loadFromRenderedText(" ", textColor, false);
					else {
						client->setUsername(userText);
						userTexture.loadFromRenderedText(userText.c_str(),
								textColor, false);
					}

					if (passwordText == "")
						passwordTexture.loadFromRenderedText(" ", textColor,
								true);
					else {
						client->setPassword(passwordText);
						passwordTexture.loadFromRenderedText(
								passwordText.c_str(), textColor, true);

					}

					if (serverText == "")
						serverTexture.loadFromRenderedText(" ", textColor,
								false);
					else
						serverTexture.loadFromRenderedText(serverText.c_str(),
								textColor, false);

					if (portText == "")
						portTexture.loadFromRenderedText(" ", textColor, false);
					else
						portTexture.loadFromRenderedText(portText.c_str(),
								textColor, false);

					if (promptText == "")
						promptTexture.loadFromRenderedText(" ", promptTextColor, false);
					else
						promptTexture.loadFromRenderedText(promptText.c_str(),
								promptTextColor, false);
				}

				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);

				splashTexture.render(0, 0);
				buttonTexture.render(BUTTON_POSITION_X, posicionBotonY);
				userTexture.render(TEXTBOX_POSITION_X + 10,
						USERTEXTBOX_POSITION_Y + 5);
				passwordTexture.render(TEXTBOX_POSITION_X + 10,
						PASSWORDTEXTBOX_POSITION_Y + 8);
				serverTexture.render(TEXTBOX_POSITION_X + 10,
						SERVERTEXTBOX_POSITION_Y + 5);
				portTexture.render(TEXTBOX_POSITION_X + 10,
						PORTTEXTBOX_POSITION_Y + 5);
				promptTexture.render(TEXTBOX_POSITION_X,
						PORTTEXTBOX_POSITION_Y + 50);
				SDL_RenderPresent(renderer);
				SDL_UpdateWindowSurface(window);
			}
			SDL_StopTextInput();
		}
	}
	close();
	return success;
}
