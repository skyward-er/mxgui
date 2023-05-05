#include "Plot.h"

#include <miosix.h>
#include <misc_inst.h>

#include <sstream>

using namespace std;

namespace mxgui
{

Plot::Plot(Point upperLeft, Point lowerRight)
    : upperLeft(upperLeft), lowerRight(lowerRight),
      buffer(lowerRight.x() - upperLeft.x())
{
    // ...
}

void Plot::setXScale(float min, float max)
{
    xMin = min;
    xMax = max;
}

void Plot::setYScale(float min, float max)
{
    yMin = min;
    yMax = max;
}

void Plot::addDataPoint(float y) { buffer.put(y); }

void Plot::draw(DrawingContext& dc)
{
    // Clear plot area
    dc.clear(upperLeft, lowerRight, black);

    // Draw axes
    {
        // Y axis line
        dc.line({upperLeft.x() + 6, upperLeft.y() + 6},
                {upperLeft.x() + 6, lowerRight.y() - 6}, white);

        // Upper arrow
        dc.line({upperLeft.x() + 6, upperLeft.y() + 6},
                {upperLeft.x() + 3, upperLeft.y() + 10}, white);
        dc.line({upperLeft.x() + 6, upperLeft.y() + 6},
                {upperLeft.x() + 9, upperLeft.y() + 10}, white);

        // Lower arrow
        dc.line({upperLeft.x() + 6, lowerRight.y() - 6},
                {upperLeft.x() + 3, lowerRight.y() - 10}, white);
        dc.line({upperLeft.x() + 6, lowerRight.y() - 6},
                {upperLeft.x() + 9, lowerRight.y() - 10}, white);

        // Max and min values
        dc.setFont(droid11);
        dc.write({upperLeft.x() + 12, upperLeft.y() + 2},
                 toString(yMax, 0).c_str());
        dc.write({upperLeft.x() + 12, lowerRight.y() - 11 - 2},
                 toString(yMin, 0).c_str());
    }

    // Draw data points
    for (int i = 1; i < buffer.count(); i++)
    {
        short int x1 =
            upperLeft.x() + buffer.getSize() - buffer.count() + i - 1;
        short int y1 = buffer.get(i - 1) * (lowerRight.y() - upperLeft.y());

        short int x2 = upperLeft.x() + buffer.getSize() - buffer.count() + i;
        short int y2 = buffer.get(i) * (lowerRight.y() - upperLeft.y());

        dc.line({x1, y1}, {x2, y2}, white);
    }
}

string Plot::toString(float num, int precision)
{
    ostringstream ss;
    ss.precision(precision);
    ss << num;
    return ss.str();
}

}  // namespace mxgui