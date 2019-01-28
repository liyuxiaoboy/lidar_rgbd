
#include "basic.h"
#include "qx_basic_file.h"
#include<sys/io.h>
#include <dirent.h>
#include <string.h>
#include<boost/filesystem.hpp>
int get_nr_file(const std::string file_folder,const std::string file_format,bool display_files)
{
  chdir(file_folder.c_str());
  int nr_file=0;
  if(boost::filesystem::exists(file_folder))  //判断文件存在性
  {
    if(boost::filesystem::is_directory(file_folder)) { //file_folder is a folder
      boost::filesystem::recursive_directory_iterator beg_iter(file_folder);
      boost::filesystem::recursive_directory_iterator end_iter;
      for (; beg_iter != end_iter; ++beg_iter)
      {
//        std::cout<<"beg_iter->path().extension(): "<<beg_iter->path().extension()<<std::endl;
          if (boost::filesystem::is_regular_file(*beg_iter) &&
              beg_iter->path().extension() == file_format)
            nr_file++;
      }
    }
  }
  else
  {
      std::cout << "get_nr_file: cannot find folder [" << file_folder << "]!" << std::endl;
     //boost::filesystem::create_directory(file_folder);  //目录不存在，创建
  }

  return(nr_file);
}

int get_files(char **files,const std::string file_folder,const std::string file_format,int str_length,int max_nr_file)
{
  int nr_file=0;
  if(max_nr_file<=0) max_nr_file=get_nr_file(file_folder,file_format,false);
  if(boost::filesystem::exists(file_folder))  //判断文件存在性
  {
    if(boost::filesystem::is_directory(file_folder)) { //file_folder is a folder
      boost::filesystem::recursive_directory_iterator beg_iter(file_folder);
      boost::filesystem::recursive_directory_iterator end_iter;
      for (; beg_iter != end_iter; ++beg_iter)
      {
          if (boost::filesystem::is_regular_file(*beg_iter) &&
              beg_iter->path().extension() == file_format&&nr_file<max_nr_file){
            std::string strPath = beg_iter->path().string();  //遍历出来的文件名
            snprintf(files[nr_file],str_length,"%s",strPath.c_str());
            nr_file++;
          }
      }
    }
  }
  else
  {
      std::cout << "get_files: cannot find folder [" << file_folder << "]!" << std::endl;
  }
  return(nr_file);
}

int file_open_ascii(char *file_path,double *out,int len)
{
        FILE *file_in; char str[65]; int i;
        file_in=fopen(file_path, "r");
        //file_in = fopen_s(file_path,"r");
        if(file_in!=NULL)
        {
                fseek(file_in,0,SEEK_SET);
                for(i=0;i<len;i++ )
                {
                        fscanf(file_in,"%s",str);
                        //fscanf_s(file_in,"%s",str,65);
                        out[i]=atof(str);
                }
                fclose(file_in);
        }
        else
        {
                printf("qx_basic_file: Can not open file: %s\n",file_path);
                getchar();
                exit(-1);
        }
        return(0);
}


void file_save_ascii_2d(char *file_path,double **out,int h,int w)
{
	FILE * fileout; int y,x; 
	char*str_format="%9.9f ";
	//char str_format[10];
	//if(str) sprintf_s(str_format,10,"%s ",str);
	//else  sprintf_s(str_format,10,"%e ");
	fileout= fopen(file_path,"w");
	//fopen_s(&fileout,file_path,"w");
	for(y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(fileout,str_format,out[y][x]);	
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}
void file_save_ascii_2d(char *file_path,unsigned char **out,int h,int w)
{
	FILE * fileout; int y,x;
	fileout= fopen(file_path,"w");
	//fopen_s(&fileout,file_path,"w");
	for(y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(fileout,"%i ",out[y][x]);	
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}
