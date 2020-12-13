#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "font_drawing.h"

#ifndef SDL_TRIPLEBUF
#define SDL_TRIPLEBUF SDL_DOUBLEBUF
#endif

SDL_Surface* sdl_screen, *backbuffer;
uint32_t key_pressed = 0;

uint8_t str[5][64];
int buttons;

/* This is the deadzone that you should use for both sticks */
#define JOYSTICK_DEADZONE 8192
int32_t axis_input[4] = {0, 0, 0, 0};

SDL_Joystick * sdl_joy;

uint8_t joystick_stick_text[4][64] =
{
	"Left stick X axis : ",
	"Left stick Y axis : ",
	"Right stick X axis : ",
	"Right stick Y axis : ",
};

char* Return_Text(int a)
{
	switch(a)
	{
		case SDLK_UP:
			return "UP DPAD";
		break;
		case SDLK_DOWN:
			return "DOWN DPAD";
		break;
		case SDLK_LEFT:
			return "LEFT DPAD";
		break;
		case SDLK_RIGHT:
			return "RIGHT DPAD";
		break;
		
		case SDLK_LCTRL:
			return "A BUTTON";
		break;
		case SDLK_LALT:
			return "B BUTTON";
		break;
		case SDLK_LSHIFT:
			return "X BUTTON";
		break;
		case SDLK_SPACE:
			return "Y BUTTON";
		break;
		
		case SDLK_RETURN:
			return "START BUTTON";
		break;
		case SDLK_ESCAPE:
			return "SELECT BUTTON";
		break;
		
		case SDLK_TAB:
			return "L1 SHOULDER";
		break;
		case SDLK_BACKSPACE:
			return "R1 SHOULDER";
		break;
		case SDLK_PAGEUP:
			return "L2 SHOULDER";
		break;
		case SDLK_PAGEDOWN:
			return "R2 SHOULDER";
		break;
		
		case SDLK_KP_DIVIDE:
			return "L3 (L-Stick)";
		break;
		case SDLK_KP_PERIOD:
			return "R3 (R-Stick)";
		break;
		default:
			return "Nothing";
		break;
	}
}

int main (int argc, char *argv[]) 
{
	SDL_Event event;
	int quit = 0;
	int i;
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_ShowCursor(0);
	sdl_screen = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE | SDL_TRIPLEBUF);
	if (!sdl_screen)
	{
		printf("Can't set video mode\n");
		return 0;
	}
	backbuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, sdl_screen->w, sdl_screen->h, sdl_screen->format->BytesPerPixel*8, 0, 0,0,0); 
	
	sdl_joy = SDL_JoystickOpen(0);

	while(!quit)
	{
		SDL_JoystickUpdate();
		
		while (SDL_PollEvent(&event)) 
		{
			switch(event.type) 
			{
				case SDL_KEYUP:
					switch(event.key.keysym.sym) 
					{
						/* SDLK_HOME for OD needs the Power button to be detected upon release. */
						case SDLK_HOME:
							quit = 1;
						break;
						default:
						break;
					}
				break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) 
					{
						/* This is how you detect a button upon being pressed. */
						/*
						case SDLK_UP:
						// Do stuff here
						break;
						*/
						default:
							key_pressed = event.key.keysym.sym;
						break;
					}
				break;
				case SDL_JOYAXISMOTION:
					/* Second analog stick on stock is mapped to 3/4 instead of 2/3, for some reasons. */
					if (event.jaxis.axis < 4)
					axis_input[event.jaxis.axis] = event.jaxis.value;
				break;
				case SDL_QUIT:
					quit = 1;
				break;
			}
		}
		
		SDL_FillRect(backbuffer, NULL, 0);
		
		print_string("INPUT TEST", 65000, 0, 20, 5, backbuffer->pixels);
		snprintf(str[0], sizeof(str[0]), "Last button pressed : %s", Return_Text(key_pressed));
		print_string(str[0], 65000, 0, 20, 30, backbuffer->pixels);
		
		for(i=0;i<4;i++)
		{
			snprintf(str[1], sizeof(str[1]), "%s : %d", joystick_stick_text[i], axis_input[i]);
			print_string(str[1], 65000, 0, 20, 60 + (i * 30), backbuffer->pixels);
		}
		
		/* Print back buffer to the final screen */
		SDL_BlitSurface(backbuffer, NULL, sdl_screen, NULL);
		
		/* Flip the screen so it gets displayed*/
		SDL_Flip(sdl_screen);
	}
	
	/* Make sure to clean up the allocated surfaces before exiting.
	 * Most of the time when an SDL app leaks, it's for that reason.
	 * */
	
	if (sdl_screen)
	{
		SDL_FreeSurface(sdl_screen);
		sdl_screen = NULL;
	}
	if (backbuffer)
	{
		SDL_FreeSurface(backbuffer);
		backbuffer = NULL;
	}
	
	if (sdl_joy)
	{
		SDL_JoystickClose(sdl_joy);
		sdl_joy = NULL;
	}
	
	SDL_Quit();
}
