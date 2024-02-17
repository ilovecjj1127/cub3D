# cub3D
My first RayCaster with miniLibX

## the rules of the description file `.cub` 
- The map is composed of only 6 possible characters: 0 for an empty space, for a wall, N,S,E or W for the play's start position and spawning orientation.
- The map is surrounded by walls(1), otherwise an error returned.
- The map content has to be the last, others can be set in any order and be separated by one or more lines.
- Each type of info from a Single element can be separated by one or more spaces.
- Type Identifier: start with NO/SO/WE/EA/F/C
