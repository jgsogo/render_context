#include "line.h"

namespace primitives {

    std::vector<Vector2Mm> Line::getPolyline() const {
        return {start, end};
    }

    void Line::doRender(RenderContext &render) const {
        render.drawLine(start, end, color, thickness);
    }

}