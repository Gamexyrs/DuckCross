inline func Char_M::Enemy::Alloter::reset(void) -> void {
  Char_M::Enemy::Alloter::enemyNum.__chick     = 0;
  Char_M::Enemy::Alloter::enemyNum.__bombChick = 0;
  Char_M::Enemy::Alloter::enemyNum.__shellPig = 0;
  Char_M::Enemy::Alloter::__need_update = true;
  Char_M::Enemy::Alloter::__active.clear();
  Char_M::data.enemyNum.__chick = 0;
  Char_M::data.enemyNum.__bombChick = 0;
  Char_M::data.enemyNum.__shellPig = 0;
  
  ChickBoss::__proceed = ChickBossState::None;
  ChickBoss::__boss_living = false;
  ChickBoss::__boss_died = false;
  ChickBoss::__this.release();
}

inline func Char_M::Enemy::Alloter::update(void) -> void {
  Char_M::Enemy::Alloter::update_active();

  if(Char_M::Duck::__v->noBlood() || sf::Msgable::getLocked() || ChickBoss::__proceed != ChickBossState::None) return;
  
  if(Char_M::Enemy::Alloter::__need_update || !Char_M::Enemy::Alloter::enemyNum.__chick || !Char_M::Enemy::Alloter::__active.size()) {
     Char_M::Enemy::Alloter::__need_update = false;
     
     Char_M::Enemy::Alloter::enemyNum.__chick = static_cast<size_t>(std::pow(Char_M::Value::__level, 1.5)) + 5;
     Char_M::Enemy::Alloter::enemyNum.__bombChick = static_cast<size_t>(std::pow(Char_M::Value::__level, 1.2)) + 2;
     
     if(Char_M::Value::__level < 4) goto no_more;
     
     Char_M::Enemy::Alloter::enemyNum.__shellPig = Char_M::Value::__level - 1;
     
  } no_more:
  
  if(Char_M::data.enemyNum.__chick < Char_M::Enemy::Alloter::enemyNum.__chick) {
    if(  Char_M::Enemy::CreatePool::valid(__ECODE_CHICK__))
         Char_M::Enemy::Alloter::__active.emplace_back(Char_M::Enemy::CreatePool::move());
    else Char_M::Enemy::Alloter::__active.emplace_back(std::move(std::make_unique<Char_M::Enemy::Chick>()));
    return;
  }
  if(Char_M::data.enemyNum.__bombChick < Char_M::Enemy::Alloter::enemyNum.__bombChick) {
    if(  Char_M::Enemy::CreatePool::valid(__ECODE_BOMBCHICK__))
         Char_M::Enemy::Alloter::__active.emplace_back(Char_M::Enemy::CreatePool::move());
    else Char_M::Enemy::Alloter::__active.emplace_back(std::move(std::make_unique<Char_M::Enemy::BombChick>()));
    return;
  }
  if(Char_M::data.enemyNum.__shellPig < Char_M::Enemy::Alloter::enemyNum.__shellPig) {
    if(  Char_M::Enemy::CreatePool::valid(__ECODE_SHELLPIG__))
         Char_M::Enemy::Alloter::__active.emplace_back(Char_M::Enemy::CreatePool::move());
    else Char_M::Enemy::Alloter::__active.emplace_back(std::move(std::make_unique<Char_M::Enemy::ShellPig>()));
    return;
  }
}

inline func Char_M::Enemy::Alloter::update_active(void) -> void {
  // Char_M::Enemy::Alloter::__active_inview.clear();
  // Char_M::Enemy::Alloter::__active_inzone.clear();
  
  for(auto& i : Char_M::Enemy::Alloter::__active) {
    i->__inview = false;
    i->__inzone = false;
    
    if(i->__s.getGlobalBounds().intersects(sf::Renderable::getViewRect())) {
       i->__inview = true;
      // Char_M::Enemy::Alloter::__active_inview.emplace_back(i);
      if(i->__s.getGlobalBounds().intersects(sf::FloatRect{sf::Fm::getCenter(Char_M::Duck::__v->__realRect).x - 200, sf::Fm::getCenter(Char_M::Duck::__v->__realRect).y - 200, 400, 400})) {
         i->__inzone = true;
        // Char_M::Enemy::Alloter::__active_inzone.emplace_back(i);
      }
    }
  }
}
