// Seven feedback differences: r29/r30 tile walker and destination-X allocation swapped.
#include "challenge/gap_1D590.h"
extern u8 lbl_803CBBC0;

// .text:0x0001D590 size:0x104
// Copy selected tiles into a cleared image, then publish it to the GPU cache.
void fn_1_1D590(ChallengeTileImage* source, ChallengeTileImage* destination, u8* tiles, s32 tileWidth, s32 tileHeight) {
    s32 row;
    s32 column;
    s32 rows;
    s32 columns;
    memset(destination->pixels, 0, destination->width * destination->height);
    rows = destination->height / tileHeight;
    columns = destination->width / tileWidth;
    for (row = 0; row < rows; row++) {
        for (column = 0; column < columns; column++) {
            if (column & lbl_803CBBC0) {
                s32 tile = tiles[column + row * columns];
                fn_80023F0C(source, destination, tileWidth * (tile % columns), tileHeight * (tile / columns),
                            tileWidth, tileHeight, column * tileWidth, row * tileHeight);
            }
        }
    }
    DCStoreRange(destination->pixels, destination->width * destination->height);
}
