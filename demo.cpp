#include <wx/wx.h>
#include "Tree.hpp"
#include "Node.hpp"

#define WIDTH 1200
#define HIGHT 800

// MyApp class definition, derived from wxApp
class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

// MyFrame class definition, derived from wxFrame
class MyFrame : public wxFrame {
public:
    MyFrame(const wxString &title);

    // Event handler for paint events
    void OnPaint(wxPaintEvent &event);

private:
    Tree<int> *tree; // Pointer to a tree of integers

wxDECLARE_EVENT_TABLE();
};

// Event table for MyFrame, connecting events to their handlers
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame) // before connecting event
EVT_PAINT(MyFrame::OnPaint) // Connect paint events to the OnPaint handler
wxEND_EVENT_TABLE() // after connecting event

// define to the wx that this is the app we want to run
wxIMPLEMENT_APP(MyApp);

// Initialization function for the application -  this function will run when the application will start
bool MyApp::OnInit() {
    try {
        // Create the main application window (frame)
        MyFrame *frame = new MyFrame("Tree Visualization");
        frame->Show(true); // will trigger PAINT event which will trigger the onPaint function
        return true;
    } catch (const std::exception &e) {
        wxLogError("Unhandled exception: %s", e.what()); // Log any exceptions
        return false;
    } catch (...) {
        wxLogError("Unhandled unknown exception"); // Log any unknown exceptions
        return false;
    }
}

// Constructor for the main application window (frame)
MyFrame::MyFrame(const wxString &title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(WIDTH, HIGHT)) {
    // Center the window on the screen
    Centre();
    // Create a sample tree
    tree = new Tree<int>(1, 3); // Create a tree with root value 1 and some branching factor
    Node<int> *root = tree->getRoot(); // Get the root node
    Node<int> *child1 = new Node<int>(3, 2); // Create child node with value 3 and some branching factor
    Node<int> *child2 = new Node<int>(3, 2); // Create another child node

    // Add children to the root
    tree->add_sub_node(root, child1);
    tree->add_sub_node(root, child2);

    // Add grandchildren to the first child
    tree->add_sub_node(child1, new Node<int>(3, 2));
    tree->add_sub_node(child1, new Node<int>(3, 2));
    tree->add_sub_node(child1, new Node<int>(3, 2));

    // Add grandchildren to the second child
    tree->add_sub_node(child2, new Node<int>(3, 2));
    tree->add_sub_node(child2, new Node<int>(3, 2));
    tree->add_sub_node(child2, new Node<int>(3, 2));
}

// Event handler for paint events
void MyFrame::OnPaint(wxPaintEvent &event) {
    wxBufferedPaintDC dc(this); // Double-buffered device context to prevent flickering
    dc.Clear(); // Clear the drawing area
    // Draw the tree starting from the specified coordinates
    tree->drawTree(dc, WIDTH / 2, 50, WIDTH, HIGHT);
    // std::cout << tree; // Optionally, print the tree to the console
}
