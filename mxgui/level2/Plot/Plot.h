#pragma once

#include <display.h>
#include <utils/collections/ResizableCircularBuffer.h>

#include <map>
#include <string>
#include <vector>

namespace mxgui
{

class Plot
{
public:
    Plot(Point upperLeft, Point lowerRight);

    void setYScale(float min, float max);

    void addDataPoint(float y, int index, Color color);

    void draw(DrawingContext& dc);

private:
    std::string toString(float num, int precision);

    // Corner coordinates of the plot
    Point upperLeft, lowerRight;

    // Y scale
    float yMin = 0;
    float yMax = 1;

    // Data buffers
    std::map<int, Boardcore::ResizableCircularBuffer<float>*> buffers;
    std::map<int, Color> colors;

    bool first = true;
};

}  // namespace mxgui