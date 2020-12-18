#include "pyramidclass.h"
#include <QVector>
#include <QLine>

PyramidClass::PyramidClass(float w, float h) :
    AbstractPaintitng3D(),
    width(w),
    height(h)
{
    setSize(w, h);

}

void PyramidClass::setSize(float w, float h){
    points[0] = {(-1.0f * w/2.0f), (-1.0f * h/2.0f), w/2.0f          , 1};
    points[1] = {w/2.0f          , (-1.0f * h/2.0f), w/2.0f          , 1};
    points[2] = {w/2.0f          , (-1.0f * h/2.0f), (-1.0f * w/2.0f), 1};
    points[3] = {(-1.0f * w/2.0f), (-1.0f * h/2.0f), (-1.0f * w/2.0f), 1};
    points[4] = {0.0f            , h/2.0f          , 0.0f            , 1}; // вершина
}

void PyramidClass::calculatePolygons() {
    polygons->push_back(new RectPolygon3D(points[0], points[1], points[2], points[3]));
    polygons->push_back(new Polygon3D(points[0], points[4], points[1]));
    polygons->push_back(new Polygon3D(points[1], points[4], points[2]));
    polygons->push_back(new Polygon3D(points[2], points[4], points[3]));
    polygons->push_back(new Polygon3D(points[3], points[4], points[0]));

}


void PyramidClass::setWidth(float w){
    width = w;
    setSize(width, height);

}
void PyramidClass::setHeight(float h){
    height = h;
    setSize(width, height);

}
