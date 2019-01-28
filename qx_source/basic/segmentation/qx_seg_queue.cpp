/*$Id: qx_seg_queue.cpp,v 1.1 2007/04/04 02:14:42 liiton Exp $*/
#include "qx_seg_queue.h"
#include "basic.h"
qx_segm_data::qx_segm_data()
{
	labels=NULL;
	label_2_nr_pixels=NULL;
	label_2_pixels_y=NULL;
	label_2_pixels_x=NULL;
	m_ys=NULL;
	m_xs=NULL;
}
qx_segm_data::~qx_segm_data()
{
	labels=NULL;
	label_2_nr_pixels=NULL;
	label_2_pixels_y=NULL;
	label_2_pixels_x=NULL;
	m_ys=NULL;
	m_xs=NULL;
}
int qx_segm_data::re_addressing(int h,int w)
{	
	int y,x,i,nr_pixels_curr;
	m_ys=&label_2_pixels_y[0][0];
	m_xs=&label_2_pixels_x[0][0];
	nr_pixels_curr=0;
	for(i=0;i<nr_labels;i++)
	{
		label_2_pixels_y[i]=&m_ys[nr_pixels_curr];
		label_2_pixels_x[i]=&m_xs[nr_pixels_curr];
		nr_pixels_curr+=label_2_nr_pixels[i];
	}
	memset(label_2_nr_pixels,0,sizeof(int)*nr_labels);
	nr_pixels_curr=0;
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			i=labels[y][x];
			nr_pixels_curr=label_2_nr_pixels[i];
			label_2_pixels_y[i][nr_pixels_curr]=y;
			label_2_pixels_x[i][nr_pixels_curr]=x;
			label_2_nr_pixels[i]++;
		}
	}
	//memset(label_2_nr_pixels,0,sizeof(int)*nr_labels);
	//for(y=0;y<h;y++)
	//{
	//	for(x=0;x<w;x++)
	//	{
	//		i=labels[y][x];
	//		label_2_pixels_y[i][nr_pixels_curr]=y;
	//		label_2_pixels_x[i][nr_pixels_curr]=x;
	//		nr_pixels_curr=label_2_nr_pixels[i];
	//		label_2_nr_pixels[i]++; 
	//	}
	//}
	//int label_curr=0;
	////image_display(labels,h,w);
	//for(i=0;i<nr_labels;i++)
	//{
	//	nr_pixels_curr=label_2_nr_pixels[i];
	//	if(nr_pixels_curr>0)
	//	{
	//		for(int j=0;j<nr_pixels_curr;j++)
	//		{
	//			y=label_2_pixels_y[i][j];
	//			x=label_2_pixels_x[i][j];
	//			labels[y][x]=label_curr;
	//		}
	//		label_curr++;
	//	}
	//}
	//nr_labels=label_curr;
	//m_ys=&label_2_pixels_y[0][0];
	//m_xs=&label_2_pixels_x[0][0];
	//nr_pixels_curr=0;
	//for(i=0;i<nr_labels;i++)
	//{
	//	label_2_pixels_y[i]=&m_ys[nr_pixels_curr];
	//	label_2_pixels_x[i]=&m_xs[nr_pixels_curr];
	//	nr_pixels_curr+=label_2_nr_pixels[i];
	//}
	//memset(label_2_nr_pixels,0,sizeof(int)*nr_labels);
	//nr_pixels_curr=0;
	//for(y=0;y<h;y++)
	//{
	//	for(x=0;x<w;x++)
	//	{
	//		i=labels[y][x];
	//		nr_pixels_curr=label_2_nr_pixels[i];
	//		label_2_pixels_y[i][nr_pixels_curr]=y;
	//		label_2_pixels_x[i][nr_pixels_curr]=x;
	//		label_2_nr_pixels[i]++;
	//	}
	//}
	//image_display(labels,h,w);
	//memset(label_2_nr_pixels,0,sizeof(int)*nr_labels);
	//for(y=0;y<h;y++)
	//{
	//	for(x=0;x<w;x++)
	//	{
	//		i=labels[y][x];
	//		nr_pixels_curr=label_2_nr_pixels[i];
	//		label_2_pixels_y[i][nr_pixels_curr]=y;
	//		label_2_pixels_x[i][nr_pixels_curr]=x;
	//		label_2_nr_pixels[i]++;
	//	}
	//}
	return(0);
}
qx_queue::qx_queue()
{
	queue_y= NULL;
	queue_x= NULL;
};
qx_queue::~qx_queue()
{
	clean();
};
int qx_queue::init(int len)
{
	if (len<=0) 
	{
		cout<<"The length is: "<<len<<"!!";
		exit (0);
	}
	queue_y= (int*) malloc(sizeof(int)*len*2);
	queue_x= (int*) malloc(sizeof(int)*len*2);
	first=0; 
	last= -1;
	length= 0;
	return (0);
}
void qx_queue::reinit() 
{
	first=0; 
	last= -1;
	length= 0;
}
void qx_queue::clean() 
{
	if (queue_y!=NULL) free(queue_y); queue_y=NULL;
	if (queue_x!=NULL) free(queue_x); queue_x=NULL; 
}
void qx_queue::push(int y,int x) 
{
	length++;
	queue_y[++last]=y;
	queue_x[last]=x;
}
void qx_queue::pull(int &y,int &x)
{
	length--;
	y=queue_y[first];
	x=queue_x[first++];
}