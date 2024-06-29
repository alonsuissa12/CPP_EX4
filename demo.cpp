#include <wx/wx.h>
#include "Tree.hpp"
#include "Node.hpp"
#include "Complex.hpp"

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
    Tree<Complex> *tree; // Pointer to a tree of integers

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
    Complex *cRoot = new Complex(0,0);
    Complex *c1 = new Complex(1,1);
    Complex *c2 = new Complex(2,2);
    Complex *c3 = new Complex(3,3);
    Complex *c4 = new Complex(4,4);
    Complex *c5 = new Complex(5,5);
    Complex *c6 = new Complex(6,6);
    Complex *c7 = new Complex(7,7);
    Complex *c8 = new Complex(8,8);

    tree = new Tree<Complex>(*cRoot, 3); // Create a tree with root value 1 and some branching factor
    Node<Complex> *root = tree->getRoot(); // Get the root node
    Node<Complex> *child1 = new Node<Complex>(*c1, 3); // Create child node with value 3 and some branching factor
    Node<Complex> *child2 = new Node<Complex>(*c2, 3); // Create another child node

    // Add children to the root
    tree->add_sub_node(root, child1);
    tree->add_sub_node(root, child2);

    // Add grandchildren to the first child
    tree->add_sub_node(child1, new Node<Complex>(*c3, 3));
    tree->add_sub_node(child1, new Node<Complex>(*c4,3));
    tree->add_sub_node(child1, new Node<Complex>(*c5,3));

    // Add grandchildren to the second child
    tree->add_sub_node(child2, new Node<Complex>(*c6,3));
    tree->add_sub_node(child2, new Node<Complex>(*c7,3));
    tree->add_sub_node(child2, new Node<Complex>(*c8,3));
}

// Event handler for paint events
void MyFrame::OnPaint(wxPaintEvent &event) {
    wxBufferedPaintDC dc(this); // Double-buffered device context to prevent flickering
    dc.Clear(); // Clear the drawing area
    // Draw the tree starting from the specified coordinates
    tree->drawTree(dc, WIDTH / 2, 50, WIDTH, HIGHT);
}
