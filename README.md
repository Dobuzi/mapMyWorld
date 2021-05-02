# Graph SLAM with RTAB Mapping on ROS

## Robot Components

1. Chassis : Body + Ball Caster * 2
2. Wheel : Left Wheel + Right Wheel
3. Sensor : Camera + Lidar (hokuyo)

## Live Video

### Ball chasing
![Camera and Lidar Sensing while turning around](ballChaser.gif)

### Localization
![Camera and Lidar Sensing And Localization with AMCL](whereAmI.gif)

### SLAM
![RGBD Camera with RTAB ROS](mapMyWorld.gif)

## How to use

1. Run 1st terminal
```
git clone https://github.com/Dobuzi/mapMyWorld.git
cd mapMyWorld
source devel/setup.bash
catkin_make
source devel/setup.bash
roslaunch my_robot world.launch
```
2. Run 2nd terminal
```
source devel/setup.bash
roslaunch my_robot mapping.launch # or localization.launch
```

3. Run 3rd terminal
```
source devel/setup.bash
roslaunch my_robot teleop.launch
```
