#include <iostream>
#include<opencv2/opencv.hpp>
#include <string>
#include <fstream>
#include <sstream>

void LoadImages(const std::string &strFile,std::vector<std::string> &vstrImgFilenames);

int main(int argc, char** argv) {
    if(argc!=4)
    {
        std::cout<<"enter the [associate.txt] [data_path] [output_path]"<<std::endl;
    }
    std::string associate(argv[1]);
    std::string data_path(argv[2]);
    std::string opt_path(argv[3]);
    std::vector<std::string> vstrImgFilenames;
    //读文件开始了
    LoadImages(associate,vstrImgFilenames);
    int nImages = vstrImgFilenames.size();

    for(int ni=0; ni<nImages; ni++)
    {
        std::string im_img=data_path+"/"+vstrImgFilenames[ni]+".png";
        cv::Mat input_image = cv::imread(im_img, cv::IMREAD_UNCHANGED);
        //Rect area [x, y, width, heigth];
        cv::Rect rect(0, 500, 1920, 580);
        cv::Mat image_roi = input_image(rect);
        std::string out_img=opt_path+"/"+vstrImgFilenames[ni]+".png";
        cv::imwrite(out_img, image_roi);
    }
    return 0;
}

void LoadImages(const std::string &strFile,std::vector<std::string> &vstrImgFilenames)
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
            vstrImgFilenames.push_back(sRGB);
        }
    }
}