#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z) {
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;

  if (!client.call(srv)) {
    ROS_ERROR("Failed to call service drive robot");
  }
}

bool isWhite(int R, int G, int B) {
  if ((R == 255) && (G == 255) && (B == 255)) {
    return true;
  }
  return false;
}

void process_image_callback(const sensor_msgs::Image img) {
  int white_pixel = 255;
  int left = 0;
  int forward = 0;
  int right = 0;
  float lin_x = 0.0;
  float ang_z = 0.0;
  int max_zone = 0;
  int max_threshold = 50000;
  int min_threshold = 500;
  float turn_left = 0.3;
  float turn_right = -0.3;
  float run_forward = 0.3;
  int R, G, B;

  for (int i = 0; i < img.height * img.step; i++) {
    R = img.data[i];
    G = img.data[i+1];
    B = img.data[i+2];
    if ((i%3 == 0) and isWhite(R, G, B)) {
      int position = i % img.step;
      if (position < (img.step / 4)) {
        left++;
      } else if (position < (img.step * 2 / 4)) {
        forward++;
      } else {
        right++;
      }
    }
  }

  if ((left > forward) && (left > right)) {
    max_zone = left;
    ang_z = turn_left;
  } else if ((forward > left) && (forward > right)) {
    max_zone = forward;
    lin_x = run_forward;
  } else {
    max_zone = right;
    ang_z = turn_right;
  }

  ROS_INFO_STREAM("left: " << std::to_string(left) << ", forward:" << std::to_string(forward) << ", right: " << std::to_string(right));
  
  if ((max_zone < min_threshold) || (max_zone > max_threshold)) {
    lin_x = 0.0;
    ang_z = 0.0;
  }
  drive_robot(lin_x, ang_z);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
  ROS_INFO("Ready to follow white ball");
  ros::spin();

  return 0;
}
