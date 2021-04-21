# Ball Chaser Robot with Gazebo and ROS

## Robot Components

1. Chassis : Body + Ball Caster * 2
2. Wheel : Left Wheel + Right Wheel
3. Sensor : Camera + Lidar (hokuyo)

## Live Video

### Ball chasing
![Camera and Lidar Sensing while turning around](ballChaser.gif)

### Localization
![Camera and Lidar Sensing And Localization with AMCL](whereAmI.gif)

## How to use

1. Run 1st terminal
```
git clone https://github.com/Dobuzi/whereAmI.git
cd whereAmI
source devel/setup.bash
catkin_make
source devel/setup.bash
roslaunch my_robot world.launch
```
2. Run 2nd terminal
```
source devel/setup.bash
roslaunch my_robot amcl.launch
```

3. Run 3rd terminal
```
source devel/setup.bash
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```
