# Tree Visualization Project

## Goal of the Project
The goal of this project is to visualize different types of trees using wxWidgets, demonstrating hierarchical data structures and their graphical representation. Three types of trees are implemented: a generic tree (`Tree<T>`), a binary tree (`Tree<int>`), and a binary tree of strings (`Tree<std::string>`).

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
2. **Node<T>**: Templated class representing a node in the tree structure.

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


