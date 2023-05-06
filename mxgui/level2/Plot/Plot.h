#pragma once

#include <display.h>
#include <utils/collections/ResizableCircularBuffer.h>

#include <string>
#include <vector>

namespace mxgui
{

class Plot
{
public:
    Plot(Point upperLeft, Point lowerRight);

    void setYScale(float min, float max);

    void addDataPoint(float y);

    void draw(DrawingContext& dc);

private:
    std::string toString(float num, int precision);

    // Corner coordinates of the plot
    Point upperLeft, lowerRight;

    // Y scale
    float yMin = 0;
    float yMax = 1;

    // Data buffer
    Boardcore::ResizableCircularBuffer<float> buffer;

    bool first = true;
};

}  // namespace mxgui