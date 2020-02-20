#include <assert.h>
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "bmp.h"


void load_bmp(const char *filename, BMP *bmp) {
    FILE *fin = fopen(filename, "rb");
    fread(&bmp->header, sizeof(BMPheader), 1, fin);
    bmp->w = (bmp->header.biWidth * 3 + 3) & (-4);
    bmp->h = bmp->header.biHeight;
    bmp->image = malloc(bmp->w * bmp->h);
    fread(bmp->image, bmp->w * bmp->h, 1, fin);
    fclose(fin);
}


void save_bmp(const char *filename, BMP *bmp) {
    FILE *fout = fopen(filename, "wb");
    fwrite(&bmp->header, sizeof(BMPheader), 1, fout);
    fwrite(bmp->image, bmp->w * bmp->h, 1, fout);
    fclose(fout);
}


void update(BMP *bmp, int w, int h) {
    bmp->w = (w * 3 + 3) & (-4);
    bmp->h = h;
    bmp->header.bfSize = bmp->w * bmp->h + sizeof(BMPheader);;
    bmp->header.biWidth = w;
    bmp->header.biHeight = h;
    bmp->header.biSizeImage = bmp->w * bmp->h;
    bmp->image = malloc(bmp->w * bmp->h);
    memset(bmp->image, 0, bmp->w * bmp->h);
}


void crop(BMP *bmp, int x, int y, int w, int h) {
    assert(x >= 0 && x + w <= bmp->header.biWidth && y >= 0 && y + h <= bmp->header.biHeight);
    BMP *bmp_copy = malloc(sizeof(BMP));
    memcpy(bmp_copy, bmp, sizeof(BMPheader));
    update(bmp_copy, w, h);

    for (int i = bmp->h - h - y; i < bmp->h - y; i++) {
        memcpy(&bmp_copy->image[bmp_copy->w * (i - bmp->h + h + y)], &bmp->image[bmp->w * i + x * 3], w * 3);
    }

    free(bmp->image);
    memcpy(bmp, bmp_copy, sizeof(BMP));
    free(bmp_copy);
}

void rotate(BMP *bmp) {
    BMP *bmp_copy = malloc(sizeof(BMP));
    memcpy(bmp_copy, bmp, sizeof(BMPheader));

    update(bmp_copy, bmp->header.biHeight, bmp->header.biWidth);

    for (int i = 0; i < bmp->header.biHeight; i++) {
        for (int j = 0; j < bmp->header.biWidth; j++) {
            memcpy(&bmp_copy->image[bmp_copy->w * (bmp->header.biWidth - j - 1) + 3 * i],
                   &bmp->image[bmp->w * i + 3 * j], 3);
        }
    }

    free(bmp->image);
    memcpy(bmp, bmp_copy, sizeof(BMP));
    free(bmp_copy);
}