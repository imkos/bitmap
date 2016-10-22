/* -- Wikipedia XPM3 examples ----------------------------- */

/* XPM */
static char * XFACE[] = {
/* <Values> */
/* <width/cols> <height/rows> <colors> <char on pixel>*/
"48 4 2 1",
/* <Colors> */
"a c #ffffff",
"b c #000000",
/* <Pixels> */
"abaabaababaaabaabababaabaabaababaabaaababaabaaab",
"abaabaababaaabaabababaabaabaababaabaaababaabaaab",
"abaabaababaaabaabababaabaabaababaabaaababaabaaab",
"abaabaababaaabaabababaabaabaababaabaaababaabaaab"
};

/* XPM */
static char * blarg_xpm[] = {
"16 7 2 1",
"* c #000000",
". c #ffffff",
"**..*...........",
"*.*.*...........",
"**..*..**.**..**",
"*.*.*.*.*.*..*.*",
"**..*..**.*...**",
"...............*",
".............**."
};

/* -------------------------------------------------------- */

/*
https://en.wikipedia.org/wiki/X_PixMap
http://www.fileformat.info/format/xpm/egff.htm
*/

#include <stdio.h>
#include <assert.h>

#include "../bmp.h"

#define MAX_COLORS 256
#define TRANS_COLOR 1

Bitmap *from_xpm3(char *xpm[]) {
    /* Assumes the input XPM is correct, and just uses
    assertions for error checking. */
    Bitmap *b;
    int w, h, nc, cp;
    int i, j, r;
    unsigned int colors[MAX_COLORS];
    unsigned char chars[MAX_COLORS];

    r = sscanf(xpm[0], "%d %d %d %d", &w, &h, &nc, &cp);
    assert(r == 4);(void)r;
    assert(w > 0 && h > 0);
    assert(nc > 0 && nc < MAX_COLORS);
    assert(cp == 1); /* cp != 1 not supported */

    b = bm_create(w, h);
    for(i = 0; i < nc; i++) {
        char k, col[20];
        col[sizeof col - 1] = 0;
        chars[i] = xpm[i+1][0]; /* to allow spaces */
        r = sscanf(xpm[i+1] + 1, " %c %s", &k, col);
        //printf("%d '%c' '%c' \"%s\"\n", i, chars[i], k, col);
        assert(r == 2);(void)r;
        assert(k == 'c'); /* other keys not supported */
        assert(col[sizeof col - 1] == 0);
        colors[i] = bm_atoi(col);

#ifdef TRANS_COLOR
        for(j=0;col[j];j++){col[j]=tolower(col[j]);}
        if(!strcmp(col,"none")){colors[i]=TRANS_COLOR;}
#endif
    }

    for(j = 0; j < h; j++) {
        char *row = xpm[1 + nc + j];
        for(i = 0; i < w; i++) {
            assert(row[i]);
            for(r = 0; r < nc; r++) {
                if(chars[r] == row[i]) {
                    bm_set_color(b, colors[r]);
                    break;
                }
            }
            bm_putpixel(b, i, j);
        }
    }
#ifdef TRANS_COLOR
    bm_set_color(b, TRANS_COLOR);
#else
    bm_set_color(b,1);/* arb color for transparency when saving to GIF */
#endif
    return b;
}

int main(int argc, char *argv[]) {
    Bitmap *b = from_xpm3(blarg_xpm);
    bm_save(b, "blarg.gif");
    bm_free(b);
    return 1;
}