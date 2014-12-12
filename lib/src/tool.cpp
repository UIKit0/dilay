#include <QMouseEvent>
#include <QPushButton>
#include <glm/glm.hpp>
#include "config.hpp"
#include "scene.hpp"
#include "state.hpp"
#include "tool.hpp"
#include "view/gl-widget.hpp"
#include "view/main-window.hpp"
#include "view/properties.hpp"
#include "view/properties/widget.hpp"
#include "view/tool/menu-parameters.hpp"
#include "view/tool/tip.hpp"
#include "view/util.hpp"

struct Tool::Impl {
  Tool*                  self;
  const bool             hasProperties;
  ViewToolMenuParameters menuParameters;
  ViewToolTip            toolTip;
  ConfigProxy            config;

  Impl (Tool* s, const ViewToolMenuParameters& p, const std::string& key) 
    : self           (s) 
    , hasProperties  (p.hasLabel ())
    , menuParameters (p)
    , config         ("/cache/tool/" + key + "/")
  {
    if (this->hasProperties) {
      QPushButton& close = ViewUtil::pushButton (QObject::tr ("Close"), true);
      this->properties ().setFooter (close);

      QObject::connect (&close, &QPushButton::clicked, [this] () {
        this->close ();
        State::setTool (nullptr);
      });
    }
    this->resetToolTip ();
  }

  void showToolTip () {
    State::mainWindow ().showToolTip (this->toolTip);
  }

  ToolResponse initialize () { 
    return this->self->runInitialize ();
  }

  void render () { 
    return this->self->runRender ( ); 
  }

  ToolResponse mouseMoveEvent (QMouseEvent& e) { 
    return this->self->runMouseMoveEvent (e);
  }

  ToolResponse mousePressEvent (QMouseEvent& e) {
    if (e.button () == Qt::RightButton) {
      return ToolResponse::None;
    }
    else {
      return this->self->runMousePressEvent (e);
    }
  }

  ToolResponse mouseReleaseEvent (QMouseEvent& e) {
    if (e.button () == Qt::RightButton) {
      this->close ();
      return ToolResponse::Terminate;
    }
    else {
      return this->self->runMouseReleaseEvent (e);
    }
  }

  ToolResponse wheelEvent (QWheelEvent& e) {
    return this->self->runWheelEvent (e);
  }

  void close () { 
    return this->self->runClose (); 
  }

  void updateGlWidget () {
    State::mainWindow ().glWidget ().update ();
  }

  ViewProperties& properties () {
    assert (this->hasProperties);
    return State::mainWindow ().properties ().tool ();
  }

  void resetToolTip () {
    this->toolTip.reset ();
    this->toolTip.add   (ViewToolTip::Button::Right, QObject::tr ("Close"));
  }
};

DELEGATE2_BIG3_SELF (Tool, const ViewToolMenuParameters&, const std::string&)
GETTER_CONST   (bool                         , Tool, hasProperties)
GETTER_CONST   (const ViewToolMenuParameters&, Tool, menuParameters)
DELEGATE       (void                         , Tool, showToolTip)
DELEGATE       (ToolResponse                 , Tool, initialize)
DELEGATE       (void                         , Tool, render)
DELEGATE1      (ToolResponse                 , Tool, mouseMoveEvent, QMouseEvent&)
DELEGATE1      (ToolResponse                 , Tool, mousePressEvent, QMouseEvent&)
DELEGATE1      (ToolResponse                 , Tool, mouseReleaseEvent, QMouseEvent&)
DELEGATE1      (ToolResponse                 , Tool, wheelEvent, QWheelEvent&)
DELEGATE       (void                         , Tool, close)
DELEGATE       (void                         , Tool, updateGlWidget)
DELEGATE       (ViewProperties&              , Tool, properties)
GETTER         (ViewToolTip&                 , Tool, toolTip)
DELEGATE       (void                         , Tool, resetToolTip)
GETTER         (ConfigProxy&                 , Tool, config)
