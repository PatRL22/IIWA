#include "ros/ros.h"
#include "classwork3/ReqRes.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include <tf/transform_listener.h>

using namespace std;

bool service_callback( classwork3::ReqRes::Request &req, classwork3::ReqRes::Response &res) {

    bool transformation = true;

	cout << "Transformation from the frame: "<< req.frame_b.data << "to the frame: "<<req.frame_b.data << endl;

    tf::TransformListener listener;
    tf::StampedTransform transform;

    try {

        listener.lookupTransform(req.frame_b.data, req.frame_a.data, ros::Time(0), transform);
        res.pose.position.x = transform.getOrigin().x() << ", " << 
        res.pose.position.y = transform.getOrigin().y() << ", " <<
        res.pose.position.z = transform.getOrigin().z() << ", " << 
        res.pose.orientation.x = transform.getRotation().x() << ", " << 
        res.pose.orientation.y = transform.getRotation().y() << ", " << 
        res.pose.orientation.z = transform.getRotation().z()
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
        transformation=false;
    }

	return transformation;
}


int main(int argc, char **argv) {

	ros::init(argc, argv, "Pose_listener");

	ros::NodeHandle n;

	ros::ServiceServer service = n.advertiseService("Pose", service_callback);
    
	ros::spin();


	return 0;
}
