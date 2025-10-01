#define __OK_RENDERER__ (sf::Renderable::getRenderer() == nullptr \
                         || _Renderer.isOpen())

inline func Arc_M::clear(void) -> void {
  std::queue<std::pair<sf::String, size_t>> __empty_queue{};

  Json_M::ofs.open(__PATH_ARCHIVE_JSON__, std::ios::trunc);
  Json_M::ofs.close();
  Char_M::Skill::reset();
  Char_M::data.resetKilledNum();
  Char_M::Enemy::Alloter::reset();
  Char_M::Enemy::CreatePool::clear();
  PlayView_M::__msgBoxStr.swap(__empty_queue);
  Storage_M::__buf.clear();
  Storage_M::saveJ(false);
  
  Char_M::Weapon::__v = std::move(std::make_unique<Char_M::Weapon::Scissors>());
  Char_M::Duck::__v->__s.setPosition({});
}

inline func Arc_M::loadJ_t(void) -> bool {
  return(Json_M::parseJ(Arc_M::dom, __PATH_ARCHIVE_JSON__)
  && __CHECK_JVALUE__(Arc_M::dom, "Enable", Bool)
  &&                  Arc_M::dom ["Enable"].GetBool()
  && __CHECK_JVALUE__(Arc_M::dom, "_Version", Uint)
  &&                  Arc_M::dom ["_Version"].GetUint() == sys::__apkVer
  && __CHECK_JVALUE__(Arc_M::dom, "Time", Uint)
  &&  (std::time(0) - Arc_M::dom["Time"].GetUint() <= 60));
}

inline func Arc_M::loadJ(void) -> bool {
  if(Json_M::parseJ(Arc_M::dom, __PATH_ARCHIVE_JSON__)) {
    if((__CHECK_JVALUE__(Arc_M::dom, "Enable", Bool)
                      && Arc_M::dom ["Enable"].GetBool())
    && (__CHECK_JVALUE__(Arc_M::dom, "_Version", Uint)
                      && Arc_M::dom ["_Version"].GetUint() == sys::__apkVer)) {
    } else goto error;
    
    if(__CHECK_JVALUE__(Arc_M::dom, "Data", Object)) {
      const rj::Value& data = Arc_M::dom["Data"];
      
      // Data: Enemy
      if(__CHECK_JVALUE__(data, "Enemy", Object)) {
        const rj::Value& ene = data["Enemy"];
        
        if(__CHECK_JVALUE__(ene, "Total", Uint)
        && __CHECK_JVALUE__(ene, "Info", Array)) {
          const size_t __enemy_num_to_load{ene["Total"].GetUint()};

Arc_M::__process = 0;
Arc_M::__all_process = __enemy_num_to_load + 6;

          if(__CHECK_JVALUE__(ene, "ChickBossData", Object)) {
            const rj::Value& cbd = ene["ChickBossData"];
            int __stateCode{0};
            
            __GET_JVALUE__(cbd, "Proceed", Int, __stateCode);
            
                 if(__stateCode == 0) goto noBoss;
            else if(__stateCode < 10) goto noBoss;
            else if(__stateCode < 20) {
              ChickBoss::__this = std::make_unique<Char_M::Enemy::Chick>();
              ChickBoss::__boss_living = true;
              ChickBoss::startInit();

                     if(__CHECK_JVALUE__(cbd, "RushTowards", Array)) {
                     ChickBoss::__rushTowards = rj::arrayToVector2(cbd["RushTowards"]);
                     ChickBoss::__proceed = ChickBossState::Ready_to_rush;
                     ChickBoss::__rushClock.restart();
                     
              } else if(__CHECK_JVALUE__(cbd, "FlashCenter", Array)) {
                     ChickBoss::__flashHint->setCenter(rj::arrayToVector2(cbd["FlashCenter"]));
                     ChickBoss::__proceed = ChickBossState::Ready_to_flash;
                     
              } else ChickBoss::__proceed = ChickBossState::Live;
            }
            else if(__stateCode < 30) {
              ChickBoss::__boss_died = true;
              goto noBoss;
            }
            else goto noBoss;
            
            __IF_JVALUE_OK__(cbd, "Position", Array, {ChickBoss::__this->__s.setPosition(rj::arrayToVector2(cbd["Position"]));});
            __GET_JVALUE__(cbd, "Blood", Int, ChickBoss::__this->__cast_blood);
            ChickBoss::__blood_prog->setProgress(static_cast<float>(ChickBoss::__this->__cast_blood % 50) / 50.0f);
            ChickBoss::__blood_prog->setTag<int>(static_cast<size_t>(ChickBoss::__this->__cast_blood / 50) + 1);
            ChickBoss::__blood_prog->setTextString(L"×" + std::to_wstring(ChickBoss::__blood_prog->getTag<int>()));
            ChickBoss::__blood_prog->getInside().setFillColor(ChickBoss::__BLOOD_LAYERS_COLOR__[ChickBoss::__blood_prog->getTag<int>() - 1]);
            if(ChickBoss::__blood_prog->getTag<int>() >= 2)
               ChickBoss::__blood_prog->setFillColor(ChickBoss::__BLOOD_LAYERS_COLOR__[ChickBoss::__blood_prog->getTag<int>() - 2]);
            else
               ChickBoss::__blood_prog->setFillColor(sf::ColorEx::LightPink | 70);
          }
noBoss:   ++Arc_M::__process;
          
          if(__CHECK_JVALUE__(ene, "Killed", Object)) {
            const rj::Value& kil = ene["Killed"];
            if(!ChickBoss::__boss_died)
              __GET_JVALUE__(kil, "ChickBoss", Bool, ChickBoss::__boss_died); ++Arc_M::__process;
            __GET_JVALUE__(kil, "Ordi", Int64, Char_M::data.killedNum.__ordi); ++Arc_M::__process;
            __GET_JVALUE__(kil, "Spec", Int64, Char_M::data.killedNum.__spec); ++Arc_M::__process;
            __GET_JVALUE__(kil, "Boss", Int64, Char_M::data.killedNum.__boss); ++Arc_M::__process;
          }
          
          for(size_t i{0}; i < __enemy_num_to_load; ++i, ++Arc_M::__process) {
            const rj::Value& eif = ene["Info"][i];
            
            if(__CHECK_JVALUE__(eif, "Type", Int64)) {
              switch(eif["Type"].GetInt64()) {
                case(__ECODE_SHELLPIG__): {
                  if(  Char_M::Enemy::CreatePool::valid(__ECODE_SHELLPIG__))
                       Char_M::Enemy::Alloter::__active.emplace_back(Char_M::Enemy::CreatePool::move());
                  else Char_M::Enemy::Alloter::__active.emplace_back(std::move(std::make_unique<Char_M::Enemy::ShellPig>()));
                } break;
                case(__ECODE_BOMBCHICK__): {
                  if(  Char_M::Enemy::CreatePool::valid(__ECODE_BOMBCHICK__))
                       Char_M::Enemy::Alloter::__active.emplace_back(Char_M::Enemy::CreatePool::move());
                  else Char_M::Enemy::Alloter::__active.emplace_back(std::move(std::make_unique<Char_M::Enemy::BombChick>()));
                  __IF_JVALUE_OK__(eif, "BombState", Int, {Char_M::Enemy::Alloter::__active.back()->__bombState = static_cast<BombState>(eif["BombState"].GetInt());});
                  __GET_JVALUE__  (eif, "BombTick", Int,   Char_M::Enemy::Alloter::__active.back()->__kindlingTick);
                } break;
                case(__ECODE_CHICK__): default: {
                  if(  Char_M::Enemy::CreatePool::valid(__ECODE_CHICK__))
                       Char_M::Enemy::Alloter::__active.emplace_back(Char_M::Enemy::CreatePool::move());
                  else Char_M::Enemy::Alloter::__active.emplace_back(std::move(std::make_unique<Char_M::Enemy::Chick>()));
                } break;
              }
            } else goto error;
            
            __IF_JVALUE_OK__(eif, "Position", Array, {
              Char_M::Enemy::Alloter::__active.back()->__s.setPosition(rj::arrayToVector2(eif["Position"]));
            });
            __IF_JVALUE_OK__(eif, "Exmove",       Array, {Char_M::Enemy::Alloter::__active.back()->__exmove = rj::arrayToVector2(eif["Exmove"]);
                                                          Char_M::Enemy::Alloter::__active.back()->__cast_exp = 0; });
            __GET_JVALUE__(eif, "Blood",        Int,    Char_M::Enemy::Alloter::__active.back()->__cast_blood);
            __GET_JVALUE__(eif, "Speed_Factor", Float,  Char_M::Enemy::Alloter::__active.back()->__speed_f);
          }
          
        } else goto error;
      } else goto error;
      if(__CHECK_JVALUE__(data, "PlayTime", Uint)) {
        Arc_M::__playTime = sf::seconds(data["PlayTime"].GetUint()); ++Arc_M::__process;
      }
      
      // Data: Duck
      if(__CHECK_JVALUE__(data, "Duck", Object)) {
        const rj::Value& duck = data["Duck"];
        
        if(!__CHECK_JVALUE__(duck, "Skill", Array)) goto error;
        
Arc_M::__process = 0;
Arc_M::__all_process = duck["Skill"].GetArray().Size() + 12;
        
        if(__CHECK_JVALUE__(duck, "Movtion", Object)) {
          __IF_JVALUE_OK__(duck["Movtion"], "Position", Array, {Char_M::Duck::__v->__s.setPosition(rj::arrayToVector2(duck["Movtion"]["Position"]));}); ++Arc_M::__process;
          __IF_JVALUE_OK__(duck["Movtion"], "Repel",    Array, {Char_M::Duck::__v->__repel = rj::arrayToVector2(duck["Movtion"]["Repel"]);}); ++Arc_M::__process;
        } else goto error;
        
        if(__CHECK_JVALUE__(duck, "Attribute", Object)) {
          __GET_JVALUE__(duck["Attribute"], "Blood", Uint, Char_M::Value::__blood); ++Arc_M::__process;
          __GET_JVALUE__(duck["Attribute"], "Food", Float, Char_M::Value::__food); ++Arc_M::__process;
          __GET_JVALUE__(duck["Attribute"], "Level", Uint, Char_M::Value::__level); ++Arc_M::__process;
          __GET_JVALUE__(duck["Attribute"], "Exp",   Uint, Char_M::Value::__exp); ++Arc_M::__process;
        } else goto error;
        
        if(__CHECK_JVALUE__(duck, "Record", Object)) {
          __GET_JVALUE__(duck["Record"], "AttkV", Uint, Char_M::Value::__total_attkV); ++Arc_M::__process;
          __GET_JVALUE__(duck["Record"], "CureV", Uint, Char_M::Value::__total_cureV); ++Arc_M::__process;
          __GET_JVALUE__(duck["Record"], "Move", Float, Char_M::Value::__total_move); ++Arc_M::__process;
          __GET_JVALUE__(duck["Record"], "Attk", Uint, Char_M::Value::__total_attk); ++Arc_M::__process;
          __GET_JVALUE__(duck["Record"], "Hit",  Uint, Char_M::Value::__total_hit); ++Arc_M::__process;
        }
        
        for(const auto& i : duck["Skill"].GetArray()) {
          if(i.IsString()) { Char_M::Skill::require(i.GetString()); } ++Arc_M::__process;
        }
        if(__CHECK_JVALUE__(duck, "Skill_reload", Array)) {
           Char_M::Value::__update_level = true;
           for(const auto& i : duck["Skill_reload"].GetArray())
             if(i.IsString()) Char_M::Skill::__reload_list.emplace_back(i.GetString());
        };
        
        if(Char_M::Weapon::__v.operator bool()) {
          if(__CHECK_JVALUE__(duck,  "Weapon", Object)) {
            if(__CHECK_JVALUE__(duck["Weapon"], "Type", Int64)) {
              if(Char_M::Weapon::__weapon_code < 0)
                 Char_M::Weapon::__weapon_code = duck["Weapon"]["Type"].GetInt64();
              switch(Char_M::Weapon::__weapon_code) {
                case(__WCODE_PISTOL__): {
                  Char_M::Weapon::__v = std::move(std::make_unique<Char_M::Weapon::Pistol>());
                } break;
                case(__WCODE_SCISSORS__): default: {
                  Char_M::Weapon::__v = std::move(std::make_unique<Char_M::Weapon::Scissors>());
                } break;
              } ++Arc_M::__process;
            } else goto error;
          } else goto error;
        } else goto error;
      } else goto error;
    } else goto error;
  } else goto error;
  Arc_M::__all_process = 0;
  Arc_M::__load_ok = true;
  return true;
  
error: // NoArc or BrokenArc
  Arc_M::__all_process = 0;
  Arc_M::__load_ok = true;
  Arc_M::clear();
  return false;
}

//>>> Warning: use std::thread to control it!
inline func Arc_M::saveJ(void) -> void {
  while(sys_acti::__actype != sys_acti::ActivityType::Exit && __OK_RENDERER__) {
    while(Arc_M::__joinable) {
      if(Storage_M::__buf.__signal_update) Storage_M::saveJ(false);

      if(Acc_M::__signal_update) Acc_M::saveJ();
      
      if(Arc_M::saveJ_overrideMode()) break;
      
      if(Arc_M::__joinable && (sf::Renderable::getRenderer() != nullptr
                               || _Renderer.isOpen()))
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    if(Arc_M::__trRun_l) {
       Arc_M::__trRun_l = false;
       Arc_M::loadJ();
    }
  }
}

inline func Arc_M::saveJ_overrideMode(void) -> bool {
  if(sf::Msgable::getLocked()) Arc_M::__playTimeClock.restart();
  
  __NEW_OBJECT__({
    Json_M::writer.Key("Enable"); Json_M::writer.Bool(true);
    Json_M::writer.Key("Time"); Json_M::writer.Uint(std::time(0));
    
    Json_M::writer.Key("Data"); __NEW_OBJECT__({
      Json_M::writer.Key("PlayTime"); Json_M::writer.Uint((!Char_M::Duck::__v->noBlood()
        ? Arc_M::__playTime += Arc_M::__playTimeClock.restart()
        : sf::Time::Zero).asSeconds());
      
      Json_M::writer.Key("Duck"); __NEW_OBJECT__({
        Json_M::writer.Key("Movtion"); __NEW_OBJECT__({
          Json_M::writer.Key("Position"); __NEW_ARRAY_V2f__(Char_M::Duck::__v->__s.getPosition());
          Json_M::writer.Key("Repel");    __NEW_ARRAY_V2f__(Char_M::Duck::__v->__repel);
        });
        
        Json_M::writer.Key("Attribute"); __NEW_OBJECT__({
          Json_M::writer.Key("Blood"); Json_M::writer.Uint(Char_M::Value::__blood);
          Json_M::writer.Key("Food");  Json_M::writer.Double(Char_M::Value::__food);
          Json_M::writer.Key("Level"); Json_M::writer.Uint(Char_M::Value::__level);
          Json_M::writer.Key("Exp");   Json_M::writer.Uint(Char_M::Value::__exp);
        });
        Json_M::writer.Key("Record"); __NEW_OBJECT__({
          Json_M::writer.Key("AttkV"); Json_M::writer.Uint(Char_M::Value::__total_attkV);
          Json_M::writer.Key("CureV"); Json_M::writer.Uint(Char_M::Value::__total_cureV);
          Json_M::writer.Key("Move"); Json_M::writer.Double(Char_M::Value::__total_move);
          Json_M::writer.Key("Attk"); Json_M::writer.Uint(Char_M::Value::__total_attk);
          Json_M::writer.Key("Hit"); Json_M::writer.Uint(Char_M::Value::__total_hit);
        });
        Json_M::writer.Key("Skill"); __NEW_ARRAY__({
          for(const auto& i : Char_M::Skill::__enable_list) Json_M::writer.String(i.c_str());
        });
        if(!Char_M::Skill::__reload_list.empty()) {
          Json_M::writer.Key("Skill_reload"); __NEW_ARRAY__({
            for(const auto& i : Char_M::Skill::__reload_list) Json_M::writer.String(i.c_str());
          });
        }
        Json_M::writer.Key("Weapon"); __NEW_OBJECT__({
          Json_M::writer.Key("Type"); Json_M::writer.Uint(Char_M::Weapon::__v->__weapon_code);
        });
      });
      
      Json_M::__mutex.lock();
      if(!Arc_M::__joinable || !__OK_RENDERER__) { Json_M::__mutex.unlock(); return true; }
      Json_M::writer.Key("Enemy"); __NEW_OBJECT__({
        Json_M::writer.Key("Total"); Json_M::writer.Uint(Char_M::Enemy::Alloter::__active.size());
        
        // Boss
        if(ChickBoss::__this.operator bool()) {
          Json_M::writer.Key("ChickBossData"); __NEW_OBJECT__({
            Json_M::writer.Key("Proceed"); Json_M::writer.Int(static_cast<int>(ChickBoss::__proceed));
            Json_M::writer.Key("Position"); __NEW_ARRAY_V2f__(ChickBoss::__this->__s.getPosition());
            Json_M::writer.Key("Blood"); Json_M::writer.Int(ChickBoss::__this->__cast_blood);
            
            // Rush
            if(ChickBoss::__proceed == ChickBossState::Ready_to_rush
            || ChickBoss::__proceed == ChickBossState::Rushing) {
              Json_M::writer.Key("RushTowards"); __NEW_ARRAY_V2f__(ChickBoss::__rushTowards);
            // Flash
            } else if(ChickBoss::__proceed == ChickBossState::Ready_to_flash
                 || ChickBoss::__proceed == ChickBossState::Flashing) {
              Json_M::writer.Key("FlashCenter"); __NEW_ARRAY_V2f__(ChickBoss::__flashHint->getCenter());
            }
          });
        }
        
        Json_M::writer.Key("Killed"); __NEW_OBJECT__({
          Json_M::writer.Key("ChickBoss"); Json_M::writer.Bool(ChickBoss::__boss_died);
          Json_M::writer.Key("Ordi"); Json_M::writer.Int64(Char_M::data.killedNum.__ordi);
          Json_M::writer.Key("Spec"); Json_M::writer.Int64(Char_M::data.killedNum.__spec);
          Json_M::writer.Key("Boss"); Json_M::writer.Int64(Char_M::data.killedNum.__boss);
        });

        Json_M::writer.Key("Info"); __NEW_ARRAY__({
          for(const auto& i : Char_M::Enemy::Alloter::__active) {
            __NEW_OBJECT__({
              Json_M::writer.Key("Position"); __NEW_ARRAY_V2f__(i->__s.getPosition());
              if(i->__exmove != sf::Vector2f{}) {
                Json_M::writer.Key("Exmove"); __NEW_ARRAY_V2f__(i->__exmove);
              }
              Json_M::writer.Key("Blood");        Json_M::writer.Int(i->__cast_blood);
              Json_M::writer.Key("Speed_Factor"); Json_M::writer.Double(i->__speed_f);
              if(i->__enemy_code == __ECODE_BOMBCHICK__) {
                Json_M::writer.Key("BombState"); Json_M::writer.Int(static_cast<int>(i->__bombState));
                Json_M::writer.Key("BombTick");  Json_M::writer.Int(i->__kindlingTick);
              } Json_M::writer.Key("Type");    Json_M::writer.Int64(i->__enemy_code);
            });
          }
        });
      });
      Json_M::__mutex.unlock();
    });
    
    Json_M::writer.Key("_Version"); Json_M::writer.Uint(sys::__apkVer);
  });
  Json_M::writeJ(__PATH_ARCHIVE_JSON__);
  return false;
}

#undef __OK_RENDERER__
