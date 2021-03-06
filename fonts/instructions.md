Some 8x8 fonts that can be used with the bitmap module.

Raster Fonts
============

`bmp.h` has support for drawing text using raster fonts from any of the 
supported file types.

The characters in the bitmap must be arranged like this:
```
 !"#$%&'()*+,-./
0123456789:;<=>?
@ABCDEFGHIJKLMNO
PQRSTUVWXYZ[\]^_
`abcdefghijklmno
pqrstuvwxyz{|}~ 
```

The characters are in ASCII sequence, without the first 32 control characters. 
The pixel width and hight of the individual characters is calculated by dividing
the width and height of the bitmap by 16 and 6 respectively.

`font.gif` is an example of an 8x8 font that can be used in this way:

![sample font image](font.gif)

The image is 128x48 pixels, so the individual characters are 8x8 pixels.
(128/16=8 and 48/6=8)
 
Usage:

    /* Create a */
    BmFont *font = bm_make_ras_font("font.gif", 7);
    if(!font) {
        fprintf(stderr, "error: %s\n", "font.gif");
        return 1;
    }	
    
    /* Then set the font on your Bitmap object */
    bm_set_font(b, font);
    
    /* Then free the font when you're done with it */
    bm_free_ras_font(font);

XBM Fonts
=========

The XBM fonts in this directory can be compiled directly into your executable,
so that you don't have to distribute any additonal files.

You create a `BmFont` object with the `bm_make_xbm_font()` function, then use
`bm_set_font()` to start using the font

I basically drew the font.xbm files from the fonts at
<http://damieng.com/blog/2011/02/20/typography-in-8-bits-system-fonts>. The
Apple ][ font turned out to be the nicest normal font. The bold font was
inspired by Commodore 64. I later added some others for a bit of variety.

The normal.xbm file actually contains the default font available through the
`bm_reset_font()` function, but it is included here for completeness/if you
want to build a font off of it.

Usage:

    /* Include the XBM files in your project. */
    #include "fonts/bold.xbm"
    #include "fonts/circuit.xbm"
    #include "fonts/hand.xbm"
    #include "fonts/normal.xbm"
    #include "fonts/small.xbm"
    #include "fonts/smallinv.xbm"
    #include "fonts/thick.xbm"
    
    /* Create the BmFont object from the XBM's bytes */
    BmFont *bfont_normal = bm_make_xbm_font(normal_bits, 6);
    BmFont *bfont_bold = bm_make_xbm_font(bold_bits, 8);
    BmFont *bfont_circuit = bm_make_xbm_font(circuit_bits, 7);
    BmFont *bfont_hand = bm_make_xbm_font(hand_bits, 7);
    BmFont *bfont_small = bm_make_xbm_font(small_bits, 5);
    BmFont *bfont_smallinv = bm_make_xbm_font(smallinv_bits, 7);
    BmFont *bfont_thick = bm_make_xbm_font(thick_bits, 6);
    
    /* Then set the font on your Bitmap object */
    bm_set_font(Bitmap *, BmFont *);
    
    /* Then free the fonts when you're done with them */
    bm_free_xbm_font(bfont_normal);
    bm_free_xbm_font(bfont_bold);
    bm_free_xbm_font(bfont_circuit);
    bm_free_xbm_font(bfont_hand);
    bm_free_xbm_font(bfont_small);
    bm_free_xbm_font(bfont_smallinv);
    bm_free_xbm_font(bfont_thick);

