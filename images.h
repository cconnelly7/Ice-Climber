
//{{BLOCK(images)

//======================================================================
//
//	images, 256x512@4, 
//	+ palette 256 entries, not compressed
//	+ 14 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x64 
//	Total size: 512 + 448 + 4096 = 5056
//
//	Time-stamp: 2017-11-26, 10:59:28
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_IMAGES_H
#define GRIT_IMAGES_H

#define imagesTilesLen 448
extern const unsigned short imagesTiles[224];

#define imagesMapLen 4096
extern const unsigned short imagesMap[2048];

#define imagesPalLen 512
extern const unsigned short imagesPal[256];

#endif // GRIT_IMAGES_H

//}}BLOCK(images)
