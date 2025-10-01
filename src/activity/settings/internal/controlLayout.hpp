#define __FIX_CTRLOBJ__(objrect, cobjtype) \
  else if(objrect.contains(sf::TouchEvent::getPosition())) \
     { __ctrlObj = CtrlObj::cobjtype; __modified = true; }

#define  __SAV_VECTOR2__(Key, Vec2) \
  __SET_JVALUE_VECTOR2__(sys::__jcontext["Control"]["Layout"][Key], Float, Vec2);

#define __MOV_CTRLOBJ__(objrect, cobjtype, obj) \
  case(CtrlObj::cobjtype): { obj.move({ \
         ((objrect.left < 0 && sf::TouchEvent::getTouchMove().x < 0) \
      || ((objrect.left + objrect.width  > sf::Fm::getRoot(sf::Renderable::getViewRect()).x) \
      && sf::TouchEvent::getTouchMove().x > 0)) ? 0 : sf::TouchEvent::getTouchMove().x, \
         ((objrect.top  < 0 && sf::TouchEvent::getTouchMove().y < 0) \
      || ((objrect.top  + objrect.height > sf::Fm::getRoot(sf::Renderable::getViewRect()).y) \
      && sf::TouchEvent::getTouchMove().y > 0)) ? 0 : sf::TouchEvent::getTouchMove().y  \
  }); __outlineBox.setFrame(objrect); } break;

#define __UNIT_COIN_RECT__ sf::FloatRect{ \
  spv.co.__pic.getPosition().x, spv.co.__pic.getPosition().y,  \
  spv.co.__pic.getSize().x    + spv.co.__num.getSize().x + 40, \
  spv.co.__pic.getSize().y}

// Blood & Food
#define __UNIT_BLFD_RECT__ sf::FloatRect{ \
  spv.bl.__prog.getPosition().x, spv.bl.__prog.getPosition().y, spv.bl.__prog.getSize().x, \
  spv.bl.__prog.getSize().y + spv.fd.__pic.getBuildPosition().y + spv.fd.__pic.getSize().y}

//TODO View_Skill(_actived)

typedef enum class ControlObject : int {
  Control_Move,
  Control_Attack,
  Control_Observe,
  View_Settings,
  View_Pause,
  View_Blood,
  View_Equip,
  View_Coin,
  
  Unknown = -1,
}CtrlObj;

func controlLayout(void) -> sys_acti::ActivityType {
  CtrlObj __ctrlObj{CtrlObj::Unknown};
  
  PlayView_M spv;
  spv.Blood_init();
  
  ui_m->__viewpos.setPosition(sf::Renderable::getViewPosition());

  sf::PushBtn __reset({100, 60}, ui_m->__back, 5, {40, 25}, {true, false}); {
    __reset.setText(L"重置", res::__font, 30);
    __reset.setTextAlign(sf::Align::C);
    __reset.setTextColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __reset.getBase().setOutlineColor(__reset.getTextColor());
    __reset.setStateColor(sf::Color::Transparent, sf::BtnState::None);
  }
  
  sf::Div __outlineBox; {
    __outlineBox.getBase().setOutlineColor(sf::ColorEx::makeTrs(sf::Color::Blue));
    __outlineBox.getBase().setFillColor(sf::Color::Transparent);
    __outlineBox.getBase().setOutlineThickness(2);
  }
  
  // 控件初始化
  Control_M::init();
  spv.__settings.getBase().setTexture(res::ui::__settings.get());
  spv.__settings.getBase().setOutlineThickness(0);
  spv.__settings.align(sf::Align::TR)
  -= rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["View_Settings"]);
  
  bool __modified{false};
  while(sf::Renderable::loopBegin(sys::__darkMode
  ? __DARK_COLOR_COL__ : sf::Color::White)) {
    
    sf::TouchEvent::pollEvent(sys::__event);
    while(_Renderer.pollEvent(sys::__event)) {
      if(__ACTIV_EXIT__      (sys::__event))
        return sys_acti::ActivityType::Settings;
      if(ui_m->__back.pollEvent_if(sys::__event)) {
        if(__modified) {
          ui_m->__msg.launchQueue({
            .title = L"提示",
            .info  = L"操作布局有改动, 确定保存?",
            .btn = { {L"确定",  1},
                     {L"取消", -1}, },
            .btnTextSize = 60,
          }, true);
        } else return sys_acti::ActivityType::Settings;
        
      } else if(!ui_m->__back.isTouchDown()) {
        if(auto r = ui_m->__msg.pollEvent(sys::__event)) {
          switch(sf::Vector2f __offs{}; r.value()) {
            case(2): /* 重置 */ {
              __modified = true;
              Control_M::__move.setCenter(__INITPOS_MOVE__);
              Control_M::__attk.setCenter(_Renderer.getView().getSize() - __INITPOS_ATTACK__);
              Control_M::__obsr.setCenter(sf::align(sf::Vector2f{Control_M::__obsr.getEdgeRadius(),
                Control_M::__obsr.getEdgeRadius()} * 2, sf::Renderable::getViewRect(), sf::Align::TR) - __INITPOS_OBSERVE__);
              spv.__settings.align(sf::Align::TR) -= __INITPOS_SETTINGS__;
              spv.__pause.setBuildPosition(__INITPOS_PAUSE__);
              spv.bl.__prog.setBuildPosition(__INITPOS_BLOOD__);
              spv.eq.__box. setBuildPosition(__INITPOS_EQUIP__);
              spv.co.__pic.align(sf::Align::L) += __INITPOS_COIN__;
            } break;
            case(1): /* 保存 */ {
              __SAV_VECTOR2__("Control_Move", Control_M::__move.getCenter())
              __SAV_VECTOR2__("Control_Attack", (_Renderer.getView().getSize() - Control_M::__move.getCenter()))
              __SAV_VECTOR2__("Control_Observe",  (sf::align(sf::Fm::getSize(Control_M::__obsr.getEdge().getRect()),
                   sf::Renderable::getViewRect(), sf::Align::TR) - Control_M::__obsr.getCenter()));
              __SAV_VECTOR2__("View_Settings", (sf::align(sf::Fm::getSize(spv.__settings.getBase(false).getGlobalBounds()),
                                   _RendererRect, sf::Align::TR) - spv.__settings.getPosition()));
              __SAV_VECTOR2__("View_Pause", spv.__pause.getPosition());
              __SAV_VECTOR2__("View_Blood", spv.bl.__prog.getPosition());
              __SAV_VECTOR2__("View_Equip", spv.eq.__box. getPosition());
              __SAV_VECTOR2__("View_Coin", (spv.co.__pic.getPosition() - sf::align(spv.co.__pic.getSize(),
                                    sf::Renderable::getViewRect(), sf::Align::L)));
            } [[fallthrough]];
            case(-1): return sys_acti::ActivityType::Settings;
          }
        }
        
        if(__reset.pollEvent_if(sys::__event)) {
          ui_m->__msg.launchQueue({
            .title = L"提示",
            .info  = L"确定重置布局?",
            .btn = { {L"确定", 2},
                     {L"取消", 0}, },
            .btnTextSize = 60,
          }, true);
        }
        
        if(sys::__event.type == sf::Event::TouchBegan && !sf::Msgable::getLocked()) {
          if(false); /* 初始化边缘 */
          __FIX_CTRLOBJ__(Control_M::__move.getEdge().getRect(), Control_Move)
          __FIX_CTRLOBJ__(Control_M::__attk.getEdge().getRect(), Control_Attack)
          __FIX_CTRLOBJ__(Control_M::__obsr.getEdge().getRect(), Control_Observe)
          __FIX_CTRLOBJ__(spv.__settings.getRect(), View_Settings)
          __FIX_CTRLOBJ__(spv.__pause.getRect(), View_Pause)
          __FIX_CTRLOBJ__(__UNIT_BLFD_RECT__, View_Blood)
          __FIX_CTRLOBJ__(spv.eq.__box.  getRect(), View_Equip)
          __FIX_CTRLOBJ__(__UNIT_COIN_RECT__, View_Coin)
          else __ctrlObj = CtrlObj::Unknown;
          
        } else if(__ctrlObj != CtrlObj::Unknown && sf::Touch::isDown(0)) {
          switch( __ctrlObj) /* 移动检测 */ {
            __MOV_CTRLOBJ__(Control_M::__move.getEdge().getRect(), Control_Move, Control_M::__move.getEdge())
            __MOV_CTRLOBJ__(Control_M::__attk.getEdge().getRect(), Control_Attack, Control_M::__attk.getEdge())
            __MOV_CTRLOBJ__(Control_M::__obsr.getEdge().getRect(), Control_Observe, Control_M::__obsr.getEdge())
            __MOV_CTRLOBJ__(spv.__settings.getBase(false).getGlobalBounds(), View_Settings, spv.__settings)
            __MOV_CTRLOBJ__(spv.__pause.getBase(false).getGlobalBounds(), View_Pause, spv.__pause)
            __MOV_CTRLOBJ__(__UNIT_BLFD_RECT__, View_Blood, spv.bl.__prog)
            __MOV_CTRLOBJ__(spv.eq.__box. getRect(), View_Equip, spv.eq.__box)
            __MOV_CTRLOBJ__(__UNIT_COIN_RECT__, View_Coin, spv.co.__pic)
            default: break;
          }
        } else {
          __outlineBox.setFrame({{-10, 0}, {}});
          __ctrlObj = CtrlObj::Unknown;
        }
      }
    }
    
    Control_M::draw();
    sf::Renderable::draw(spv.__settings,
                         spv.__pause,
                         spv.bl.__prog,
                         spv.fd.__prog,
                         spv.fd.__pic,
                         spv.eq.__box,
                         spv.co.__pic,
                         spv.co.__num);
    
    sf::Renderable::draw(ui_m->__back, __reset, __outlineBox);
    
                sys::flashDisplay();
  } return sys_acti::ActivityType::Exit;
}

#undef __FIX_CTRLOBJ__
#undef __SAV_VECTOR2__
#undef __MOV_CTRLOBJ__
#undef __UNIT_COIN_RECT__
#undef __UNIT_BLFD_RECT__
