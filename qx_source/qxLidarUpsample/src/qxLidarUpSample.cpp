#include "qxLidarUpSample.h"

#include <assert.h>

#include "basic.h"
#include "ppm.h"
#include "qx_basic_file.h"

#include "ctmf.h"
#include "qx_tree_filter.h"

namespace qx_lidar_upsample {
void LidarUpSample(const std::string& lidar_image,
                   const std::string& camera_image, const int crop_y,
                   const std::string& out_image_name1,
                   const std::string& out_image_name2) {
  qx_tree_filter tf;
  int h, w;
  int y0 = crop_y;  // to crop a valid region from the input color image
  unsigned char ***image, **depth, ***image2, **depth1, **depth2, **depth_out;
  double** depth_tf;
  double*** cost;
  const char* filename = camera_image.c_str();
  const char* filename_depth = lidar_image.c_str();
  const char* filename_depth_1 = out_image_name1.c_str();
  const char* filename_depth_2 = out_image_name2.c_str();
  qx_image_size(filename, h, w);
  assert(h > y0);
  int h2 = h - y0;
  image = qx_allocu_3(h, w, 3);
  depth = qx_allocu(h, w);
  image2 = qx_allocu_3(h2, w, 3);
  depth1 = qx_allocu(h2, w);
  depth2 = qx_allocu(h2, w);
  depth_tf = qx_allocd(h2, w);
  cost = qx_allocd_3(5, h2, w);
  depth_out = qx_allocu(h2, w);

  qx_loadimage(filename, image[0][0], h, w);
  qx_loadimage(filename_depth, depth[0], h, w);
  memcpy(image2[0][0], image[y0][0], sizeof(char) * h2 * w * 3);
  memcpy(depth1[0], depth[y0], sizeof(char) * h2 * w);
  memcpy(depth2[0], depth1[0], sizeof(char) * h2 * w);

  memset(cost[0][0], 0, sizeof(double) * 5 * h2 * w);
  int nr_point = 0;
  for (int y = 0; y < h2; y++) {
    for (int x = 0; x < w; x++) {
      for (int c = 0; c < 3; c++) {
        image2[y][x][c] = image[y + y0][x][c];
      }
      depth2[y][x] = depth[y + y0][x];
      if (depth2[y][x] > 0) {
        cost[0][y][x] = depth2[y][x];
        cost[1][y][x] = 1;
        nr_point++;
      }
    }
  }

  tf.init(h2, w, 3);
  tf.build_tree(image2[0][0]);
  tf.filter(cost[0][0], cost[2][0], cost[3][0], cost[4][0]);
  tf.filter(cost[1][0], cost[2][0], cost[3][0], cost[4][0]);

  for (int y = 0; y < h2; y++) {
    for (int x = 0; x < w; x++) {
      depth_tf[y][x] = qx_div(cost[0][y][x], cost[1][y][x]);
    }
  }
  for (int y = 0; y < h2; y++)
    for (int x = 0; x < w; x++) {  // transfer to color depth
      int d = qx_min(255, qx_round(depth_tf[y][x]));
      depth_out[y][x] = d;
    }
  qx_saveimage(filename_depth_1, depth_out[0], h2, w, 1);

  int nr_valid = 0;
  double depth_threshold = 2.f;
  memset(cost[0][0], 0, sizeof(double) * 5 * h2 * w);
  for (int y = 0; y < h2; y++) {
    for (int x = 0; x < w; x++) {
      if (depth2[y][x]) {
        double dist = depth2[y][x] - depth_tf[y][x];
        // ************* well-aligned 3d points *************
        if (abs(dist) < depth_threshold) {
          nr_valid++;
          cost[0][y][x] = depth2[y][x];
          cost[1][y][x] = 1;
        } else {
          depth2[y][x] = 0;
        }
      }
    }
  }

  std::cout << "nr_point vs nr_valid: " << nr_point << " " << nr_valid
            << std::endl;
  tf.filter(cost[0][0], cost[2][0], cost[3][0], cost[4][0]);
  tf.filter(cost[1][0], cost[2][0], cost[3][0], cost[4][0]);

  for (int y = 0; y < h2; y++) {
    for (int x = 0; x < w; x++) {
      depth_tf[y][x] = qx_div(cost[0][y][x], cost[1][y][x]);
      depth2[y][x] = qx_round(depth_tf[y][x]);
    }
  }

  for (int y = 0; y < h2; y++)
    for (int x = 0; x < w; x++) {  // transfer to color depth
      int d = qx_min(255, qx_round(depth_tf[y][x]));
      depth_out[y][x] = d;
    }
  qx_saveimage(filename_depth_2, depth_out[0], h2, w, 1);

  qx_freeu(depth);
  qx_freeu(depth_out);
  qx_freeu_3(image);
  qx_freeu(depth2);
  qx_freed(depth_tf);
  qx_freeu_3(image2);
  qx_freed_3(cost);
}

}  // namespace qx_lidar_upsample
