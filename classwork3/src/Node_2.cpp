#include "ros/ros.h"
#include "classwork3/ReqRes.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include <tf/transform_listener.h>

using namespace std;

int main(int argc, char **argv) {

	ros::init(argc, argv, "Pose_broadcaster");
	ros::NodeHandle n;

	
	ros::ServiceClient client = n.serviceClient<classwork3::ReqRes>("pose");
	
    classwork3::ReqRes srv;
	classwork3::ReqRes::Request req;
    classwork3::ReqRes::Response res;

    tf::TransformBroadcaster br;
    tf::Transform transform;

    req.frame_a.data = "/base_link";
    req.frame_b.data = "/end_effector";
	

	ROS_INFO("Waiting for the client server");
	client.waitForExistence();
	ROS_INFO("Client server up now");

	if (!client.call(srv)) {
		ROS_ERROR("Error calling the service");
		return 1;
	}

    ros::Rate rate(10);

    while( ros::ok()){
    
    transform.setOrigin( tf::Vector3(res.pose.position.x, res.pose.position.y, res.pose.position.z) );

    tf::Quaternion q;
    q.setRPY(res.pose.orientation.x, res.pose.orientation.y, res.pose.orientation.z);
    transform.setRotation(q);

    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", camera_link));


	cout << "Pose: " << res.pose << endl;

    rate::sleep();

    }
	
	return 0;
}