#define __RESET_ENEMY__                  \
  (*i)->__s.setRotation(0);              \
  (*i)->__s.setColor(sf::Color::White);  \
  (*i)->__exmove = sf::Vector2f{};       \
  (*i)->__nodrop = false;                \
  (*i)->__cast_blood=(*i)->__cnst_blood; \
  (*i)->__cast_exp  =(*i)->__cnst_exp;   \
  (*i)->initPos();   (*i)->adaptRect();

inline func Char_M::Enemy::CreatePool::clear(void) -> void {
  CreatePool::__pool.clear();
  CreatePool::content.    __chick = 0;
  CreatePool::content.__bombChick = 0;
  CreatePool::content.__shellPig = 0;
}

inline func Char_M::Enemy::CreatePool::valid(long v) -> bool {
  if(CreatePool::__pool.empty()) return false;
  if(CreatePool::__buf.get() != nullptr)
     CreatePool::move(CreatePool::__buf);
  
  switch(v) {
    case(__ECODE_SHELLPIG__): {
      if(!CreatePool::content.__shellPig) return false;
      else for(auto i = CreatePool::__pool.begin(); i != CreatePool::__pool.end(); ++i) {
        if((*i)->__enemy_code == __ECODE_SHELLPIG__) {
        --CreatePool::content.__shellPig;
        ++Char_M::data.enemyNum.__shellPig;
        
          __RESET_ENEMY__;
          
          CreatePool::__buf = std::move(*i);
          CreatePool::__pool.erase(i);
          return true;
        }
      }
    } break;
    case(__ECODE_BOMBCHICK__): {
      if(!CreatePool::content.__bombChick) return false;
      else for(auto i = CreatePool::__pool.begin(); i != CreatePool::__pool.end(); ++i) {
        if((*i)->__enemy_code == __ECODE_BOMBCHICK__) {
        --CreatePool::content.__bombChick;
        ++Char_M::data.enemyNum.__bombChick;
        
          __RESET_ENEMY__;
          (*i)->__bombState = BombState::None;
          (*i)->__kindlingTick = 0;
          
          CreatePool::__buf = std::move(*i);
          CreatePool::__pool.erase(i);
          return true;
        }
      }
    } break;
    case(__ECODE_CHICK__): default: {
      if(!CreatePool::content.__chick) return false;
      else for(auto i = CreatePool::__pool.begin(); i != CreatePool::__pool.end(); ++i) {
        if((*i)->__enemy_code == __ECODE_CHICK__) {
        --CreatePool::content.__chick;
        ++Char_M::data.enemyNum.__chick;
        
          __RESET_ENEMY__;
          
          CreatePool::__buf = std::move(*i);
          CreatePool::__pool.erase(i);
          return true;
        }
      }
    } break;
  } return false;
}

inline func Char_M::Enemy::CreatePool::move_from_active(void) -> void {
  for(auto& i : Char_M::Enemy::Alloter::__active) CreatePool::move(i);
                Char_M::Enemy::Alloter::__active.clear();
}

inline func Char_M::Enemy::CreatePool::move(void) -> std::unique_ptr<Enemy> {
  if(CreatePool::__buf.get() == nullptr) {
    sf::err() << "CreatePool: move(): unvalidBuffer";
  } else {
    CreatePool::__buf->__out_of_screen_clock.restart();
    return std::move(CreatePool::__buf);
  } return nullptr;
}

inline func Char_M::Enemy::CreatePool::move(std::unique_ptr<Enemy>& v) -> void {
  switch(v->__enemy_code) {
    case(__ECODE_SHELLPIG__): {
    ++CreatePool::content.__shellPig;
    --Char_M::data.enemyNum.__shellPig;
    } break;
    case(__ECODE_BOMBCHICK__): {
    ++CreatePool::content.__bombChick;
    --Char_M::data.enemyNum.__bombChick;
    } break;
    case(__ECODE_CHICK__): default: {
    ++CreatePool::content.__chick;
    --Char_M::data.enemyNum.__chick;
    } break;
  } CreatePool::__pool.emplace_back(std::move(v));
}

#undef __RESET_ENEMY__
