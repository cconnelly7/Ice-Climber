
//{{BLOCK(mountain)

//======================================================================
//
//	mountain, 256x512@4, 
//	+ palette 256 entries, not compressed
//	+ 488 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x64 
//	Total size: 512 + 15616 + 4096 = 20224
//
//	Time-stamp: 2017-11-20, 22:14:22
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MOUNTAIN_H
#define GRIT_MOUNTAIN_H

#define mountainTilesLen 15616
extern const unsigned short mountainTiles[7808];

#define mountainMapLen 4096
extern const unsigned short mountainMap[2048];

#define mountainPalLen 512
extern const unsigned short mountainPal[256];

#endif // GRIT_MOUNTAIN_H

//}}BLOCK(mountain)
