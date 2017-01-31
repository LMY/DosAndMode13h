/*
	LMY, 3531.1
	SDL Simple Library
*/

#include "SDL.h"


bool display_bmp(char* file_name)
{
	SDL_Surface* image = SDL_LoadBMP(file_name);
	if (image == NULL) {
		fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
		return 0;
	}

	if (image->format->palette && screen->format->palette)
		SDL_SetColors(screen, image->format->palette->colors, 0, image->format->palette->ncolors);

	if(SDL_BlitSurface(image, NULL, screen, NULL) < 0)
		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
	SDL_UpdateRect(screen, 0, 0, image->w, image->h);

	SDL_FreeSurface(image);
	return 1;
}




Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;

	Uint8* p = (Uint8*) surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
		case 1: return *p;
		case 2: return *(Uint16 *)p;
		case 3: return (SDL_BYTEORDER == SDL_BIG_ENDIAN  ?  p[0] << 16 | p[1] << 8 | p[2]  :  p[0] | p[1] << 8 | p[2] << 16);
		case 4: return *(Uint32 *)p;
		default: return 0;					// this won't happen
	}
}



void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;

	Uint8* p = (Uint8*) surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16*) p = pixel;
			break;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32*) p = pixel;
			break;
	}
}
