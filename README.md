# Physarum slime simulation
A GPU based simulation of the [Physarum polycephalum](https://en.wikipedia.org/wiki/Physarum_polycephalum) slime mold written in C++ and GLSL using the OpenGL graphics API. 

Inpired by [Sebastian Lague](https://github.com/SebLague/Slime-Simulation) and [Sage Jenson](https://cargocollective.com/sagejenson/physarum), based on a model proposed in a [2010 paper by Jeff Jones](https://uwe-repository.worktribe.com/output/980579).

## Configuration parameters
As defined in [config/settings.ini](config/settings.ini).

| Parameter | Description | Default value |
| --------- | ----------- | ------------- |
| FULLSCREEN      | Fullsceen mode                                          | FALSE
| DISPLAY_WIDTH   | Width of window                                         | 1000
| DISPLAY_HEIGHT  | Height of window                                        | 1000
| AGENT_COUNT     | Number of agents spawned                                | 50000
| SENSOR_ANGLE    | Angle at which agents sense stimuli                     | 45
| ROTATION_ANGLE  | Angle at which agents rotate                            | 45
| SENSOR_OFFSET   | Distance to where agents sense stimuli                  | 10
| SENSOR_SIZE     | Size of sensor                                          | 1
| STEP_SIZE       | Distance agents move at each simulation step            | 1
| SPAWN_MODE      | Agents spawn in circle(0) or rectangle(1)               | 0
| KILL_CHANCE     | Chance to eliminate agent at each simulation step       | 0.0
| TEXTURE_WIDTH   | Width of the texture the simulation lives on            | 1000
| TEXTURE_HEIGHT  | Height of the texture the simulation lives on           | 1000
| DECAY_SPEED_R   | Speed at which red decays in trail map                  | 0.005
| DECAY_SPEED_G   | Speed at which green decays at in trail map             | 0.005
| DECAY_SPEED_B   | Speed at which blue decays at in trail map              | 0.005
| DIFFUSE_SIZE    | Size of mean diffusion kernel                           | 1
| TRAIL_COLOR_R   | Red deposited by agents into trail map                  | 255
| TRAIL_COLOR_G   | Green deposited by agents into trail map                | 255
| TRAIL_COLOR_B   | Blue deposited by agents into trail map                 | 255
| STIM_RADIUS     | Radius of stimulus points deposited by left-clicking    | 10
| STIM_WEIGHT     | Weight at which stimulus points project into trail map  | 0.1
