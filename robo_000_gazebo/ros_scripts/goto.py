#!/usr/bin/env python3 
import rclpy
import math 
import random
from rclpy.node import Node

from geometry_msgs.msg import Twist
# Import Pose 
# from geometry_msgs.msg import Pose
from turtlesim.msg import Pose as TurtlePose




# Returns a tuple of (success, Twist)
def local_planner(current_pose, goal_pose):
    assert(isinstance(current_pose, TurtlePose))
    assert(isinstance(goal_pose, TurtlePose))
    max_angular_speed = 0.5
    max_linear_speed = 0.5
    max_distance_of_success = 0.1

    delta_x = goal_pose.x - current_pose.x
    delta_y = goal_pose.y - current_pose.y

    angle_to_goal = math.atan2(delta_y, delta_x)
    delta_angle = angle_to_goal - current_pose.theta
    if delta_angle > math.pi:
        delta_angle -= 2 * math.pi
    elif delta_angle < -math.pi:
        delta_angle += 2 * math.pi

    distance_to_goal = math.sqrt(delta_x**2 + delta_y**2)

    if distance_to_goal < max_distance_of_success:
        return True, Twist()

    # Rate the confidence of the distance, 1 is perfect, 0 is no confidence
    # Make it exponentially slower as the distance decreases (so it slows down as it approaches the goal)
    linear_confidence = math.exp(-distance_to_goal / 5)

    # Rate the confidence of the angle, 1 is perfect, 0 is no confidence
    # Make it exponentially slower as the angle difference increases
    angular_confidence = math.exp(100 * -abs(delta_angle) / math.pi)
    if delta_angle > 0.1 * math.pi:
        angular_confidence = 0
    speed = max(max_linear_speed, distance_to_goal * linear_confidence * angular_confidence)
    
    # Set angle to angle difference divided by 10, maximum magnitude of 0.2 radians
    angle_speed = max(-max_angular_speed, min(delta_angle, max_angular_speed))

    command = Twist()
    command.linear.x = speed
    command.angular.z = angle_speed
    return False, command

# Publish a spiral of velocity commands
class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        timer_period = 0.5  # seconds

        self.set_new_goal()
        self.command = Twist()

        self.mode = "waiting" # "moving" or "waiting"

        self.last_i_goal_achieved = 0

        self.subscription = self.create_subscription(
            TurtlePose,
            '/turtle1/pose',
            self.listener_callback,
            10)

        self.subscription  # prevent unused variable warning

        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        self.publisher_.publish(self.command)
        self.i += 1

    def set_new_goal(self):
        self.goal = TurtlePose(x=float(random.randint(0, 10)), 
                               y=float(random.randint(0, 10)), 
                               theta=0.0)
    

    def listener_callback(self, msg):
        print(f"I heard the robot x is {msg.x}, y is {msg.y}, theta is {msg.theta}")

        if self.mode == "waiting":
            self.command = Twist()
            if self.i - self.last_i_goal_achieved > 10:
                self.mode = "moving"
                self.set_new_goal()
        if self.mode == "moving":
            success, self.command = local_planner(msg, self.goal)
            if success:
                self.mode = "waiting"
                self.last_i_goal_achieved = self.i
        
            
def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()