#pragma once

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>
#include "sys/stat.h"
#include "sys/time.h"
#include "sys/types.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
//#include <string>
#include<string.h>
#include <vector>
#include <unistd.h>
#include "qx_alloc.h"


using namespace std;
#define QX_DEF_FLOAT_RELATIVE_ACCURACY      2.2204e-016

#define QX_DEF_CHAR_MAX                 255
template <typename T>static inline T qx_max(T const & a, T const & b) {return a > b ? a : b;}
template <typename T>static inline T qx_min(T const & a, T const & b) {return a < b ? a : b;}

template <typename T>static inline unsigned char qx_max_3(T*a){return(qx_max(qx_max(a[0],a[1]),a[2]));}
template <typename T>static inline unsigned char qx_max_3(T a,T b,T c){return(qx_max(qx_max(a,b),c));}
template <typename T>static inline T qx_abs(T const & a) {return a > 0 ? a : -a;}
template <typename T> static inline int qx_round(T in_x) { if(in_x<0) return (int)(in_x-0.5); else return (int)(in_x+0.5); }
template<typename T>inline void qx_memcpy_3(T a[3],T b[3]){memcpy(a,b,sizeof(T)*3);}
template <typename T>static inline double qx_div(T x,T y){return((double)x/((double)y+(double)QX_DEF_FLOAT_RELATIVE_ACCURACY));}

void qx_sort_increase_using_histogram(int*id,unsigned char*image,int len);



class qx_timer {public:  double start();  double stop();  void time_display(const char *disp, int nr_frame = 1); void fps_display(const char *disp, int nr_frame = 1); private:  double m_begin, m_end;};

