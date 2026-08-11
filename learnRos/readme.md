方案一
docker run -d --name ros2_dev \
  --env="DISPLAY=$DISPLAY" \
  --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
  osrf/ros:humble-desktop \
  sleep infinity1.终端1
```
docker exec -it ros2_dev bash -c "source /opt/ros/humble/setup.bash && ros2 run turtlesim turtlesim_node"
```
2.终端2
```
docker exec -it ros2_dev bash -c "source /opt/ros/humble/setup.bash && ros2 run turtlesim turtle_teleop_key"
```

方案二：
```
docker run -d --name ros2_dev \
  --env="DISPLAY=$DISPLAY" \
  --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
  osrf/ros:humble-desktop \
  bash -c "source /opt/ros/humble/setup.bash && sleep infinity"
```
