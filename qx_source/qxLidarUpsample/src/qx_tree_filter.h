/*$Id: ppm.h,v 1.22 2007/04/04 02:15:14 liiton Exp $*/
/****************************************************************
\Author:	Qingxiong Yang (liiton)
\Function:	Filtering an image using a tree structure.
*****************************************************************/
#ifndef QX_TREE_FILTER_H
#define QX_TREE_FILTER_H
#include "qx_mst_kruskals_image.h"
#include "basic.h"
class qx_tree_filter
{
public:
	qx_tree_filter();
	~qx_tree_filter();
	void clean();
	int init(int h,int w,int nr_channel,double sigma_range=QX_DEF_MST_KI_SIGMA_RANGE,int nr_neighbor=QX_DEF_MST_KI_4NR_NEIGHBOR);
	int build_tree(unsigned char*texture);
	//void init_tree_value(unsigned char*image);
	int filter(double*cost,double*cost_backup,double*weight,double*weight_backup,int nr_plane);
	int filter(double*cost,double*cost_backup,double*weight,double*weight_backup);
public:
	void update_table(double sigma_range);
	int*get_rank(){return(m_mst_rank);};
private:
	qx_mst_kruskals_image m_mst;
	int m_h,m_w,m_nr_channel; int m_nr_pixel;
	int*m_mst_parent;
	int*m_mst_nr_child;
	int**m_mst_children;//[QX_DEF_MST_NODE_MAX_NR_CHILDREN];
	int*m_mst_rank;
	unsigned char*m_mst_weight;//cost between this node and its parent

	double m_table[QX_DEF_CHAR_MAX+1];
	int*m_node_id;
private:
	void filter_main(bool compute_weight);
};
void test_qx_tree_filter();

#endif

