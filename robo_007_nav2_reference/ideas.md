
Potentially,
A collection of robotics software resources for me.

One day it would be nice to aggregate them all into a more coherent system.


# Brainstorming Notes

## Potential Goals
* Act as a robotics stack for reference
* If modular enough, maybe we can pull things out for use in other projects 
* Act as a testing ground for new ideas selected from reported robotics research

## Imagined Structure
* A consistent build system 
    * Relevant? colcon, catkin, Docker

Expand on ROS?


## Potential Components
* Simulations
    * Gazebo 
    * 
* Operating Systems
    * NuttX - heavy in PX4 world
* Platforms 
    * PX4 platforms
* ROS or frameworks
* Messaging Systems: uOrb, MQTT, all working at different levels


If the robotics stacks are all like layers stacked on each other, and each layer has 
various solutions but they don't mix well together, you might find that 
building a matrix of all modules interoperable with each other infeasible. 

Not limited to robotics either.

#  Next steps 

I think the first iteration is going to be this:


# Build 

```
cd nuttxspace 
docker build . -t nuttxbuilder
docker run -it --rm nuttxbuilder /bin/bash 
# Build stuff in nuttx, WIP.
```



# Rough Diagram 

``` 
flowchart
subgraph CI
GithubActions 
CircleCI 
GitlabCI 
end 

subgraph Network
    ROSNetworking
    MQTT
    OtherRobotsInSwarm
    subgraph Cloud
        ElasticSearch
        Kibana 
        SQL
    end
end
subgraph UI
    QGroundControl 
    WebInterfaces 
    QtInterfaces 
end 

subgraph Robot

    subgraph MainBoardSoftware

        subgraph BusinessApplications
            MaterialHandling
            DataCollection
            Manufacturing
        end

        subgraph RobotLogistics
            RoboticSwarmControllers 
            TrafficControl
            SafetySystems
            BatteryChargingManagement
        end 
        subgraph NavigationStack
            PX4 --- ROSNavigation
            Ardupilot
            CustomSensorFusion --- ROSNavigation
            ROSNavigation --- amcl --- Cartographer
        end
        subgraph OS
            nuttx 
            FreeRTOS 
            Ports
            Serial
        end
        subgraph platform
            board 
            qemu
        end 
    end 
    otherHardware

end

subgraph environment
subgraph simulationEnvironment
gazebo
jmavsim
end
realworld
end 

CI --> Network
UI --> Network
OS --> platform 
BusinessApplications --> RobotLogistics
RobotLogistics --> NavigationStack
NavigationStack --> OS 
Ports <--> Network
Serial <--> otherHardware
otherHardware <--> environment

subgraph user
CustomerUser
Developer
end 
CustomerUser --> UI
Developer --> CI 

Developer --> OS
```
