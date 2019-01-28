/*$Id: qx_alloc.h,v 1.3 2007/04/04 02:15:14 liiton Exp $*/
/*******************************************************
\Author:	Qingxiong Yang (liiton)
\Function:	Memory allocation.
********************************************************/
#ifndef QX_ALLOC_H
#define QX_ALLOC_H
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#define QX_DEF_PADDING 128
template <typename T> static inline T**qx_alloc2(int r,int c)
{
	T *a,**p;
	int i;
	a=new T [sizeof(T)*r*c];
    if(a == NULL)
        throw std::bad_alloc();

	p=new T* [sizeof(T*)*r];
    if(p == NULL)
        throw std::bad_alloc();

	for(i=0;i<r;i++) 
        p[i]= &a[i*c];
	return(p);
}
template <typename T> static inline void qx_free2(T**p)
{
	if(p!=NULL)
	{
		delete[] p[0];
		delete[] p;
	}
}

template <typename T> static inline T***qx_alloc3(int n,int r,int c)
{
  	T *a,**p,***pp;
    int i,j,rc=r*c;
	a=new T [sizeof(T)*n*rc];
    if(a == NULL)
        throw std::bad_alloc();
    p=new T* [sizeof(T*)*n*r];
    if(p == NULL)
        throw std::bad_alloc();
    pp=new T** [sizeof(T**)*n];
    if(pp == NULL)
        throw std::bad_alloc();

    for(i=0;i<n;i++) 
        for(j=0;j<r;j++) 
            p[i*r+j]=&a[i*rc+j*c];
    for(i=0;i<n;i++) 
        pp[i]=&p[i*r];
    return(pp);
}

template <typename T> static inline void qx_free3(T***p)
{
	if(p!=NULL)
	{
		delete[] p[0][0];
		delete[] p[0];
		delete[] p;
	}
}

inline double**qx_allocd(int r,int c,int padding=QX_DEF_PADDING)
{
	double *a,**p;
	a=(double*) malloc(sizeof(double)*(r*c+padding));
	if(a==NULL) {printf("qx_allocd() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	p=(double**) malloc(sizeof(double*)*r);
	for(int i=0;i<r;i++) p[i]= &a[i*c];
	return(p);
}
inline void qx_freed(double **p)
{
	if(p!=NULL)
	{
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline void qx_freed_1(double*p)
{
	if(p!=NULL)
	{
		delete [] p;
		p=NULL;
	}
}
inline double *** qx_allocd_3(int n,int r,int c,int padding=QX_DEF_PADDING)
{
	double *a,**p,***pp;
    int rc=r*c;
    int i,j;
	a=(double*) malloc(sizeof(double)*(n*rc+padding));
	if(a==NULL) {printf("qx_allocd_3() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(double**) malloc(sizeof(double*)*n*r);
    pp=(double***) malloc(sizeof(double**)*n);
    for(i=0;i<n;i++) 
        for(j=0;j<r;j++) 
            p[i*r+j]=&a[i*rc+j*c];
    for(i=0;i<n;i++) 
        pp[i]=&p[i*r];
    return(pp);
}
inline void qx_freed_3(double ***p)
{
	if(p!=NULL)
	{
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline double**** qx_allocd_4(int t,int n,int r,int c,int padding=QX_DEF_PADDING)
{
	double *a,**p,***pp,****ppp;
    int nrc=n*r*c,nr=n*r,rc=r*c;
    int i,j,k;
	a=(double*) malloc(sizeof(double)*(t*nrc+padding));
	if(a==NULL) {printf("qx_allocd_4() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(double**) malloc(sizeof(double*)*t*nr);
    pp=(double***) malloc(sizeof(double**)*t*n);
    ppp=(double****) malloc(sizeof(double***)*t);
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            for(j=0;j<r;j++)
                p[k*nr+i*r+j]=&a[k*nrc+i*rc+j*c];
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            pp[k*n+i]=&p[k*nr+i*r];
    for(k=0;k<t;k++)
        ppp[k]=&pp[k*n];
    return(ppp);
}
inline void qx_freed_4(double ****p)
{
	
	if(p!=NULL)
	{
		free(p[0][0][0]);
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline unsigned char** qx_allocu(int r,int c,int padding=QX_DEF_PADDING)
{
	unsigned char *a,**p;
	a=(unsigned char*) malloc(sizeof(unsigned char)*(r*c+padding));
	if(a==NULL) {printf("qx_allocu() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	p=(unsigned char**) malloc(sizeof(unsigned char*)*r);
	for(int i=0;i<r;i++) p[i]= &a[i*c];
	return(p);
}
inline void qx_freeu(unsigned char **p)
{
	if(p!=NULL)
	{
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline void qx_freeu_1(unsigned char*p)
{
	if(p!=NULL)
	{
		delete [] p;
		p=NULL;
	}
}
inline unsigned char *** qx_allocu_3(int n,int r,int c,int padding=QX_DEF_PADDING)
{
	unsigned char *a,**p,***pp;
    int rc=r*c;
    int i,j;
	a=(unsigned char*) malloc(sizeof(unsigned char )*(n*rc+padding));
	if(a==NULL) {printf("qx_allocu_3() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(unsigned char**) malloc(sizeof(unsigned char*)*n*r);
    pp=(unsigned char***) malloc(sizeof(unsigned char**)*n);
    for(i=0;i<n;i++) 
        for(j=0;j<r;j++) 
            p[i*r+j]=&a[i*rc+j*c];
    for(i=0;i<n;i++) 
        pp[i]=&p[i*r];
    return(pp);
}
inline void qx_freeu_3(unsigned char ***p)
{
	if(p!=NULL)
	{
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline unsigned char**** qx_allocu_4(int t,int n,int r,int c,int padding=QX_DEF_PADDING)
{
	unsigned char *a,**p,***pp,****ppp;
    int nrc=n*r*c,nr=n*r,rc=r*c;
    int i,j,k;
	a=(unsigned char*) malloc(sizeof(unsigned char)*(t*nrc+padding));
	if(a==NULL) {printf("qx_allocu_4() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(unsigned char**) malloc(sizeof(unsigned char*)*t*nr);
    pp=(unsigned char***) malloc(sizeof(unsigned char**)*t*n);
    ppp=(unsigned char****) malloc(sizeof(unsigned char***)*t);
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            for(j=0;j<r;j++)
                p[k*nr+i*r+j]=&a[k*nrc+i*rc+j*c];
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            pp[k*n+i]=&p[k*nr+i*r];
    for(k=0;k<t;k++)
        ppp[k]=&pp[k*n];
    return(ppp);
}
inline void qx_freeu_4(unsigned char ****p)
{
	if(p!=NULL)
	{
		free(p[0][0][0]);
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}

inline unsigned int** qx_allocui(int r,int c,int padding=QX_DEF_PADDING)
{
	unsigned int *a,**p;
	a=(unsigned int*) malloc(sizeof(unsigned int)*(r*c+padding));
	if(a==NULL) {printf("qx_allocus() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	p=(unsigned int**) malloc(sizeof(unsigned int*)*r);
	for(int i=0;i<r;i++) p[i]= &a[i*c];
	return(p);
}
inline void qx_freeui(unsigned int **p)
{
	if(p!=NULL)
	{
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline unsigned short** qx_allocus(int r,int c,int padding=QX_DEF_PADDING)
{
	unsigned short *a,**p;
	a=(unsigned short*) malloc(sizeof(unsigned short)*(r*c+padding));
	if(a==NULL) {printf("qx_allocus() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	p=(unsigned short**) malloc(sizeof(unsigned short*)*r);
	for(int i=0;i<r;i++) p[i]= &a[i*c];
	return(p);
}
inline void qx_freeus(unsigned short **p)
{
	if(p!=NULL)
	{
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline unsigned short *** qx_allocus_3(int n,int r,int c,int padding=QX_DEF_PADDING)
{
	unsigned short *a,**p,***pp;
    int rc=r*c;
    int i,j;
	a=(unsigned short*) malloc(sizeof(unsigned short )*(n*rc+padding));
	if(a==NULL) {printf("qx_allocus_3() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(unsigned short**) malloc(sizeof(unsigned short*)*n*r);
    pp=(unsigned short***) malloc(sizeof(unsigned short**)*n);
    for(i=0;i<n;i++) 
        for(j=0;j<r;j++) 
            p[i*r+j]=&a[i*rc+j*c];
    for(i=0;i<n;i++) 
        pp[i]=&p[i*r];
    return(pp);
}
inline void qx_freeus_3(unsigned short ***p)
{
	if(p!=NULL)
	{
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline char** qx_allocc(int r,int c,int padding=QX_DEF_PADDING)
{
	char *a,**p;
	a=(char*) malloc(sizeof(char)*(r*c+padding));
	if(a==NULL) {printf("qx_allocc() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	p=(char**) malloc(sizeof(char*)*r);
	for(int i=0;i<r;i++) p[i]= &a[i*c];
	return(p);
}
inline void qx_freec(char **p)
{
	if(p!=NULL)
	{
		free(p[0]);
		free(p);
		p=NULL;
	}
}

inline char *** qx_allocc_3(int n,int r,int c,int padding=QX_DEF_PADDING)
{
	char *a,**p,***pp;
    int rc=r*c;
    int i,j;
	a=(char*) malloc(sizeof(char)*(n*rc+padding));
	if(a==NULL) {printf("qx_allocc_3() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(char**) malloc(sizeof(char*)*n*r);
    pp=(char***) malloc(sizeof(char**)*n);
    for(i=0;i<n;i++) 
        for(j=0;j<r;j++) 
            p[i*r+j]=&a[i*rc+j*c];
    for(i=0;i<n;i++) 
        pp[i]=&p[i*r];
    return(pp);
}
inline void qx_freec_3(char ***p)
{
	if(p!=NULL)
	{
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline char**** qx_allocc_4(int t,int n,int r,int c,int padding=QX_DEF_PADDING)
{
	char *a,**p,***pp,****ppp;
    int nrc=n*r*c,nr=n*r,rc=r*c;
    char i,j,k;
	a=(char*) malloc(sizeof(char)*(t*nrc+padding));
	if(a==NULL) {printf("qx_allocs_4() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(char**) malloc(sizeof(char*)*t*nr);
    pp=(char***) malloc(sizeof(char**)*t*n);
    ppp=(char****) malloc(sizeof(char***)*t);
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            for(j=0;j<r;j++)
                p[k*nr+i*r+j]=&a[k*nrc+i*rc+j*c];
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            pp[k*n+i]=&p[k*nr+i*r];
    for(k=0;k<t;k++)
        ppp[k]=&pp[k*n];
    return(ppp);
}
inline void qx_freec_4(char ****p)
{
	if(p!=NULL)
	{
		free(p[0][0][0]);
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline short** qx_allocs(int r,int c,int padding=QX_DEF_PADDING)
{
	short *a,**p;
	a=(short*) malloc(sizeof(short)*(r*c+padding));
	if(a==NULL) {printf("qx_allocs() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	p=(short**) malloc(sizeof(short*)*r);
	for(int i=0;i<r;i++) p[i]= &a[i*c];
	return(p);
}
inline void qx_frees(short **p)
{
	if(p!=NULL)
	{
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline short*** qx_allocs_3(int n,int r,int c,int padding=QX_DEF_PADDING)
{
	short *a,**p,***pp;
    int rc=r*c;
    short i,j;
	a=(short*) malloc(sizeof(short)*(n*rc+padding));
	if(a==NULL)
	{
		printf("qx_allocs_3() fail, Memory is too huge, fail.\n"); 
		getchar(); exit(0); 
	
	}
    p=(short**) malloc(sizeof(short*)*n*r);
    pp=(short***) malloc(sizeof(short**)*n);
    for(i=0;i<n;i++) 
        for(j=0;j<r;j++) 
            p[i*r+j]=&a[i*rc+j*c];
    for(i=0;i<n;i++) 
        pp[i]=&p[i*r];
    return(pp);
}
inline void qx_frees_3(short ***p)
{
	if(p!=NULL)
	{
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline short**** qx_allocs_4(int t,int n,int r,int c,int padding=QX_DEF_PADDING)
{
	short *a,**p,***pp,****ppp;
    int nrc=n*r*c,nr=n*r,rc=r*c;
    short i,j,k;
	a=(short*) malloc(sizeof(short)*(t*nrc+padding));
	if(a==NULL) {printf("qx_allocs_4() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(short**) malloc(sizeof(short*)*t*nr);
    pp=(short***) malloc(sizeof(short**)*t*n);
    ppp=(short****) malloc(sizeof(short***)*t);
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            for(j=0;j<r;j++)
                p[k*nr+i*r+j]=&a[k*nrc+i*rc+j*c];
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            pp[k*n+i]=&p[k*nr+i*r];
    for(k=0;k<t;k++)
        ppp[k]=&pp[k*n];
    return(ppp);
}
inline void qx_frees_4(short ****p)
{
	if(p!=NULL)
	{
		free(p[0][0][0]);
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline void qx_freef_1(float*p)
{
	if(p!=NULL)
	{
		delete [] p;
		p=NULL;
	}
}
inline float** qx_allocf(int r,int c,int padding=QX_DEF_PADDING)
{
	float *a,**p;
	a=(float*) malloc(sizeof(float)*(r*c+padding));
	if(a==NULL) {printf("qx_allocf() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	p=(float**) malloc(sizeof(float*)*r);
	for(int i=0;i<r;i++) p[i]= &a[i*c];
	return(p);
}
inline void qx_freef(float **p)
{
	if(p!=NULL)
	{
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline float *** qx_allocf_3(int n,int r,int c,int padding=QX_DEF_PADDING)
{
	float *a,**p,***pp;
    int rc=r*c;
    int i,j;
	a=(float*) malloc(sizeof(float)*(n*rc+padding));
	if(a==NULL) {printf("qx_allocf_3() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(float**) malloc(sizeof(float*)*n*r);
    pp=(float***) malloc(sizeof(float**)*n);
    for(i=0;i<n;i++) 
        for(j=0;j<r;j++) 
            p[i*r+j]=&a[i*rc+j*c];
    for(i=0;i<n;i++) 
        pp[i]=&p[i*r];
    return(pp);
}
inline void qx_freef_3(float ***p)
{
	if(p!=NULL)
	{
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline float**** qx_allocf_4(int t,int n,int r,int c,int padding=QX_DEF_PADDING)
{
	float *a,**p,***pp,****ppp;
    int nrc=n*r*c,nr=n*r,rc=r*c;
    int i,j,k;
	a=(float*) malloc(sizeof(float)*(t*nrc+padding));
	if(a==NULL) {printf("qx_allocf_4() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(float**) malloc(sizeof(float*)*t*nr);
    pp=(float***) malloc(sizeof(float**)*t*n);
    ppp=(float****) malloc(sizeof(float***)*t);
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            for(j=0;j<r;j++)
                p[k*nr+i*r+j]=&a[k*nrc+i*rc+j*c];
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            pp[k*n+i]=&p[k*nr+i*r];
    for(k=0;k<t;k++)
        ppp[k]=&pp[k*n];
    return(ppp);
}
inline void qx_freef_4(float ****p)
{
	if(p!=NULL)
	{
		free(p[0][0][0]);
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline int** qx_alloci(int r,int c,int padding=QX_DEF_PADDING)
{
	int *a,**p;
	a=(int*) malloc(sizeof(int)*(r*c+padding));
	if(a==NULL) {printf("qx_alloci() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	p=(int**) malloc(sizeof(int*)*r);
	for(int i=0;i<r;i++) p[i]= &a[i*c];
	return(p);
}
inline void qx_freei(int **p)
{
	if(p!=NULL)
	{
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline void qx_freei_1(int*p)
{
	if(p!=NULL)
	{
		delete [] p;
		p=NULL;
	}
}
inline int*** qx_alloci_3(int n,int r,int c,int padding=QX_DEF_PADDING)
{
	int *a,**p,***pp;
    int rc=r*c;
    int i,j;
	a=(int*) malloc(sizeof(int)*(n*rc+padding));
	if(a==NULL) {printf("qx_alloci_3() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(int**) malloc(sizeof(int*)*n*r);
    pp=(int***) malloc(sizeof(int**)*n);
    for(i=0;i<n;i++) 
        for(j=0;j<r;j++) 
            p[i*r+j]=&a[i*rc+j*c];
    for(i=0;i<n;i++) 
        pp[i]=&p[i*r];
    return(pp);
}
inline void qx_freei_3(int ***p)
{
	if(p!=NULL)
	{
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}
inline int**** qx_alloci_4(int t,int n,int r,int c,int padding=QX_DEF_PADDING)
{
	int *a,**p,***pp,****ppp;
    int nrc=n*r*c,nr=n*r,rc=r*c;
    int i,j,k;
	a=(int*) malloc(sizeof(int)*(t*nrc+padding));
	if(a==NULL) {printf("qx_alloci_4() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
    p=(int**) malloc(sizeof(int*)*t*nr);
    pp=(int***) malloc(sizeof(int**)*t*n);
    ppp=(int****) malloc(sizeof(int***)*t);
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            for(j=0;j<r;j++)
                p[k*nr+i*r+j]=&a[k*nrc+i*rc+j*c];
    for(k=0;k<t;k++)
        for(i=0;i<n;i++)
            pp[k*n+i]=&p[k*nr+i*r];
    for(k=0;k<t;k++)
        ppp[k]=&pp[k*n];
    return(ppp);
}
inline void qx_freei_4(int ****p)
{
	if(p!=NULL)
	{
		free(p[0][0][0]);
		free(p[0][0]);
		free(p[0]);
		free(p);
		p=NULL;
	}
}

inline long int** qx_allocli(int r,int c,int padding=QX_DEF_PADDING)
{
	long int *a,**p;
	a=(long int*) malloc(sizeof(long int)*(r*c+padding));
	if(a==NULL) {printf("qx_allocli() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	p=(long int**) malloc(sizeof(long int*)*r);
	for(int i=0;i<r;i++) p[i]= &a[i*c];
	return(p);
}
inline void qx_freeli(long int **p)
{
	if(p!=NULL)
	{
		free(p[0]);
		free(p);
		p=NULL;
	}
}

inline unsigned char***qx_allocu_3_special(int n,int r,int c)
{
	unsigned char***a=new unsigned char**[n];
	for(int i=0;i<n;i++)
	{
		a[i]=qx_allocu(r,c);
		if(a[i]==NULL) {printf("qx_allocu_3_special() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	}
    return(a);
}
inline void qx_freeu_3_special(unsigned char***p,int n)
{
	if(p!=NULL)
	{
		for(int i=0;i<n;i++)
		{
			qx_freeu(p[i]);
			p[i]=NULL;
		}
		delete [] p; p=NULL;
	}
}
inline short***qx_allocs_3_special(int n,int r,int c)
{
	short***a=new short**[n];
	for(int i=0;i<n;i++)
	{
		a[i]=qx_allocs(r,c);
		if(a[i]==NULL) {printf("qx_allocu_3_special() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	}
    return(a);
}
inline void qx_frees_3_special(short***p,int n)
{
	if(p!=NULL)
	{
		for(int i=0;i<n;i++)
		{
			qx_frees(p[i]);
			p[i]=NULL;
		}
		delete [] p; p=NULL;
	}
}
inline short****qx_allocs_4_special(int t,int n,int r,int c)
{
	short****a=new short***[t];
	for(int i=0;i<t;i++)
	{
		//printf("[%d] ",i);
		a[i]=qx_allocs_3(n,r,c);
		if(a[i]==NULL) {printf("qx_allocs_4_special() fail, Memory is too huge, fail.\n"); getchar(); exit(0); }
	}
    return(a);
}
inline void qx_frees_4_special(short****p,int n)
{
	if(p!=NULL)
	{
		for(int i=0;i<n;i++)
		{
			qx_frees_3(p[i]);
			p[i]=NULL;
		}
		delete [] p; p=NULL;
	}
}
#endif
