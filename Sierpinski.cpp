#include "simpio.h"
#include "gwindow.h"
#include "gobjects.h"
#include "math.h"

using namespace std;

struct vertices {
    GPoint first;
    GPoint second;
    GPoint third;
    vertices (GPoint f = GPoint(0,0), GPoint s =  GPoint(0,0),GPoint t = GPoint(0,0)) {
        first = f;
        second = s;
        third = t;
    }
};
//this method draws triangle
void drawTriangle(GPoint p1, GPoint p2, GPoint p3, GWindow & gw) {
    gw.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    gw.drawLine(p2.getX(), p2.getY(), p3.getX(), p3.getY());
    gw.drawLine(p1.getX(), p1.getY(), p3.getX(), p3.getY());
}

//this method finds middle point of the edge
GPoint middle(GPoint & p1, GPoint & p2) {
    GPoint midpoint((p1.getX() + p2.getX()) / 2, (p1.getY() + p2.getY()) / 2);
    return midpoint;
}
//this method draws triangles recursively
void recursiveDrawing(vertices triangle, GWindow & gw, int edge, int order) {
    if(order != 0) {
        drawTriangle(middle(triangle.first, triangle.second), middle(triangle.second, triangle.third), 
            middle(triangle.first, triangle.third), gw);

        recursiveDrawing(vertices(triangle.first, middle(triangle.first, triangle.second), 
            middle(triangle.first, triangle.third)), gw, edge / 2, order - 1);

        recursiveDrawing(vertices(middle(triangle.first, triangle.second), triangle.second,
            middle(triangle.second, triangle.third)), gw, edge / 2, order - 1);

        recursiveDrawing(vertices(middle(triangle.first, triangle.third), 
            middle(triangle.second, triangle.third), triangle.third), gw, edge / 2, order - 1);
    }
}

//this method draws first triangle
vertices drawStartingTriangle(GWindow & gw, int edge) {
    vertices res;
    res.second = gw.drawPolarLine(gw.getWidth()/2 -  edge/2, gw.getHeight() / 2 + (edge * sqrt(3.0)) / 4, edge, 60);
    res.third = gw.drawPolarLine(res.second, edge, 360 - 60);
    res.first = gw.drawPolarLine(res.third, edge, 360 - 3 * 60);
    return res;
}

//this method gets size of the triangle edge and number of order 
int main() {
    int edge = getInteger();
    int order = getInteger();
    GWindow gw;
    vertices triangle = drawStartingTriangle(gw, edge);
    recursiveDrawing(triangle, gw, edge, order);
    return 0;
}