/*$Id: ppm.cpp,v 1.23 2007/04/04 02:15:14 liiton Exp $*/
#include "basic.h"
#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LEN_MAX	256


/*extended function*/
int qx_image_size(const char* filename, int &h, int &w)
{
    FILE * file_in; int nr_channel;
    char line[LEN_MAX];
    int	p_idx;
    unsigned char *image=NULL;
    file_in=fopen(filename,"rb");
    //fopen_s(&file_in,filename,"rb");
    if(!file_in)
    {
        printf("Please check input filename: %s\n",filename);
        getchar();
        exit(0);
    }
    if(fgetc(file_in)=='P')
        fscanf(file_in,"%d\n",&p_idx);
        //fscanf_s(file_in,"%d\n",&p_idx);
    else
    {
        printf("Bad	header in ppm file.\n");
        getchar();
        exit(1);
    }
    while(fgets(line,LEN_MAX,file_in)!=NULL)
    {
        if(line[0]=='#') continue;
        else
        {
            //sscanf_s(line, "%d %d\n",	&w,	&h);
            sscanf(line, "%d %d\n",	&w,	&h);
            if(p_idx==9)
            {
              //fscanf_s(file_in,"%d\n",&nr_channel);
              fscanf(file_in,"%d\n",&nr_channel);
            }
            else if(p_idx==5||p_idx==2||p_idx==7) nr_channel=1;
            else if(p_idx==6||p_idx==3||p_idx==8) nr_channel=3;
            break;
        }
    }
    fclose(file_in);
    return(nr_channel);
}

int qx_loadimage(const char* filename,unsigned char *image,int h,int w,int *nr_channel)
{
	FILE * file_in; int nrc;
	char line[LEN_MAX];
	int	i; int imax,hc,wc;	
	unsigned char *image_=image;
    file_in=fopen(filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		exit(0);
	}
	if(fgetc(file_in)=='P') 
        fscanf(file_in,"%d\n",&i);
	else
	{
		printf("Bad	header in ppm file.\n");
		exit(1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{	
            sscanf(line, "%d %d\n",&wc,&hc);
			break;
		}
	}
	char str_tmp[100];
	switch (i)
	{
		case 5:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=1;
			memset(image,0,sizeof(unsigned char)*h*w);
			fread(image,sizeof(unsigned char),h*w,file_in);
			break;
		case 6:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=3;
			memset(image,0,sizeof(unsigned char)*h*w*3);
			fread(image,sizeof(unsigned char),h*w*3,file_in);
			break;
		case 2:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			for(int y=0;y<h;y++) for(int x=0;x<w;x++)
			{
				//if(fscanf_s(file_in,"%d",&imax)!=1){printf("error in reading file.\n");getchar();exit(0);}
                fscanf(file_in,"%d",&imax);
				*image_++=imax;
			}
			break;
		case 3:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			int cr,cg,cb;
			for(int y=0;y<h;y++) for(int x=0;x<w;x++)
			{
				//if(fscanf_s(file_in,"%d%d%d",&cr,&cg,&cb)!=3){printf("error in reading file.\n");getchar();exit(0);}
                fscanf(file_in,"%d%d%d",&cr,&cg,&cb);
                //fscanf_s(file_in,"%d%d%d",&cr,&cg,&cb);
				*image_++=cr; *image_++=cg; *image_++=cb; 
			}
			break;
		case 9:
			fgets(str_tmp,100,file_in);
			nrc=atoi(str_tmp);
			//fscanf_s(file_in,"%d\n",&nrc);
			if(nr_channel!=NULL) (*nr_channel)=nrc;
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			fread(image,sizeof(unsigned char),h*w*nrc,file_in);
			break;
		default:
			printf("Can not open image [%s]!!\n",filename);
			break;					
	}
	fclose(file_in);
	return (0);
}

void qx_saveimage(const char* filename,unsigned char *image,int h,int w,int channel)
{
    FILE* file_out; unsigned char maxx=255;
    //fopen_s(&file_out,filename,"wb");
    file_out=fopen(filename,"wb");
    if(channel==1) fprintf(file_out,"P5\n%d %d\n%d\n",w,h,maxx);
    //else if(channel==3) fprintf(file_out,"P6\n%d %d\n%d\n",w,h,maxx);
    else if(channel==3) fprintf(file_out,"P6\n%d %d\n%d\n",w,h,maxx);
    else fprintf(file_out,"P9\n%d %d\n%d\n%d\n",w,h,channel,maxx);
    fwrite(image,sizeof(unsigned char),h*w*channel,file_out);

    fclose(file_out);
}
