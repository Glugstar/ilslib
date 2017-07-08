# ilslib
"Interface Layout Scheme" is a C++ library for GUI layouts.

The purpose of this library is to manage abstract GUI objects into specific layouts. It does not include functions that know how to draw objects, a custom adapter is needed for that.

The library classes are organized into a hierarchy. Display objects are almost abstract and the actual GUI element implementations are different objects, defined by the library user. These objects are placed inside containers that have specific layout properties. The containers can be placed inside other containers in a recursive layout format.

Given a container structure and layouts, the library calculates the order and coordinates where each component goes on the screen. The library user is reponsible for actually drawing the final result.

Similarily, the library manages user input, like keyboard and mouse activity and finally outputs the action details that could be taken, as specified by assigned callback functions.