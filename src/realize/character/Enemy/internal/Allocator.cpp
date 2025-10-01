inline func Char_M::Enemy::Allocator::update(void) -> void {
  Char_M::Enemy::Alloter::update();
  ChickBoss::update();
  
  for(auto i  = Char_M::Enemy::Alloter::__active.begin();
           i != Char_M::Enemy::Alloter::__active.end();) {
    if(*i != nullptr) {
      (*i)->act();
      
      if((*i)->__inview) {
        if(Char_M::Weapon::__signal_call_att) {
           Char_M::Weapon::__v->attValid(i->get());
        }
        
        for(auto& j : Char_M::Weapon::__bullet) {
          if((*i)->__exmove != sf::Vector2f{} && Char_M::Skill::__bulletTime) break;
          else if(j.first.getBounds().intersects((*i)->__realRect)) {
            Char_M::Weapon::__v->__attk_bullet = &j;
            Char_M::Weapon::__v->attValid(i->get()); break;
          }
        }
      }
      
      if(Char_M::Enemy::__signal_call_del) {
         Char_M::Enemy::__signal_call_del = false;
         CreatePool::move(*i);
         i = Char_M::Enemy::Alloter::__active.erase(i);
      } else ++i;
    }   else   i = Char_M::Enemy::Alloter::__active.erase(i);
  } Char_M::Weapon::__signal_call_att = false;
}
