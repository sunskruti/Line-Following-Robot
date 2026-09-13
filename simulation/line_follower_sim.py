"""
Line Following Robot - 2D Kinematics & Sensor Simulation
Simulates a differential drive robot with a 3-sensor IR array following a path.
"""

import math
import time

class DifferentialDriveRobot:
    def __init__(self, x=0.0, y=0.0, theta=0.0, wheelbase=12.0, sensor_offset=8.0, sensor_spacing=2.5):
        self.x = x
        self.y = y
        self.theta = theta  # radians
        self.wheelbase = wheelbase  # distance between wheels (cm)
        self.sensor_offset = sensor_offset  # distance from center to sensor array (cm)
        self.sensor_spacing = sensor_spacing  # distance between adjacent sensors (cm)
        
        self.v_left = 0.0
        self.v_right = 0.0

    def get_sensor_positions(self):
        """Returns coordinates (x, y) for [left, center, right] sensors."""
        # Center of sensor bar
        cx = self.x + self.sensor_offset * math.cos(self.theta)
        cy = self.y + self.sensor_offset * math.sin(self.theta)
        
        # Perpendicular unit vector (left is +pi/2)
        perp_angle = self.theta + math.pi / 2
        px = math.cos(perp_angle)
        py = math.sin(perp_angle)
        
        left_pos = (cx + self.sensor_spacing * px, cy + self.sensor_spacing * py)
        center_pos = (cx, cy)
        right_pos = (cx - self.sensor_spacing * px, cy - self.sensor_spacing * py)
        
        return left_pos, center_pos, right_pos

    def update(self, dt=0.05):
        """Updates robot position and orientation using differential drive kinematics."""
        v = (self.v_right + self.v_left) / 2.0
        omega = (self.v_right - self.v_left) / self.wheelbase
        
        self.theta += omega * dt
        self.x += v * math.cos(self.theta) * dt
        self.y += v * math.sin(self.theta) * dt


def is_on_line(point, track_radius=50.0, track_width=3.0):
    """Simple circular track centered at (0, 50)."""
    px, py = point
    dist_to_center = math.hypot(px, py - track_radius)
    return abs(dist_to_center - track_radius) <= (track_width / 2.0)


def run_simulation(steps=200):
    print("==================================================")
    print(" Starting Line Follower Kinematics Simulation")
    print("==================================================")
    robot = DifferentialDriveRobot(x=0.0, y=0.0, theta=0.0)

    for step in range(steps):
        left_pos, center_pos, right_pos = robot.get_sensor_positions()
        
        # In Arduino: LOW (0) means on line, HIGH (1) means off line
        left_val = 0 if is_on_line(left_pos) else 1
        center_val = 0 if is_on_line(center_pos) else 1
        right_val = 0 if is_on_line(right_pos) else 1
        
        # Apply 3-sensor control logic
        if center_val == 0 and left_val == 1 and right_val == 1:
            # Forward
            robot.v_left = 15.0
            robot.v_right = 15.0
            action = "FORWARD"
        elif left_val == 0 and right_val == 1:
            # Turn Left
            robot.v_left = 6.0
            robot.v_right = 15.0
            action = "TURN LEFT"
        elif right_val == 0 and left_val == 1:
            # Turn Right
            robot.v_left = 15.0
            robot.v_right = 6.0
            action = "TURN RIGHT"
        elif left_val == 0 and center_val == 0 and right_val == 0:
            robot.v_left = 15.0
            robot.v_right = 15.0
            action = "ALL DETECT (FORWARD)"
        else:
            robot.v_left = 0.0
            robot.v_right = 0.0
            action = "STOP / SEARCH"
            
        robot.update(dt=0.05)
        
        if step % 20 == 0:
            print(f"Step {step:03d} | Pos: ({robot.x:6.2f}, {robot.y:6.2f}) | Theta: {math.degrees(robot.theta):6.1f} deg | Sensors: [L:{left_val} C:{center_val} R:{right_val}] | Action: {action}")

    print("==================================================")
    print(" Simulation completed successfully!")
    print("==================================================")

if __name__ == "__main__":
    run_simulation()
