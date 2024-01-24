#!/usr/bin/env python3 
import math 
import random
import datetime 

import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Twist
# Import Pose 
# from geometry_msgs.msg import Pose
from turtlesim.msg import Pose as TurtlePose


class PIDController:
    def __init__(self, Kp, Ki, Kd):
        self.Kp = Kp
        self.Ki = Ki
        self.Kd = Kd
        self.previous_error = 0
        self.integral = 0

    def calculate(self, error, delta_time):
        self.integral += error * delta_time
        derivative = (error - self.previous_error) / (delta_time + 0.0001)
        output = self.Kp * error + self.Ki * self.integral + self.Kd * derivative
        self.previous_error = error
        assert(isinstance(output, float))
        print(f"PIDController: error={error}, delta_time={delta_time}, output={output}")
        return output


def global_planner():
    return [
        # Lawnmower pattern
        TurtlePose(x=1.0, y=1.0, theta=0.0),
        TurtlePose(x=9.0, y=1.0, theta=0.0),
        TurtlePose(x=9.0, y=2.0, theta=0.0),
        TurtlePose(x=1.0, y=2.0, theta=0.0),
        TurtlePose(x=1.0, y=3.0, theta=0.0),
        TurtlePose(x=9.0, y=3.0, theta=0.0),
        TurtlePose(x=9.0, y=4.0, theta=0.0),
        TurtlePose(x=1.0, y=4.0, theta=0.0),
        TurtlePose(x=1.0, y=5.0, theta=0.0),
        TurtlePose(x=9.0, y=5.0, theta=0.0),
        TurtlePose(x=9.0, y=6.0, theta=0.0),
        TurtlePose(x=1.0, y=6.0, theta=0.0),
        TurtlePose(x=1.0, y=7.0, theta=0.0),
        TurtlePose(x=9.0, y=7.0, theta=0.0),
        TurtlePose(x=9.0, y=8.0, theta=0.0),
        TurtlePose(x=1.0, y=8.0, theta=0.0),
        TurtlePose(x=1.0, y=9.0, theta=0.0),
        TurtlePose(x=9.0, y=9.0, theta=0.0),
    ]

speed_controller = PIDController(0.5, 0.0, 0.0)
angle_controller = PIDController(0.9, 0.0, 0.0)

# Returns a tuple of (success, Twist)
last_call_time = datetime.datetime.now()
def local_planner(current_pose, goal_pose):

    assert(isinstance(current_pose, TurtlePose))
    assert(isinstance(goal_pose, TurtlePose))
    max_angular_speed = 1.0
    max_linear_speed = 4.0
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

    # Limit the distance to the goal to 1.0
    # This helps our PIDs focus on matching the expected path 
    # instead of error to overall goal.
    distance_to_goal = min(distance_to_goal, 1.0)

    if distance_to_goal < max_distance_of_success:
        return True, Twist()
    
    expected_speed = 3.0
    if abs(delta_angle) > (5.0 / 180.0) * math.pi:
        expected_speed = 0.5
        delta_angle *= 0.5
    actual_speed = math.sqrt(current_pose.linear_velocity**2 + current_pose.angular_velocity**2)
    speed_delta = expected_speed - actual_speed

    delta_time = (datetime.datetime.now() - last_call_time).total_seconds()

    speed = speed_controller.calculate(speed_delta, delta_time)
    speed = max(0.0, min(max_linear_speed, speed))

    angle_speed = angle_controller.calculate(delta_angle, delta_time)
    angle_speed = max(-max_angular_speed, min(angle_speed, max_angular_speed))

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

        self.command = Twist()

        self.lastmsg = None

        self.plan = global_planner()
        self.plan_index = 0

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

    def listener_callback(self, msg):
        
        success, self.command = local_planner(msg, self.plan[self.plan_index])

        self.lastmsg = msg
        print(f"Current goal is {self.plan[self.plan_index]}")
        if success:
            self.plan_index += 1
            if self.plan_index >= len(self.plan):
                self.plan_index = 0
        
            
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