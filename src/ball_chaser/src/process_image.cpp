#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z) {
  ROS_INFO_STREAM("Moving the arm to the center");

  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;

  if (!client.call(srv)) {
    ROS_ERROR("Failed to call service drive robot");
  }
}

void process_image_callback(const sensor_msgs::Image img) {
  int white_pixel = 255;
  int left = 0;
  int forward = 0;
  int right = 0;
  float lin_x = 0.0;
  float ang_z = 0.0;

  for (int i = 0; i < img.height * img.step; i++) {
    if (img.data[i] == white_pixel) {
      int position = i % img.step;
      if (position < (img.step / 4)) {
        left++;
      } else if (position < (img.step * 3 / 4)) {
        forward++;
      } else {
        right++;
      }
    }
  }
  if (left > forward) {
    if (left >  right) {
      ang_z = -0.3;
    } else {
      ang_z = 0.3;
    }
  } else {
    if (forward > right) {
      lin_x = 0.3;
    } else {
      ang_z = 0.3;
    }
  }
  drive_robot(lin_x, ang_z);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

  ros::spin();

  return 0;
}
