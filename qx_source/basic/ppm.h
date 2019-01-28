/*$Id: ppm.h,v 1.22 2007/04/04 02:15:14 liiton Exp $*/
/****************************************************************
\Author:	Qingxiong Yang (liiton)
\Function:	Read/Write Images.(ppm and pgm files).
*****************************************************************/
#ifndef PPM_H
#define PPM_H
#define QX_DEF_IS_PPM 1
#define QX_DEF_IS_PGM 0
/*basic function*/
/*get the size of the target image, and the properties of the image, and use the following 
4 functions to read the image data*/
int qx_image_size(const char* file_name,int &h,int &w);/*return # of channel*/
int qx_loadimage(const char* filename,unsigned char *image,int h,int w,int *nr_channel=NULL);
void qx_saveimage(const char*file_name,unsigned char*image,int h,int w,int channel);
#endif/*PPM_H*/


