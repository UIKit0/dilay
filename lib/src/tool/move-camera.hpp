/* This file is part of Dilay
 * Copyright © 2015 Alexander Bau
 * Use and redistribute under the terms of the GNU General Public License
 */
#ifndef DILAY_TOOL_MOVE_CAMERA
#define DILAY_TOOL_MOVE_CAMERA

#include <glm/fwd.hpp>
#include "configurable.hpp"

class Config;
class State;
class QMouseEvent;
class QWheelEvent;

class ToolMoveCamera : public Configurable {
  public:
    DECLARE_BIG3 (ToolMoveCamera, const Config&)

    void snap            (State&, bool);
    void resetGazePoint  (State&);

    void mouseMoveEvent  (State&, const QMouseEvent&);
    void mousePressEvent (State&, const QMouseEvent&);
    void wheelEvent      (State&, const QWheelEvent&);

  private:
    IMPLEMENTATION

    void runFromConfig (const Config&);
};

#endif
