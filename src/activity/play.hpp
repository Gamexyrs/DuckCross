inline func clear_vdata(void) -> void {
  sf::Timer::all_stop();

  Json_M::__mutex.lock();
  Arc_M::__joinable = false;
  Json_M::__mutex.unlock();
  
  Char_M::__drawList.clear();
  sys::__debugList.clear();
  
  Char_M::Explode::reset();
  
  sf::Sensor::setEnabled(sf::Sensor::Type::Gyroscope, false);
}

func play(void) -> sys_acti::ActivityType {
  sf::Timer::all_start_if_noZero();

  Arc_M::__playTimeClock.restart();
  Char_M::Skill::__signal_reset_clock = true;
  Char_M::Enemy::Alloter::__need_update = true;
  Char_M::Skill::__signal_update_skills_actived = true;

  PlayView_M spv;
  Map_M smap;
  
  Storage_M::reload();
  Control_M::__gyroscope_move = {};
  if((Control_M::__enabled_gyroscope = sys::__jcontext["Control"]["Gyroscope"].GetBool()))
    sf::Sensor::setEnabled(sf::Sensor::Type::Gyroscope, true);
  Arc_M::__joinable = true;
  
  sys::__audio->call_next("bgm_play_" + std::to_string(sys::__audio->__play_music_code));
//>>>
  
  while(sf::Renderable::loopBegin(sys::__darkMode
  ? __DARK_COLOR_COL__ : sf::Color::White)) {
    smap.draw();

    Json_M::__mutex.lock();
    
      Char_M::Skill::call();
      Char_M::Duck::__v->act();
      Control_M::event();
      ui_m->update();
      spv.update();
      
      Char_M::Weapon::__v->act();
      Char_M::Explode::act();
        
      Char_M::Enemy::Allocator::update();
    
    Json_M::__mutex.unlock();
    
    while(sys::fix_pollEvent(sys::__event)) {
      if(__ACTIV_EXIT__     (sys::__event)) {
        clear_vdata(); sys::__audio->__music.stop();
        return sys_acti::ActivityType::Exit;
      }
      if(spv.__settings.pollEvent_if(sys::__event)) {
         clear_vdata(); return sys_acti::ActivityType::Settings;
      }
      if(spv.__pause.pollEvent_if(sys::__event)) {
         spv.__pausing = true;
         sf::Timer::all_stop();
      }
      
      // 作弊
      if(spv.lv.__cheatlv6.pollEvent_if(sys::__event)) {
        Char_M::Enemy::Alloter::__need_update = true;
        Char_M::Value::__update_level = true;
        Char_M::Value::__level = 6;
      }
      if(spv.lv.__cheatboss.pollEvent_if(sys::__event)) {
        Char_M::Enemy::Alloter::__need_update = true;
        Char_M::Value::__update_level = true;
        Char_M::Value::__level = 14;
      }
      if(spv.over.__reborn.pollEvent_if(sys::__event)) {
         spv.over.__text.setTag<bool>(false);
        Char_M::Value::__blood = Char_M::Value::__blood_max;
        Char_M::Value::__update_blood = true;
        Char_M::Value::effect.__blood = 1;
        spv.__signal_reload__ = true;
        Char_M::Value::__food = 100;
      }
      
      // 结算
      if(spv.requestSettle(sys::__event)) {
         clear_vdata(); return sys_acti::ActivityType::Settle;
      }
      spv.requestPause(sys::__event);
      spv.requestEquip(sys::__event);
      spv.requestSkill(sys::__event);
      spv.requestSkill_actived(sys::__event);
      // 消息
      if(auto r = ui_m->__msg.pollEvent(sys::__event)) {
        if(r == -1) {
          clear_vdata();
          sys::__audio->__music.stop();
          return sys_acti::ActivityType::Exit;
        }
        else if(r == 1) { /* 保留 */ }
        else if(r == 101) {
          clear_vdata(); return sys_acti::ActivityType::Settings;
        }
        else if(r == 202) {
          Char_M::Value::autophagy();
          spv.__pausing = false;
        }
      }
    }

    {
      // Object: Char
      Char_M::drawList();

      AttackDisplay_M::draw();

      // Object: Ctrl
      if(!Char_M::Duck::__v->noBlood())
       Control_M::draw();

      // Object: View
      spv.draw();
      ui_m->draw();

      // Object: Debug
      sys::drawDebugList();

    } sys::flashDisplay(false);
  } return sys_acti::ActivityType::Exit;
}
