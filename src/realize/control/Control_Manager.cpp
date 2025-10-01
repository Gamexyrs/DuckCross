inline func Control_M::init(void) -> void {
  if(sys_acti::__actype == sys_acti::ActivityType::ControlLayout) {
    Control_M::__move.setCenter(sf::Renderable::getViewPosition()
                             + rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["Control_Move"]));
    Control_M::__move.reset();
    
    Control_M::__attk.setCenter(sf::Renderable::getViewPosition() + _Renderer.getView().getSize()
                              - rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["Control_Attack"]));
    Control_M::__attk.reset();
    
    Control_M::__obsr.setCenter(sf::align(sf::Vector2f{static_cast<float>(Control_M::__obsr.getEdgeRadius()),
    static_cast<float>(Control_M::__obsr.getEdgeRadius())} * 2, sf::Renderable::getViewRect(), sf::Align::TR)
    - rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["Control_Observe"]));
    Control_M::__obsr.reset();
  }
  
  Control_M::__attk.getIner().getBase().setTexture(res::__tex_ctrl_attk.get());
  Control_M::__obsr.getIner().getBase().setTexture(res::__tex_ctrl_obsr.get());
}

inline func Control_M::draw(void) -> void {
  if(sys_acti::__actype != sys_acti::ActivityType::ControlLayout) {
    Control_M::__move.setCenter(sf::Renderable::getViewPosition()
                              + rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["Control_Move"]));
  
    Control_M::__attk.setCenter(sf::Renderable::getViewPosition() + _Renderer.getView().getSize()
                              - rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["Control_Attack"]));
    
    Control_M::__obsr.setCenter(sf::align(sf::Vector2f{static_cast<float>(Control_M::__obsr.getEdgeRadius()),
    static_cast<float>(Control_M::__obsr.getEdgeRadius())} * 2, sf::Renderable::getViewRect(), sf::Align::TR)
    - rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["Control_Observe"]));
  }
  
  if(!Control_M::__once_hide)
    sf::Renderable::draw(Control_M::__move, Control_M::__attk, Control_M::__obsr);
  else Control_M::__once_hide = false;
}

inline func Control_M::event(void) -> void {
  if(Char_M::Duck::__v->noBlood() && sys_acti::__actype != sys_acti::ActivityType::ControlLayout) {
    Control_M::__move_move = {};
    Control_M::__move_attk = {};
    Control_M::__move_obsr = {};
    Control_M::__angle_attk = 0;
    return;
  }
  
  // To support the fingerEvent, banned the SFML sensor event update!
  Control_M::__move.pollEvent(sys::__event);
  Control_M::__move_move = 0.05f * Control_M::__move.getData().v_LengthToCenter_Coordinates;
  
  Control_M::__attk.pollEvent(sys::__event);
  Control_M::__angle_attk =         Control_M::__attk.getData().v_Angle;
  Control_M::__move_attk = 0.08f * Control_M::__attk.getData().v_LengthToCenter_Coordinates;
  
  if(Control_M::__obsr.pollEvent(sys::__event))
     Control_M::__move_obsr = 0.08f * Control_M::__obsr.getData().v_LengthToCenter_Coordinates;
  // 陀螺仪
  else if(Control_M::__enabled_gyroscope) {
    sf::Vector3f __v{sf::Sensor::getValue(sf::Sensor::Gyroscope)};
    Control_M::__gyroscope_move += 0.5f * sf::Vector2f{__v.x, __v.y};
    Control_M::__obsr.setMove(Control_M::__gyroscope_move);
    Control_M::__move_obsr = 0.08f * Control_M::__obsr.getData().v_LengthToCenter_Coordinates;
  } else Control_M::__move_obsr = {};
}
