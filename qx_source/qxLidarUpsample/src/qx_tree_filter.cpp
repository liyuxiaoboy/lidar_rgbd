#include "basic.h"
#include "qx_tree_filter.h"

qx_tree_filter::qx_tree_filter()
{
}
qx_tree_filter::~qx_tree_filter()
{
	clean();
}
void qx_tree_filter::clean()
{
}
int qx_tree_filter::init(int h,int w,int nr_channel,double sigma_range,int nr_neighbor)
{
	m_h=h; m_w=w; m_nr_pixel=m_h*m_w;
	m_mst.init(m_h,m_w,nr_channel,nr_neighbor);
	update_table(sigma_range);
	return(0);
}
void qx_tree_filter::update_table(double sigma_range)
{
	sigma_range=max(0.01,sigma_range);
	for(int i=0;i<=QX_DEF_CHAR_MAX;i++) m_table[i]=exp(-double(i)/(QX_DEF_CHAR_MAX*sigma_range));//weight table
}
int qx_tree_filter::build_tree(unsigned char*texture)
{
	m_mst.mst(texture);
	m_mst_parent=m_mst.get_parent();
	m_mst_nr_child=m_mst.get_nr_child();
	m_mst_children=m_mst.get_children();
	m_mst_rank=m_mst.get_rank();
	m_mst_weight=m_mst.get_weight();
	m_node_id=m_mst.get_node_id();

	return(0);
}
int qx_tree_filter::filter(double*cost,double*cost_backup,double*weight,double*weight_backup,int nr_plane)
{
	memcpy(cost_backup,cost,sizeof(double)*m_h*m_w*nr_plane);
	for(int i=0;i<m_nr_pixel*nr_plane;i++) weight[i]=1;
	memcpy(weight_backup,weight,sizeof(double)*m_h*m_w*nr_plane);
	int*node_id=m_node_id;
	int*node_idt=&(node_id[m_nr_pixel-1]);
	for(int i=0;i<m_nr_pixel;i++)
	{
		int id=*node_idt--;
		int id_=id*nr_plane;
		int nr_child=m_mst_nr_child[id];
		if(nr_child>0)
		{
			double*value_sum=&(cost_backup[id_]);
			double*weight_value_sum=&(weight_backup[id_]);
			for(int j=0;j<nr_child;j++)
			{
				int id_child=m_mst_children[id][j];
				int id_child_=id_child*nr_plane;
				double weight_curr=m_table[m_mst_weight[id_child]];
				//value_sum+=m_mst_value_sum_aggregated_from_child_to_parent[id_child]*weight_curr;
				double*value_child=&(cost_backup[id_child_]);
				double*weight_value_child=&(weight_backup[id_child_]);
				for(int k=0;k<nr_plane;k++)
				{
					value_sum[k]+=(*value_child++)*weight_curr;
					weight_value_sum[k]+=(*weight_value_child++)*weight_curr;
				}
			}
		}
		//else
		//{
		//	memcpy(&(cost_backup[id_]),&(cost[id_]),sizeof(double)*nr_plane);
		//}
		//printf("[id-value-weight_curr]: [%d - %3.3f - %3.3f]\n",id,m_mst_[id].value_sum_aggregated_from_child_to_parent,m_mst_[id].weight_sum_aggregated_from_child_to_parent);
	}
	int*node_id0=node_id;
	int tree_parent=*node_id0++;
	int tree_parent_=tree_parent*nr_plane;
	memcpy(&(cost[tree_parent_]),&(cost_backup[tree_parent_]),sizeof(double)*nr_plane);
	memcpy(&(weight[tree_parent_]),&(weight_backup[tree_parent_]),sizeof(double)*nr_plane);
	for(int i=1;i<m_nr_pixel;i++)//K_00=f(0,00)[K_0-f(0,00)J_00]+J_00, K_00: new value, J_00: old value, K_0: new value of K_00's parent
	{
		int id=*node_id0++;
		int id_=id*nr_plane;
		int parent=m_mst_parent[id];
		int parent_=parent*nr_plane;

		double*value_parent=&(cost[parent_]);//K_0
		double*value_current=&(cost_backup[id_]);//J_00
		double*value_final=&(cost[id_]);
		double*weight_value_parent=&(weight[parent_]);//K_0
		double*weight_value_current=&(weight_backup[id_]);//J_00
		double*weight_value_final=&(weight[id_]);
		double weight_curr=m_table[m_mst_weight[id]];//f(0,00)

		for(int k=0;k<nr_plane;k++) 
		{
			double vc=*value_current++;
			double weight_vc=*weight_value_current++;
			*value_final++=weight_curr*((*value_parent++)-weight_curr*vc)+vc;
			*weight_value_final++=weight_curr*((*weight_value_parent++)-weight_curr*weight_vc)+weight_vc;
		}
		//printf("Final: [id-value-weight_curr]: [%d - %3.3f - %3.3f]\n",id,m_mst_[id].value_sum_aggregated_from_parent_to_child,m_mst_[id].weight_sum_aggregated_from_parent_to_child);
	}
	return(0);
}
int qx_tree_filter::filter(double*cost,double*cost_backup,double*weight,double*weight_backup)
{
	memcpy(cost_backup,cost,sizeof(double)*m_h*m_w);
	for(int i=0;i<m_nr_pixel;i++) weight[i]=1;
	memcpy(weight_backup,weight,sizeof(double)*m_h*m_w);
	int*node_id=m_node_id;
	int*node_idt=&(node_id[m_nr_pixel-1]);
	for(int i=0;i<m_nr_pixel;i++)
	{
		int id=*node_idt--;
		int nr_child=m_mst_nr_child[id];
		if(nr_child>0)
		{
			for(int j=0;j<nr_child;j++)
			{
				int id_child=m_mst_children[id][j];
				double weight_curr=m_table[m_mst_weight[id_child]];

				cost_backup[id]+=cost_backup[id_child]*weight_curr;
				weight_backup[id]+=weight_backup[id_child]*weight_curr;
			}
		}
	}
	int*node_id0=node_id;
	int tree_parent=*node_id0++;
	cost[tree_parent]=cost_backup[tree_parent];
	weight[tree_parent]=weight_backup[tree_parent];
	for(int i=1;i<m_nr_pixel;i++)//K_00=f(0,00)[K_0-f(0,00)J_00]+J_00, K_00: new value, J_00: old value, K_0: new value of K_00's parent
	{
		int id=*node_id0++;
		int parent=m_mst_parent[id];

		double weight_curr=m_table[m_mst_weight[id]];//f(0,00)

		double value_parent=cost[parent];//K_0
		double weight_value_parent=weight[parent];//K_0

		double vc=cost_backup[id];
		double weight_vc=weight_backup[id];

		cost[id]=weight_curr*(value_parent-weight_curr*vc)+vc;
		weight[id]=weight_curr*(weight_value_parent-weight_curr*weight_vc)+weight_vc;
	}
	return(0);
}
