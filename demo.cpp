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
    Tree<Complex> *tree3ari; // Pointer to a tree of complex
    Tree<int> * treeBinary;
    Tree<std::string>* treeBinaryString;

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
    auto *cRoot = new Complex(0,0);
    auto *c1 = new Complex(1,1);
    auto *c2 = new Complex(2,2);
    auto *c3 = new Complex(3,3);
    auto *c4 = new Complex(4,4);
    auto *c5 = new Complex(5,5);
    auto *c6 = new Complex(6,6);
    auto *c7 = new Complex(7,7);
    auto *c8 = new Complex(8,8);

    tree3ari = new Tree<Complex>(*cRoot, 3); // Create a tree with root value 1 and some branching factor
    Node<Complex> *root = tree3ari->getRoot(); // Get the root node
    auto *child1 = new Node<Complex>(*c1, 3); // Create child node with value 3 and some branching factor
    auto *child2 = new Node<Complex>(*c2, 3); // Create another child node

    // Add children to the root
    tree3ari->add_sub_node(root, child1);
    tree3ari->add_sub_node(root, child2);

    // Add grandchildren to the first child
    tree3ari->add_sub_node(child1, new Node<Complex>(*c3, 3));
    tree3ari->add_sub_node(child1, new Node<Complex>(*c4, 3));
    tree3ari->add_sub_node(child1, new Node<Complex>(*c5, 3));

    // Add grandchildren to the second child
    tree3ari->add_sub_node(child2, new Node<Complex>(*c6, 3));
    tree3ari->add_sub_node(child2, new Node<Complex>(*c7, 3));
    tree3ari->add_sub_node(child2, new Node<Complex>(*c8, 3));

    treeBinary = new Tree<int>(1,2);
    Node<int> *rootBin = treeBinary->getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(3, 2);
    treeBinary->add_sub_node(rootBin, left);
    treeBinary->add_sub_node(rootBin, right);
    treeBinary->add_sub_node(left, new Node<int>(4,2));
    treeBinary->add_sub_node(left, new Node<int>(5,2));
    treeBinary->add_sub_node(right, new Node<int>(6,2));
    treeBinary->add_sub_node(right, new Node<int>(7,2));
    //expected 4, 5, 2, 6, 7, 3, 1
    for (auto it = treeBinary->begin_post_order(); it != treeBinary->end_post_order(); ++it) {
        std::cout<< (*it)->getValue() << " ";
    }
    std::cout<<" \n";


    treeBinaryString = new Tree<std::string>("root", 2);

    // Adding nodes to create a tree with 15 nodes
    Node<std::string> *root2 = treeBinaryString->getRoot();
    Node<std::string> *left2 = new Node<std::string>("left", 2);
    Node<std::string> *right2 = new Node<std::string>("right", 2);
    treeBinaryString->add_sub_node(root2, left2);
    treeBinaryString->add_sub_node(root2, right2);

    treeBinaryString->add_sub_node(left2, new Node<std::string>("a",2));
    treeBinaryString->add_sub_node(left2, new Node<std::string>("b",2));
    treeBinaryString->add_sub_node(right2, new Node<std::string>("c",2));
    treeBinaryString->add_sub_node(right2, new Node<std::string>("d",2));

    treeBinaryString->add_sub_node(right2->getChildren()[LEFT_CHILD], new Node<std::string>( "e",2));
    treeBinaryString->add_sub_node(right2->getChildren()[LEFT_CHILD], new Node<std::string>( "f",2));

    treeBinaryString->add_sub_node(right2->getChildren()[RIGHT_CHILD], new Node<std::string>( "g",2));
    treeBinaryString->add_sub_node(right2->getChildren()[RIGHT_CHILD], new Node<std::string>( "h",2));

    treeBinaryString->add_sub_node(left2->getChildren()[LEFT_CHILD], new Node<std::string>( "i",2));
    treeBinaryString->add_sub_node(left2->getChildren()[LEFT_CHILD], new Node<std::string>( "j",2));

    treeBinaryString->add_sub_node(left2->getChildren()[RIGHT_CHILD], new Node<std::string>( "k",2));
    treeBinaryString->add_sub_node(left2->getChildren()[RIGHT_CHILD], new Node<std::string>( "l",2));

    //expected: i a j left k b l root e c f right g d h
    for (auto it = treeBinaryString->begin_in_order(); it != treeBinaryString->end_in_order(); ++it) {
        std::cout << (*it)->getValue() << " ";
    }
    std::cout <<"\n";
}

// Event handler for paint events
void MyFrame::OnPaint(wxPaintEvent &event) {
    wxBufferedPaintDC dc(this); // Double-buffered device context to prevent flickering
    dc.Clear(); // Clear the drawing area
    // Draw the tree starting from the specified coordinates
    tree3ari->drawTree(dc, WIDTH / 2, 50, WIDTH, HIGHT);
    treeBinary->drawTree(dc,WIDTH / 2, 300, WIDTH, HIGHT);
    treeBinaryString->drawTree(dc,WIDTH / 2, 550, WIDTH, HIGHT);

}
