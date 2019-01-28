#include "basic.h"

double qx_timer::start() {
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  m_begin = tv.tv_sec + tv.tv_usec * 0.000001;
  return (m_begin);
}
double qx_timer::stop() {
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  m_end = tv.tv_sec + tv.tv_usec * 0.000001;
  return ((double)(m_end-m_begin));
}

void qx_timer::time_display(const char *disp, int nr_frame) {
  printf("--Running time (%s) is: %5.5f Seconds.\n", disp,
         stop() / nr_frame);
}
void qx_timer::fps_display(const char *disp, int nr_frame) {
  printf("--Running time (%s) is: %5.5f frame per second.\n", disp,
         static_cast<double>(nr_frame) / stop());
}


void qx_sort_increase_using_histogram(int*id,unsigned char*image,int len)
{
    int histogram[QX_DEF_CHAR_MAX+1];
    int nr_bin=QX_DEF_CHAR_MAX+1;
    memset(histogram,0,sizeof(int)*nr_bin);
    for(int i=0;i<len;i++)
    {
        histogram[image[i]]++;
    }
    int nr_hitted_prev=histogram[0];
    histogram[0]=0;
    for(int k=1;k<nr_bin;k++)
    {
        int nr_hitted=histogram[k];
        histogram[k]=nr_hitted_prev+histogram[k-1];
        nr_hitted_prev=nr_hitted;
    }
    for(int i=0;i<len;i++)
    {
        unsigned char dist=image[i];
        int index=histogram[dist]++;
        id[index]=i;
    }
}
