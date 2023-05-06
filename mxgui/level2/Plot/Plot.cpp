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
        constexpr short int lineOffset = 6;
        constexpr short int arrowSize  = 6;

        const Point upperEnd(upperLeft.x() + lineOffset,
                             upperLeft.y() + lineOffset);
        const Point lowerEnd(upperLeft.x() + lineOffset,
                             lowerRight.y() - lineOffset);

        // Y axis line
        dc.line(upperEnd, lowerEnd, white);

        // Upper arrow
        dc.line(upperEnd, upperEnd + Point{-arrowSize / 2, arrowSize / 2},
                white);
        dc.line(upperEnd, upperEnd + Point{arrowSize / 2, arrowSize / 2},
                white);

        // Lower arrow
        dc.line(lowerEnd, lowerEnd + Point{-arrowSize / 2, -arrowSize / 2},
                white);
        dc.line(lowerEnd, lowerEnd + Point{arrowSize / 2, -arrowSize / 2},
                white);

        // Max and min values
        dc.setFont(droid11);
        dc.write(upperEnd + Point{lineOffset, 0}, toString(yMax, 0).c_str());
        dc.write(lowerEnd + Point{lineOffset, -droid11.getHeight()},
                 toString(yMin, 0).c_str());
    }

    // Draw data points
    for (size_t i = 1; i < buffer.count(); i++)
    {
        short int x1 =
            upperLeft.x() + buffer.getSize() - buffer.count() + i - 1;
        short int y1 = (buffer.get(i - 1) - yMin) / (yMax - yMin) *
                       (lowerRight.y() - upperLeft.y());

        short int x2 = upperLeft.x() + buffer.getSize() - buffer.count() + i;
        short int y2 = (buffer.get(i) - yMin) / (yMax - yMin) *
                       (lowerRight.y() - upperLeft.y());

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