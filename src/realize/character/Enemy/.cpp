inline func Char_M::Enemy::moveToDuck(void) -> void {
  // Boss动画 进行刻
  if(sf::Msgable::getLocked()) {
    if(this->__exmove != sf::Vector2f{}
    && static_cast<int>(ChickBoss::__proceed) >= 3) {
      this->__s.move(sys::movtionSync(this->__exmove));
      this->__s.rotate(5.0f / sys::tickSync());
      // 受击效果恢复
      if(this->__s.getColor().g < 255
      || this->__s.getColor().b < 255) {
         this->__s.setColor(sf::Color{255, static_cast<sf::Uint8>(this->__s.getColor().g + 3), static_cast<sf::Uint8>(this->__s.getColor().b + 3)});
      }
    } return;
  }
  
  // 正常
  if(this->__exmove == sf::Vector2f{}) {
    // 结束
    if(Char_M::Duck::__v->noBlood()) {
      this->__exmove = sf::geometry::parse_circle_point({._radius = 100, ._center = sf::Fm::getCenter(Char_M::Duck::__v->__realRect),
        ._allow_in = false}, sf::Fm::getCenter(this->__realRect)).v_LengthToCenter_Coordinates * 0.08f;
      this->__cast_exp = 0; return;
    }
    
    // 移动
    if(this->__hinderWith != nullptr) {
      if(this == this->__hinderWith->__hinderWith) {
        this->__ghost.restart();
        this->__hinderWith = nullptr;
      } else if(std::fabs(this->__move.x) < 1.6
             && std::fabs(this->__move.y) < 1.6) {
        this->__hinderWith = nullptr;
      } else {
        if(std::fabs(this->__move.x) > 1.6) {
          if(this->__move.x > 0)
            this->__move.x -= 0.5 / sys::tickSync();
          else
            this->__move.x += 0.5 / sys::tickSync();
        }
        if(std::fabs(this->__move.y) > 1.6) {
          if(this->__move.y > 0)
            this->__move.y -= 0.5 / sys::tickSync();
          else
            this->__move.y += 0.5 / sys::tickSync();
        }
      }
    } else {
      sf::Vector2f tmp_v{sf::Fm::getCenter(Char_M::Duck::__v->__realRect)},
                   tmp_c{sf::Fm::getCenter(             this->__realRect)};
      float tmpv_atan
        {std::atan((tmp_c.y - tmp_v.y)
                 / (tmp_c.x - tmp_v.x))};
      this->__move = sf::Vector2f(std::cos(tmpv_atan),
                                  std::sin(tmpv_atan))
                   * ((tmp_c.x < tmp_v.x) ? this->__speed_f : -this->__speed_f)
                   * (1.0f + std::min(static_cast<int>(Char_M::Value::__level), 20) * 0.04f);
    }
    
    // 重置
    if(this->__out_of_screen_clock.getElapsedTime().asSeconds() >= 8) {
       this->initPos(); this->__out_of_screen_clock.restart();
    }
    
    // 阻碍
    if(this->__hinderWith == nullptr
    && this->__inview
    && this->__ghost.getElapsedTime().asSeconds() > 1.5) {
      // 重点 //>>>TODO
      sf::Vector2f __powerPoint{};
      if(std::fabs(this->__move.x) < 1.2) {
        if(this->__move.y > 0)
          __powerPoint = sf::align({}, this->__realRect, sf::Align::B);
        else
          __powerPoint = sf::align({}, this->__realRect, sf::Align::T);
      } else if(this->__img_code < 3) {
        if(std::fabs(this->__move.x)
         - std::fabs(this->__move.y) > 0)
          __powerPoint = sf::align({}, this->__realRect, sf::Align::L);
        else if(this->__move.y > 0)
          __powerPoint = sf::align({}, this->__realRect, sf::Align::LB);
        else
          __powerPoint = sf::align({}, this->__realRect, sf::Align::LT);
      } else {
        if(std::fabs(this->__move.x)
         - std::fabs(this->__move.y) > 0)
          __powerPoint = sf::align({}, this->__realRect, sf::Align::R);
        else if(this->__move.y > 0)
          __powerPoint = sf::align({}, this->__realRect, sf::Align::RB);
        else
          __powerPoint = sf::align({}, this->__realRect, sf::Align::RT);
      }
      for(auto& i : Alloter::__active) {
        if(i.operator bool() && i.get() != this && i->__movable && i->__realRect.contains(__powerPoint)) {
          (this->__hinderWith = i.get())->__s.move(sys::movtionSync(i->__move * 0.4f) * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f));
          break;
        }
      }
    }
  } else {
    this->__s.rotate((5.0f / sys::tickSync()) * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f));
  } this->__s.move(sys::movtionSync((this->__exmove != sf::Vector2f{}) ? this->__exmove
    : Map_M::mathsObsPath(Map_M::mathsObsSide(this->__realRect), this->__move)) * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f));
  
  this->adaptRect();
  
  // 受击效果恢复
  if(this->__s.getColor().g < 255
  || this->__s.getColor().b < 255) {
     this->__s.setColor(sf::Color{255, static_cast<sf::Uint8>(this->__s.getColor().g + 3), static_cast<sf::Uint8>(this->__s.getColor().b + 3)});
  }
}

inline func Char_M::Enemy::setTexture(void) -> void {
  if(!this->__inview || sf::Msgable::getLocked()) return;
  
  size_t tmp_code{this->__img_code};
  if(this->__move.x < 0) {
    if(this->__img_code == 0
    || this->__img_code == 3) {
       this->__img_code = 1;
    } else if(this->__img_code > 3) {
      this->__img_code -= 3;
    } else if(this->__img_c.getElapsedTime().asSeconds() >= 0.8) {
      if(this->__img_code == 1) {
         this->__img_code = 2;
      } else {
         this->__img_code = 1;
      }  this->__img_c.restart();
    }
  } else if(this->__move.x > 0) {
    if(this->__img_code == 0
    || this->__img_code == 3) {
       this->__img_code = 4;
    } else if(this->__img_code < 3) {
      this->__img_code += 3;
    } else if(this->__img_c.getElapsedTime().asSeconds() >= 0.8) {
      if(this->__img_code == 4) {
         this->__img_code = 5;
      } else {
         this->__img_code = 4;
      }  this->__img_c.restart();
    }
  } else {
    if(this->__img_code < 3) {
       this->__img_code = 0;
    } else {
       this->__img_code = 3;
    }
  }
  if(tmp_code        !=  this->__img_code
  || this->__attking != (this->__attkc.getElapsedTime().asSeconds() < 0.4)) {
     this->__attking  =  this->__attkc.getElapsedTime().asSeconds() < 0.4;
     switch(this->__enemy_code) {
       case(__ECODE_CHICK__):     this->__s.setTexture(*res::enemy::__t_chick    [this->__attking][this->__img_code]); break;
       case(__ECODE_BOMBCHICK__): this->__s.setTexture(*res::enemy::__t_bombChick[this->__attking][this->__img_code]); break;
       case(__ECODE_SHELLPIG__):  this->__s.setTexture(*res::enemy::__t_shellPig [this->__attking][this->__img_code]); break;
       default: break;
     }
  }
}

inline func Char_M::Enemy::adaptRect(void) -> void {
  this->__realRect = this->__s.getGlobalBounds();
}

inline func Char_M::Enemy::checkDrop(void) -> void {
  if(!this->__nodrop) {
    Char_M::Value::effect.__exp += this->__cast_exp;
  }                                this->__cast_exp = 0;
}

inline func Char_M::Enemy::pushList(void) -> void {
  if(this->__inview || (static_cast<int>(ChickBoss::__proceed) > 0
                     && static_cast<int>(ChickBoss::__proceed) < 10)) {
     this->__out_of_screen_clock.restart();
    Char_M::__drawList.emplace_back(
      std::make_pair<const sf::Vector2f&, sf::Drawable*>(
        sf::align({}, this->__s.getGlobalBounds(), sf::Align::B), &this->__s));
  }
  
  // Debug
  this->__trackBox.setRect(this->__realRect);
  this->__trackLine[0].position = sf::Fm::getCenter(Char_M::Duck::__v->__realRect);
  this->__trackLine[1].position = sf::Fm::getCenter(this->__realRect);
  if(sys::__dataMode) {
     sys::__debugList.emplace_back(&this->__trackLine);
     sys::__debugList.emplace_back(&this->__trackBox);
  }
}

inline func Char_M::Enemy::del(void) -> void {
  Char_M::Enemy::__signal_call_del = !this->__inview;
}

inline func Char_M::Enemy::initData(const std::string& str) -> void {
  const auto& target{__enemyData.find(str)->second};
  this->__enemy_code = std::get<0>(target);
  this->__cast_blood = (this->__cnst_blood = std::get<1>(target));
  this->__cast_exp   = (this->__cnst_exp   = std::get<2>(target));
  this->__attack  = std::get<3>(target);
  this->__speed_f = std::get<4>(target);
}

inline func Char_M::Enemy::initPos(void) -> void {
  sf::Vector2i __mov_dir{Control_M::__move_move * 2.5f}, __pos{};
  
  repos: __pos = {
    sys::rand<int>({-1450, static_cast<int>(_RendererSize.x) + 1600}) + __mov_dir.x,
    sys::rand<int>({ -850, static_cast<int>(_RendererSize.y) + 1000}) + __mov_dir.y
  };

  while(__pos.x > -50 && __pos.x < _RendererSize.x
     && __pos.y > -50 && __pos.y < _RendererSize.y) {
        __pos += __mov_dir;
    if(__mov_dir == sf::Vector2i{}) goto repos;
  }
  
  this->__s.setPosition(ui_m->__viewpos.getPosition() + __pos);
}

inline func Char_M::Enemy::hurt(int _bl, sf::Vector2f _toward, bool by_explode, bool count_acc) -> void {
  // 伤害数值
  if(_bl > 0) {
    if(by_explode)
      AttackDisplay_M::call(std::to_wstring(_bl), sf::Fm::getPosition(this->__realRect)); // for visible
    else {
      Char_M::Value::__total_attkV += _bl;
    ++Char_M::Value::__total_hit;
      if(Char_M::Weapon::__attk_bullet != nullptr)
           AttackDisplay_M::call(std::to_wstring(_bl), Char_M::Weapon::__attk_bullet->first[1].position);
      else AttackDisplay_M::call(std::to_wstring(_bl), sf::Fm::getCenter(this->__realRect));
      
      if(Char_M::Weapon::__signal_crit)
        AttackDisplay_M::call(L"暴击");
    }
  }
  
  // 引爆
  if(this->__enemy_code == __ECODE_BOMBCHICK__ && Char_M::Weapon::__attk_bullet != nullptr && Char_M::Skill::taken("fireBullets") && !by_explode) {
     this->__bombState = BombState::Exploded;
    Char_M::Explode::make(sf::Fm::getCenter(this->__realRect), 100, true, this);
  }
  
  if(_bl < 0 && !count_acc) {
    this->__nodrop = true;
    if(_toward == sf::Vector2f{})
      this->__exmove = sf::Fm::getCenter(this->__realRect)
                     - sf::Fm::getCenter(Char_M::Duck::__v->__realRect);
    else
      this->__exmove = _toward;
  }
  else if(_bl < 0 || (this->__cast_blood -= _bl) <= 0) {
  
    if(Char_M::Value::__vampirism_f != 1.0f && sys::rand<int>({1, 100}) <= 20)
       Char_M::Value::effect.__blood += std::ceil(this->__cnst_blood * (Char_M::Value::__vampirism_f - 1.0f));
       
    Char_M::Value::effect.__food += 35;
    
    if(_toward == sf::Vector2f{})
      this->__exmove = sf::Fm::getCenter(this->__realRect)
                     - sf::Fm::getCenter(Char_M::Duck::__v->__realRect);
    else
      this->__exmove = _toward;
      
    if(!Char_M::Duck::__v->noBlood() && count_acc) switch(this->__enemy_code) {
      case(__ECODE_SHELLPIG__):  __ACC_UPDATE__(++Acc_M::__enemy_data.find("kill_shellPig") ->second); break;
      case(__ECODE_BOMBCHICK__): __ACC_UPDATE__(++Acc_M::__enemy_data.find("kill_bombChick")->second); break;
      case(__ECODE_CHICK__):     __ACC_UPDATE__(++Acc_M::__enemy_data.find("kill_chick")    ->second); break;
      default: break;
    } __AUDIO__CHECK_SOUND__(kill);
  }
  
  // 受击效果
  this->__s.setColor(sf::Color{255, 75, 75});
}

#include "Chick.cpp"
#include "ChickEgg.cpp"
#include "BombChick.cpp"
#include "ShellPig.cpp"

#include "./internal/CreatePool.cpp"
#include "./internal/Allocator.cpp"
#include "./internal/Alloter.cpp"

#include "./boss/ChickBoss_Manager.cpp"

