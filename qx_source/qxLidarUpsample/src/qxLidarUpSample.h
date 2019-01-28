#ifndef QX_LIDAR_UPSAMPLE_H
#define QX_LIDAR_UPSAMPLE_H

#include <string>
#include <vector>

namespace qx_lidar_upsample {
void LidarUpSample(const std::string& lidar_image,
                   const std::string& camera_image, const int crop_y,
                   const std::string& out_image_name1,
                   const std::string& out_image_name2);
}  // namespace qx_lidar_upsample

#endif
