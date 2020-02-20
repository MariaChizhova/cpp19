#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "assert.h"
#include "bmp.h"

int main(int argc, char **argv) {
    assert(argc == 8);
    if (!strcmp(argv[1], "crop-rotate")) {
        BMP *bmp = malloc(sizeof(BMP));
        bmp->image = NULL;
        assert((atoi(argv[4]) >= 0) || (atoi(argv[5]) >= 0));
        load_bmp(argv[2], bmp);
        crop(bmp, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
        rotate(bmp);
        save_bmp(argv[3], bmp);

        if (bmp->image)
            free(bmp->image);
        free(bmp);
    } else {
        assert("Unknown arguments");
    }
    return 0;
}
