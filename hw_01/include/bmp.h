#pragma once

#include "stdint.h"

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    int bfSize;
    int bfReserved;
    int bfOffBits;
    int biSize;
    int biWidth;
    int biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} BMPheader;
#pragma pack(pop)


typedef struct {
    BMPheader header;
    unsigned char *image;
    int w, h;
} BMP;


void load_bmp(const char *filename, BMP *bmp);

void save_bmp(const char *filename, BMP *bmp);

void update(BMP *bmp, int w, int h);

void crop(BMP *bmp, int x, int y, int w, int h);

void rotate(BMP *bmp);
