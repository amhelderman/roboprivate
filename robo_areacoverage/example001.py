

print("hello world")


class EnvironmentMap:

    def __init__(self):
        self.list_of_corners = [(0, 0), (0, 1), (1, 1), (1, 0)]
    
    def get_corners(self):
        return self.list_of_corners
    
    def is_inside_map(self, x, y):
        # If inside the polygon defined by the given list of corners
        if x < 0 or y < 0:
            return False
        elif x > 1 or y > 1:
            return False
        else:
            return True

def check_if_path_covers_map(path, environment_map):
    pass



def plan(environment_map):
    # CHoose a starting spot 
    starting_spot = environment_map.get_corners()[0]

    # Choose a goal spot
    goal_spot = environment_map.get_corners()[2]

    # # Make a path of coordinates each 0.1 meters apart
    # path = []
    # path.append(starting_spot)

    # # Use a breadth first search to find a short path that covers the whole map 
    # # (with a 0.1 meter resolution)
    # point_queue = []
    # point_queue.append(starting_spot)

    # while len(point_queue) > 0:
    #     point = point_queue.pop(0)
    #     if point == goal_spot:
    #         break
    #     else:
    #         # Add all the neighbors to the queue
    #         neighbors = get_neighbors(point)
    #         for neighbor in neighbors:
    #             if environment_map.is_inside_map(neighbor[0], neighbor[1]):
    #                 point_queue.append(neighbor)
    #                 path.append(neighbor)



def main():
    raise Exception("Hold on - not implemented fully.")

    env_map = EnvironmentMap()
    plan(env_map)

if __name__ == "__main__":
    main()