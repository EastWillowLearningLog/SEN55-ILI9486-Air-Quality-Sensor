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
SDL_Surface* SDL_CreateRGBSurfaceWithFormatFrom(void* pixels, int width, int height, int depth, int pitch, uint32_t format) {
    SDL_Surface* s = new SDL_Surface();
    s->w = width;
    s->h = height;
    s->pitch = pitch;
    s->pixels = pixels;
    s->format = new SDL_PixelFormat();
    s->format->format = format;
    return s;
}

int SDL_SaveBMP(SDL_Surface* surface, const char* file) {
    if (!surface || !surface->pixels) return -1;

    printf("Mock SDL_SaveBMP writing real BMP to %s\n", file);
    FILE* f = fopen(file, "wb");
    if (!f) return -1;

    int w = surface->w;
    int h = surface->h;

    // Check format (we expect RGB24 from conversion, or RGB565 from raw)
    // Writing 24-bit BMP

    int row_padded = (w * 3 + 3) & (~3);
    int size_data = row_padded * h;
    int size_file = 14 + 40 + size_data; // Headers + Data

    // BMP Header
    uint8_t bmp_pad[3] = {0,0,0};
    uint8_t header[14] = {
        'B', 'M',
        (uint8_t)(size_file), (uint8_t)(size_file >> 8), (uint8_t)(size_file >> 16), (uint8_t)(size_file >> 24),
        0, 0, 0, 0,
        54, 0, 0, 0 // Offset to data
    };
    fwrite(header, 1, 14, f);

    // DIB Header (BITMAPINFOHEADER)
    uint8_t dib[40] = {
        40, 0, 0, 0,
        (uint8_t)(w), (uint8_t)(w >> 8), (uint8_t)(w >> 16), (uint8_t)(w >> 24),
        (uint8_t)(h), (uint8_t)(h >> 8), (uint8_t)(h >> 16), (uint8_t)(h >> 24), // Height usually negative for top-down, but let's assume bottom-up or flip? SDL usually bottom-up.
        1, 0, // Planes
        24, 0, // BPP
        0, 0, 0, 0, // Compression
        (uint8_t)(size_data), (uint8_t)(size_data >> 8), (uint8_t)(size_data >> 16), (uint8_t)(size_data >> 24),
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    // Adjust height for top-down if needed. SDL pixels are usually top-left origin.
    // BMP is bottom-left origin. So we should write rows in reverse or use negative height.
    // Using negative height implies V5 header usually? No, BITMAPINFOHEADER supports it.
    // Let's use negative height to flip it correctly.
    int32_t neg_h = -h;
    dib[8] = (uint8_t)(neg_h);
    dib[9] = (uint8_t)(neg_h >> 8);
    dib[10] = (uint8_t)(neg_h >> 16);
    dib[11] = (uint8_t)(neg_h >> 24);

    fwrite(dib, 1, 40, f);

    uint8_t* pixels = (uint8_t*)surface->pixels;
    bool isRGB888 = (surface->format->format == SDL_PIXELFORMAT_RGB24);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            uint8_t r, g, b;
            if (isRGB888) {
                // RGB24: R, G, B
                int idx = (y * w + x) * 3;
                r = pixels[idx];
                g = pixels[idx+1];
                b = pixels[idx+2];
            } else {
                // Assume RGB565
                uint16_t p = ((uint16_t*)pixels)[y * w + x];
                // R5 G6 B5
                r = (p & 0xF800) >> 8;
                g = (p & 0x07E0) >> 3;
                b = (p & 0x001F) << 3;
                // Expand
                r |= (r >> 5);
                g |= (g >> 6);
                b |= (b >> 5);
            }
            // BMP uses BGR
            uint8_t bgr[3] = {b, g, r};
            fwrite(bgr, 1, 3, f);
        }
        fwrite(bmp_pad, 1, (4 - (w * 3) % 4) % 4, f);
    }

    fclose(f);
    return 0;
}

void SDL_FreeSurface(SDL_Surface* surface) {
    if (surface) {
        if (surface->format) delete surface->format;
        // Don't delete pixels if they were just pointing to external buffer?
        // CreateRGBSurfaceWithFormatFrom doesn't own pixels.
        // But ConvertSurfaceFormat DOES own pixels.
        // For simplicity in stub, leak memory or add flags.
        if (surface->flags & 1) delete[] (uint8_t*)surface->pixels;
        delete surface;
    }
}

SDL_bool SDL_SetHint(const char* name, const char* value) { return SDL_TRUE; }

SDL_Surface* SDL_ConvertSurfaceFormat(SDL_Surface* src, uint32_t pixel_format, uint32_t flags) {
    if (!src) return NULL;
    // We only support converting RGB565 to RGB24 for this specific test case
    if (src->format->format == SDL_PIXELFORMAT_RGB565 && pixel_format == SDL_PIXELFORMAT_RGB24) {
        SDL_Surface* dest = new SDL_Surface();
        dest->w = src->w;
        dest->h = src->h;
        dest->pitch = src->w * 3;
        dest->format = new SDL_PixelFormat();
        dest->format->format = pixel_format;
        dest->flags = 1; // Mark as owning pixels

        uint8_t* new_pixels = new uint8_t[src->w * src->h * 3];
        dest->pixels = new_pixels;

        uint16_t* src_p = (uint16_t*)src->pixels;
        for (int i = 0; i < src->w * src->h; i++) {
            uint16_t p = src_p[i];
            uint8_t r = (p & 0xF800) >> 8;
            uint8_t g = (p & 0x07E0) >> 3;
            uint8_t b = (p & 0x001F) << 3;
            r |= (r >> 5);
            g |= (g >> 6);
            b |= (b >> 5);
            new_pixels[i*3] = r;
            new_pixels[i*3+1] = g;
            new_pixels[i*3+2] = b;
        }
        return dest;
    }
    return NULL;
}
}
