#include "SDL.h"
#include <stdio.h>

extern "C" {
int SDL_Init(uint32_t flags) { return 0; }
const char* SDL_GetError(void) { return "Mock Error"; }
SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, uint32_t flags) { return (SDL_Window*)1; }
SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, uint32_t flags) { return (SDL_Renderer*)1; }
SDL_Texture* SDL_CreateTexture(SDL_Renderer* renderer, uint32_t format, int access, int w, int h) { return (SDL_Texture*)1; }
int SDL_UpdateTexture(SDL_Texture* texture, const void* rect, const void* pixels, int pitch) { return 0; }
int SDL_RenderClear(SDL_Renderer* renderer) { return 0; }
int SDL_RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, const void* srcrect, const void* dstrect) { return 0; }
void SDL_RenderPresent(SDL_Renderer* renderer) {}
void SDL_DestroyTexture(SDL_Texture* texture) {}
void SDL_DestroyRenderer(SDL_Renderer* renderer) {}
void SDL_DestroyWindow(SDL_Window* window) {}
void SDL_Quit(void) {}
int SDL_PollEvent(SDL_Event* event) { return 0; }
void SDL_Delay(uint32_t ms) {}
SDL_Surface* SDL_CreateRGBSurfaceWithFormatFrom(void* pixels, int width, int height, int depth, int pitch, uint32_t format) { return (SDL_Surface*)1; }
SDL_Surface* SDL_ConvertSurfaceFormat(SDL_Surface* src, uint32_t pixel_format, uint32_t flags) { return (SDL_Surface*)1; }
int SDL_SaveBMP(SDL_Surface* surface, const char* file) {
    printf("Mock SDL_SaveBMP to %s\n", file);
    // Create a valid dummy BMP file (minimal header)
    FILE* f = fopen(file, "wb");
    if (f) {
        // BMP Header (14 bytes)
        unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
        unsigned int filesize = 54 + 3; // minimal size
        bmpfileheader[2] = (unsigned char)(filesize);
        bmpfileheader[3] = (unsigned char)(filesize>>8);
        bmpfileheader[4] = (unsigned char)(filesize>>16);
        bmpfileheader[5] = (unsigned char)(filesize>>24);

        // DIB Header (40 bytes)
        unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};

        fwrite(bmpfileheader, 1, 14, f);
        fwrite(bmpinfoheader, 1, 40, f);
        // Write 3 bytes of data
        unsigned char data[3] = {0, 0, 0};
        fwrite(data, 1, 3, f);
        fclose(f);
    }
    return 0;
}
void SDL_FreeSurface(SDL_Surface* surface) {}
SDL_bool SDL_SetHint(const char* name, const char* value) { return SDL_TRUE; }
}
