/* This file is part of Dilay
 * Copyright © 2015 Alexander Bau
 * Use and redistribute under the terms of the GNU General Public License
 */
#ifndef VIEW_UTIL
#define VIEW_UTIL

#include <functional>
#include <glm/fwd.hpp>

class ViewDoubleSlider;
class QAbstractSpinBox;
class QButtonGroup;
class QCheckBox;
class QDoubleSpinBox;
class QFrame;
class QMouseEvent;
class QPoint;
class QPushButton;
class QRadioButton;
class QSpinBox;
class QString;
class QToolButton;

namespace ViewUtil {
  QSpinBox&         spinBox        (int, int, int, int = 1);
  QDoubleSpinBox&   spinBox        (float, float, float, float);
  QPushButton&      pushButton     (const QString&, bool = false);
  QToolButton&      toolButton     (const QString&);
  QRadioButton&     radioButton    (const QString&, bool = false);
  QCheckBox&        checkBox       (const QString&, bool = false);
  ViewDoubleSlider& slider         (unsigned short, float, float, float, unsigned short = 1);
  QFrame&           horizontalLine ();
  glm::uvec2        toUVec2        (const QPoint&);
  glm::uvec2        toUVec2        (const QMouseEvent&);
  glm::ivec2        toIVec2        (const QPoint&);
  glm::ivec2        toIVec2        (const QMouseEvent&);
  void              connect        (const QSpinBox&, const std::function <void (int)>&);
  void              connect        (const QDoubleSpinBox&, const std::function <void (double)>&);
  void              connect        (const QPushButton&, const std::function <void ()>&);
  void              connect        (const QButtonGroup&, const std::function <void (int)>&);
  void              connect        (const QCheckBox&, const std::function <void (bool)>&);
  void              connect        (const QRadioButton&, const std::function <void (bool)>&);
  void              connect        (const ViewDoubleSlider&, const std::function <void (float)>&);
  QWidget&          stretcher      (bool, bool);
  void              deselect       (QAbstractSpinBox&);
  bool              question       (QWidget&, const QString&);
  void              error          (QWidget&, const QString&);
  void              about          (QWidget&, const QString&);
};

#endif
