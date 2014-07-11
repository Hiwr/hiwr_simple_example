hiwr\_simple\_example
===============================================
 
The hiwr\_simple\_example ROS package is an example to show use of facetracking and touchscreen event handling. Hiwr will follow people with the head and turn grumpy when touching its screen. 


Contributing
----------------------

Contributions via pull request are welcome and may be included under the
same license as below.

Copyright
----------------------

hiwr\_simple\_example, except where otherwise noted, is released under the
[Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html).
See the LICENSE file located in the root directory.

Build
----------------------
It requires hiwr\_msg to work properly

Execution
----------------------
Make sure that your project is compiled and sourced.

To start hiwr\_simple\_example, do the following (assuming you
have a working ROS core running):

Launch using roslaunch:

    $ roslaunch hiwr_simple_example hiwr_simple_example.launch 

Launch from another launchfile:

    <include file="$(find hiwr\_simple\_example)/hiwr_simple_example.launch" />
 
Node
----------------------

### Subscribed Topics

* `/hiwr_tired/brightness`
 * The brightness in the room

* `/hiwr_touchscreen/touch_event`
  * The event triggered when touching the screen

### Published Topics

* `/scenario/state`
  * Send the new state to display on the screen
