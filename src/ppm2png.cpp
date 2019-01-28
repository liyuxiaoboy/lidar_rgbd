#include <iostream>
#include<opencv2/opencv.hpp>
#include <string>
#include <fstream>
#include <sstream>

void LoadImages(const std::string &strFile,std::vector<std::string> &vstrDepthFilenames);

int main(int argc, char** argv) {
    if(argc!=4)
    {
        std::cout<<"enter the [associate.txt] [data_path] [output_path]"<<std::endl;
    }
    std::string associate(argv[1]);
    std::string data_path(argv[2]);
    std::string opt_path(argv[3]);
    std::vector<std::string> vstrDepthFilenames;
    //读文件开始了
    LoadImages(associate,vstrDepthFilenames);
    int nImages = vstrDepthFilenames.size();

    for(int ni=0; ni<nImages; ni++)
    {
        std::string im_depth=data_path+"/"+vstrDepthFilenames[ni]+".ppm";
        cv::Mat input_image = cv::imread(im_depth, cv::IMREAD_UNCHANGED);
        std::string out_img=opt_path+"/"+vstrDepthFilenames[ni]+".png";
        cv::imwrite(out_img, input_image);
    }
    return 0;
}

void LoadImages(const std::string &strFile,std::vector<std::string> &vstrDepthFilenames)
{
    std::ifstream f;
    f.open(strFile.c_str());

    while(!f.eof())
    {
        std::string s;
        getline(f,s);
        if(!s.empty())
        {
//注意txt中的空格不读的
            std::stringstream ss;
            ss << s;
            std::string sRGB;
            std::string sDepth;
            std::string stemp;
            ss >> sRGB;
            ss >> stemp;
            ss >> sDepth;
            vstrDepthFilenames.push_back(sDepth);
        }
    }
}