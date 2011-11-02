#ifndef GAZEBO_ROS_CREATE_H
#define GAZEBO_ROS_CREATE_H

#include <gazebo/Controller.hh>
#include <gazebo/Model.hh>
#include <gazebo/Geom.hh>
#include <gazebo/Time.hh>
#include <gazebo/RaySensor.hh>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TwistWithCovariance.h>
#include <geometry_msgs/PoseWithCovariance.h>

#include <tf/transform_broadcaster.h>
#include <ros/ros.h>

namespace gazebo
{
  class GazeboRosCreate : public Controller
  {
    public: 
      GazeboRosCreate( gazebo::Entity *parent );
      virtual ~GazeboRosCreate();
          
      virtual void LoadChild( XMLConfigNode *node );
      virtual void InitChild();
      virtual void FiniChild();
      virtual void UpdateChild();
  
    private:

      void UpdateSensors();
      void OnContact(const gazebo::Contact &contact);
      void OnCmdVel( const geometry_msgs::TwistConstPtr &msg);

      ros::NodeHandle *rosnode_;
      //ros::Service operating_mode_srv_;
      //ros::Service digital_output_srv_;
  
      ros::Publisher sensor_state_pub_;
      ros::Publisher odom_pub_;
      ros::Publisher joint_state_pub_;
  
      ros::Subscriber cmd_vel_sub_;

      ParamT<std::string> *node_namespaceP_;
      ParamT<std::string> *left_wheel_joint_nameP_;
      ParamT<std::string> *right_wheel_joint_nameP_;
      ParamT<std::string> *front_castor_joint_nameP_;
      ParamT<std::string> *rear_castor_joint_nameP_;
      ParamT<std::string> *base_geom_nameP_;

      /// Separation between the wheels
      ParamT<float> *wheel_sepP_;

      /// Diameter of the wheels
      ParamT<float> *wheel_diamP_;

      ///Torque applied to the wheels
      ParamT<float> *torqueP_;

      Model *my_parent_;

      /// Speeds of the wheels
      float *wheel_speed_;

      // Simulation time of the last update
      Time prev_update_time_;
      Time last_cmd_vel_time_;

      float odom_pose_[3];
      float odom_vel_[3];

      bool set_joints_[4];
      Joint *joints_[4];
      Geom *base_geom_;

      RaySensor *left_cliff_sensor_;
      RaySensor *leftfront_cliff_sensor_;
      RaySensor *rightfront_cliff_sensor_;
      RaySensor *right_cliff_sensor_;
      RaySensor *wall_sensor_;

      tf::TransformBroadcaster transform_broadcaster_;
      sensor_msgs::JointState js_;

      turtlebot_node::TurtlebotSensorState sensor_state_;

      void spin();
      boost::thread *spinner_thread_;
  };
}
#endif
