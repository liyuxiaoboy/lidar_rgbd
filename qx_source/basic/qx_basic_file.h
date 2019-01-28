#pragma once

//#include "boost/filesystem/operations.hpp"
//#include "boost/filesystem/path.hpp"
#include "sys/stat.h"
#include "sys/types.h"
int get_nr_file(const std::string file_folder,const std::string file_format,bool display_files=false);

int get_files(char **files,const std::string file_folder,const std::string file_format,int str_length,int max_nr_file=0);

int file_open_ascii(char *file_path,double *out,int len);
void file_save_ascii_2d(char *file_path,double **out,int h,int w);
void file_save_ascii_2d(char *file_path,unsigned char **out,int h,int w);
