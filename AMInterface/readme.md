The Arduino MEGA 2560 under the interface does the following:

1. Check which tiles are placed. The tiles individually pull an assigned digital high on the Arduino when placed in their designated docking positions on the panel. These values are put into an array. 1 being "tile = placed", 0 being "tile = absent". Subsequently, the lights are turned ON or OFF on the corners of each tile depending on whether they are placed, or not.

2. 
