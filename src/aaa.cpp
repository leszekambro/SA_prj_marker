#include <ros/ros.h>
//#include <tf/Matrix.h>
#include <tf/transform_listener.h>


int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;

  tf::TransformListener listener;

  ros::Rate rate(10.0);
  
  bool nie_ma = true; 
  while (node.ok()){
    tf::StampedTransform transform;
    std::cout << std::boolalpha << nie_ma << std::endl;
    try{
      listener.lookupTransform("/ardrone_base_bottomcam", "/ar_marker_0",  
                               ros::Time(0), transform);
      nie_ma = false;
      std::cout << transform.getOrigin().getX()<< transform.getOrigin().getY()<< transform.getOrigin().getZ()
      << std::endl;
      double roll, pitch, yaw;
      tf::Matrix3x3 mat(transform.getRotation());
	mat.getEulerYPR(yaw, pitch, roll);
	using namespace std;
	cout << roll << " " << pitch << " " << yaw << endl;
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }
    catch (tf::LookupException& ex) { 
		nie_ma = true;
		}

    rate.sleep();
  }
  return 0;
};
