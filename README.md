# Tree Visualization Project

## Goal of the Project
The goal of this project is to scan and visualize different types of trees using one generic class.

## Hierarchy of Classes
### Tree Visualization Classes
1. **MyApp**: Inherits from `wxApp`, initializes the application and creates the main frame.
2. **MyFrame**: Inherits from `wxFrame`, represents the main application window where trees are visualized.
   - Contains instances of:
     - `Tree<Complex>` (`tree3ari`)
     - `Tree<int>` (`treeBinary`)
     - `Tree<std::string>` (`treeBinaryString`)
   - Handles paint events to draw trees on the frame.


### Data Structures
1. **Tree<T>**: Templated class representing a generic tree structure.
   - **Iterators**: Provided for different tree traversals:
     - `begin_pre_order()`, `end_pre_order()`
     - `begin_post_order()`, `end_post_order()`
     - `begin_in_order()`, `end_in_order()`

2. **Node<T>**: Represents a node in the tree, storing data of type `T` and managing child nodes.
   - **Methods**: Includes methods for adding children, accessing node data, and comparison operators.


### Other Supporting Classes
- **Complex**: Represents complex numbers.
- **wxWidgets**: Used for GUI and graphics rendering.

## Libraries Used
- **wxWidgets**: Cross-platform GUI library used for creating the graphical user interface and handling events.

## How to Compile and Run the Project
### Prerequisites
1. **wxWidgets**: Ensure wxWidgets is installed on your system. You can download it from [wxWidgets website](https://www.wxwidgets.org/downloads/).
2. **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., g++, clang++).

### Compilation Steps
1. **Clone the Repository:**
-git clone https://github.com/your/repository.git
-cd repository

2. **Compile the Project:**
- Replace in the makefile `g++` with your compiler command if different.
- type "make tree" on the terminal
This will launch the application, displaying the graphical visualization of the trees.

## Example Output
Upon running the application, you will see three visual representations of trees: a generic tree of complex numbers, a binary tree of integers, and a binary tree of strings.


