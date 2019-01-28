//
// Created by yxli on 18-11-6.
//

#include "opencv2/opencv.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/passthrough.h>
#include <pcl/visualization/pcl_visualizer.h>



void getPcdFilesAndPoses(const std::string &pcd_path, const std::string &pcd_folder, std::map<long, std::string> &files)
{
    std::ifstream fin(pcd_path, std::ios::in);
    char line[1024] = {0};
    std::string name = "";
    std::string timestamp = "";
    while (fin.getline(line, sizeof(line)))
    {
        std::stringstream word(line);
        word >> name;
        word >> timestamp;
        long pcd_time = stod(timestamp) * 1e6;
        files[pcd_time] = pcd_folder + name + ".pcd";


    }
    fin.clear();
    fin.close();
}

void getImgFilesAndPOses(const std::string &image_path, const std::string &image_folder, std::map<long, std::string> &files)
{
    std::ifstream fin(image_path, std::ios::in);
    char line[1024] = {0};
    std::string name = "";
    std::string timestamp = "";
    while (fin.getline(line, sizeof(line)))
    {
        std::stringstream word(line);
        word >> name;
        word >> timestamp;
        long img_time = stod(timestamp) * 1e6;
        files[img_time] = image_folder + name + ".png";

    }
    fin.clear();
    fin.close();
}

bool getClosestImage(long pcd_time, const std::map<long, std::string> &img_map,
                     std::map<long, std::string>::iterator img_iter, long &img_time)
{
    if (img_iter == img_map.end() || pcd_time < img_iter->first)
        return false;

    if (pcd_time == img_iter->first)
    {
        img_time = img_iter->first;
        return true;
    }

    auto img_next = img_iter;
    img_next++;
    while (pcd_time > img_iter->first && img_next != img_map.end() && pcd_time > img_next->first)
    {
        img_iter++;
        img_next++;
    }
    if (pcd_time > img_iter->first && pcd_time < img_next->first)
    {
        img_time = (((pcd_time - img_iter->first) - (img_next->first - pcd_time)) > 0) ? img_next->first : img_iter->first;
        return true;
    }
    return false;
}

std::string ltos(long l)
{
    std::ostringstream os;
    os<<l;
    std::string result;
    std::istringstream is(os.str());
    is>>result;
    return result;
}



std::vector<cv::Point3d> get3DPoints(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    std::vector<cv::Point3d> points;
    for (int i = 0; i < cloud->points.size(); i++)
    {
        points.push_back(cv::Point3d(cloud->points[i].x, cloud->points[i].y, cloud->points[i].z));
    }

    return points;
}


int main(int argc, char **argv)
{
    if (argc != 7)
    {
        std::cout << "please input with format: ./color_1 [pcd_timestamp.txt] [img_timestamp.txt] [pcd_folder] [image_folder]  [output_pcd_dir/] [output_image_dir/] \n";
        return 0;
    }

    std::string pcd_path = argv[1];//pcd_timestamp.txt
    std::string img_path = argv[2];//img_timestamps.txt

    std::string pcd_folder = argv[3];
    std::string img_folder = argv[4];

    std::string output_pcd_path = argv[5];
    std::string output_img_path = argv[6];

    std::map<long, std::string> pcd_map;
    std::map<long, std::string> img_map;

    getPcdFilesAndPoses(pcd_path, pcd_folder, pcd_map);
    getImgFilesAndPOses(img_path, img_folder, img_map);

    //transform between lidar and camera 相机和lidar之间的参数矩阵 w,x,y,z
    Eigen::Quaterniond q_c_l(0.549172, -0.477332, 0.452615, -0.515464);
    Eigen::Affine3d extrinsic_l_c;
    extrinsic_l_c.translation() = Eigen::Vector3d(0.633962, -0.364735, -0.215942);
    extrinsic_l_c.linear() = q_c_l.matrix();
    extrinsic_l_c = extrinsic_l_c.inverse();
    Eigen::Matrix4d trans_pcd_img;
    Eigen::Matrix4d trans_img_pcd;
    trans_pcd_img = extrinsic_l_c.matrix();
    trans_img_pcd = extrinsic_l_c.inverse().matrix();

    cv::Mat intrisicMat(3, 3, cv::DataType<double>::type); // Intrisic matrix 这是相机内参3D->2D
    intrisicMat.at<double>(0, 0) = 1984.964717;
    intrisicMat.at<double>(1, 0) = 0;
    intrisicMat.at<double>(2, 0) = 0;

    intrisicMat.at<double>(0, 1) = 0;
    intrisicMat.at<double>(1, 1) = 1996.986882;
    intrisicMat.at<double>(2, 1) = 0;

    intrisicMat.at<double>(0, 2) = 842.779003;
    intrisicMat.at<double>(1, 2) = 593.359923;
    intrisicMat.at<double>(2, 2) = 1;

    cv::Mat rVec(3, 1, cv::DataType<double>::type); // Rotation vector
    rVec.at<double>(0) = 0;
    rVec.at<double>(1) = 0;
    rVec.at<double>(2) = 0;

    cv::Mat tVec(3, 1, cv::DataType<double>::type); // Translation vector
    tVec.at<double>(0) = 0;
    tVec.at<double>(1) = 0;
    tVec.at<double>(2) = 0;

    cv::Mat distCoeffs(5, 1, cv::DataType<double>::type); // Distortion vector
    distCoeffs.at<double>(0) = -0.542865;
    distCoeffs.at<double>(1) = 0.245749;
    distCoeffs.at<double>(2) = 0.005958;
    distCoeffs.at<double>(3) = 0.005136;
    distCoeffs.at<double>(4) = 0;

    cv::Mat image;
    std::vector<cv::Point2d> imagePoints;
    std::vector<std::string> associate;
    auto img_iter = img_map.begin();
    for (auto pcd_iter = pcd_map.begin(); pcd_iter != pcd_map.end(); pcd_iter++)
    {
        long img_time;
        if (!getClosestImage(pcd_iter->first, img_map, img_iter, img_time))
            continue;

        cv::Mat img;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_src(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::io::loadPCDFile<pcl::PointXYZ>(pcd_iter->second, *cloud_src);


        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cam(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::transformPointCloud(*cloud_src, *cloud_cam, trans_pcd_img);

        std::vector<cv::Point3d> objectPoints = get3DPoints(cloud_cam);
        cv::projectPoints(objectPoints, rVec, tVec, intrisicMat, distCoeffs, imagePoints);

        image = cv::imread(img_map[img_time], CV_LOAD_IMAGE_COLOR);
        cv::Mat depth_2 = cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
        int k=0;
        std::vector<int> obstacle_id;
        for (int i = 0; i < imagePoints.size(); i++)
        {
            auto col = round(imagePoints[i].x);
            auto row = round(imagePoints[i].y);
            auto x = cloud_cam->points[i].x;
            auto y = cloud_cam->points[i].y;
            auto z = cloud_cam->points[i].z;

            if (z <= 0)
                continue;

            if (col >= 0 && col < image.cols && row >= 0 && row < image.rows)
            {
                if (depth_2.at<float>(row, col) == 0)
                    depth_2.at<float>(row, col) = sqrt(x * x + y * y + z * z);
                else if (x * x + y * y + z * z < depth_2.at<float>(row, col) * depth_2.at<float>(row, col))
                {
                    depth_2.at<float>(row, col) = sqrt(x * x + y * y + z * z);

                }
                if(depth_2.at<float>(row, col)!=0)
                {++k;}
            }

        }
        cout<<"opt the "<<pcd_iter->first<<" picture "<<"find "<<k<<" points"<<endl;
        std::string opt_pcd=ltos(pcd_iter->first);
        std::string opt_img=ltos(img_time);
        cv::imwrite(output_pcd_path +"pgm/" +opt_pcd + ".pgm", depth_2);
        cv::imwrite(output_img_path +"ppm/" +opt_img + ".ppm", image);
        cv::imwrite(output_pcd_path +"depth/" +opt_pcd + ".png", depth_2);
        cv::imwrite(output_img_path +"rgb/"+opt_img + ".png", image);

        associate.push_back(opt_img + " " + "rgb/" + opt_img + ".png" + " " + opt_pcd + " " + "depth/" + opt_pcd + ".png");

    }
    std::ofstream out( output_img_path+"img_timestamps.txt");
    for (auto line : associate) {
        if (out.is_open()) {
            out << line << "\n";
        }
    }
    out.close();

    return 0;
}
