/*$Id: qx_seg_queue.h,v 1.1 2007/04/04 02:14:42 liiton Exp $*/
/*******************************************************
\Author:	Qingxiong Yang (liiton)
\Function:	Queue operation.
********************************************************/
#ifndef QX_QUEUE_H
#define QX_QUEUE_H

class qx_segm_data
{
public:
	qx_segm_data();
	~qx_segm_data();
	int nr_labels,**labels,*label_2_nr_pixels,**label_2_pixels_y,**label_2_pixels_x;
	void init();
	int re_addressing(int h,int w);
private:
	int *m_ys,*m_xs;
};
class qx_queue
{
public:
	qx_queue();
	~qx_queue();
	void clean();
	int	init(int len);
	void reinit();
	void push(int y,int x);
	void pull(int &y,int &x);
	int *queue_x,*queue_y;
	int	length;
	int	first;
	int	last;
};
#endif