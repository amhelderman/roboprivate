import numpy as np
import matplotlib.pyplot as plt
import math

import json


# To avoid `UserWarning: FigureCanvasAgg is non-interactive, and thus cannot be shown` error
import matplotlib 
matplotlib.use('TkAgg')


def simulate_lidar_scan(x, y, theta, environment_map, num_rays=360, max_distance=10):
    """
    Simulate a LiDAR scan given the robot's position and orientation.
    """
    angles = np.linspace(0, 2*np.pi, num_rays)
    scan = []
    for angle in angles:
        for r in np.linspace(0, max_distance, 100):
            dx = r * math.cos(angle + theta)
            dy = r * math.sin(angle + theta)
            
            testx = int(x + dx)
            testy = int(y + dy)
            if testx < 0 or testx >= environment_map.shape[0] or testy < 0 or testy >= environment_map.shape[1]:
                scan.append(max_distance)
                break
            elif environment_map[int(x + dx), int(y + dy)] == 1:
                scan.append(r)
                break
            else:
                scan.append(max_distance)
    return scan

def create_environment():
    """
    Create a 10x10 room with a column at (8, 6) with a radius of 1m.
    """
    environment_map = np.zeros((10, 10))
    for x in range(10):
        for y in range(10):
            if (x-8)**2 + (y-6)**2 <= 1**2:
                environment_map[x, y] = 1
    return environment_map

def simulate_robot_movement(initial_position, speed=1, rate=1, duration=7):
    """
    Simulate the robot's movement, assuming it moves straight forward.
    """
    x, y, theta = initial_position
    environment_map = create_environment()
    positions = [(x, y, theta)]
    scans = [simulate_lidar_scan(x, y, theta, environment_map)]

    for t in range(1, duration * rate + 1):
        x += speed / rate * math.cos(theta)
        y += speed / rate * math.sin(theta)
        positions.append((x, y, theta))
        scans.append(simulate_lidar_scan(x, y, theta, environment_map))

    return positions, scans

def main():
    initial_position = (1, 1, np.pi/4)  # Starting at (1,1) facing up and right.
    positions, scans = simulate_robot_movement(initial_position)

    # Save scans and control commands to a json file 
    data = {
        "positions": positions,
        "scans": scans
    }
    with open("data.json", "w") as f:
        json.dump(data, f)
        
    # Visualization (optional)
    plt.figure(figsize=(10, 10))
    environment_map = create_environment()
    plt.imshow(environment_map.T, cmap='gray', origin='lower', extent=[0, 10, 0, 10])
    xs, ys, _ = zip(*positions)
    plt.plot(xs, ys, 'r-')
    plt.show()
    

if __name__ == "__main__":
    main()
