
//{{BLOCK(imagesICE)

//======================================================================
//
//	imagesICE, 256x512@4, 
//	+ palette 256 entries, not compressed
//	+ 40 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x64 
//	Total size: 512 + 1280 + 4096 = 5888
//
//	Time-stamp: 2017-12-04, 13:49:12
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_IMAGESICE_H
#define GRIT_IMAGESICE_H

#define imagesICETilesLen 1280
extern const unsigned short imagesICETiles[640];

#define imagesICEMapLen 4096
extern const unsigned short imagesICEMap[2048];

#define imagesICEPalLen 512
extern const unsigned short imagesICEPal[256];

#endif // GRIT_IMAGESICE_H

//}}BLOCK(imagesICE)
