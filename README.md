# Map4 Extract Sensor Data

Simple ROS2 node to extract sensor data. Tested in Humble.

* Extract Compressed Image : convert CompressedImage to .jpg and save by timestamp.
* Extrace Image : convert Image to .jpg and save by timestamp
* Extract PointCloud2 : convert PointCloud2 into .pcd file and save by timestamp. 

See launch files for usage. E.g.

```
ros2 launch map4_extract_sensor_data extract_pointcloud2.launch.xml input_topic:=/lidar/front/points output_folder:=./pcd
```

```
ros2 launch map4_extract_sensor_data extract_image.launch.xml input_topic:=/camera/image_raw output_folder:=./raw
```

```
ros2 launch map4_extract_sensor_data extract_compress_image.launch.xml input_topic:=/camera/image_raw/compressed output_folder:=./compressed

```