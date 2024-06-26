#include <wx/wx.h>
#include "Tree.hpp"
#include "Node.hpp"

#define WIDTH 1200
#define HIGHT 800

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString &title);

    void OnPaint(wxPaintEvent &event);

private:
    Tree<int> *tree;

wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
                EVT_PAINT(MyFrame::OnPaint)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    try {
        MyFrame *frame = new MyFrame("Tree Visualization");
        frame->Show(true);
        return true;
    } catch (const std::exception &e) {
        wxLogError("Unhandled exception: %s", e.what());
        return false;
    } catch (...) {
        wxLogError("Unhandled unknown exception");
        return false;
    }
}

MyFrame::MyFrame(const wxString &title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(WIDTH, HIGHT)) {
    // Create a sample tree
    tree = new Tree<int>(1, 3);
    Node<int> *root = tree->getRoot();
    Node<int> *child1 = new Node<int>(3, 2);
    Node<int> *child2 = new Node<int>(3, 2);
    tree->add_sub_node(root, child1);
    tree->add_sub_node(root, child2);
    tree->add_sub_node(child1, new Node<int>(3, 2));
    tree->add_sub_node(child1, new Node<int>(3, 2));
    tree->add_sub_node(child1, new Node<int>(3, 2));
    tree->add_sub_node(child2, new Node<int>(3, 2));
    tree->add_sub_node(child2, new Node<int>(3, 2));
    tree->add_sub_node(child2, new Node<int>(3, 2));


}

void MyFrame::OnPaint(wxPaintEvent &event) {
    wxBufferedPaintDC dc(this);
    dc.Clear();
    tree->drawTree(dc, WIDTH/2, 50, WIDTH, HIGHT);  // Adjust the initial coordinates and dimensions as needed
    //std::cout << tree;
}
