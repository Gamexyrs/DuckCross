inline func Acc_M::checkMaxPoints(size_t __n) -> bool {
  if(Acc_M::__play_data.find("max_points")->second < __n) {
     Acc_M::__play_data.find("max_points")->second = __n;
     Acc_M::__signal_update = true;
    return true;
  } return false;
}

inline func Acc_M::getMaxPoints(void) -> size_t {
  return Acc_M::__play_data.find("max_points")->second;
}

inline func Acc_M::clear(void) -> void {
  Json_M::ofs.open(__PATH_ACCOUNT_JSON__, std::ios::trunc);
  Json_M::ofs.close();
  
  for(auto& i : __enemy_data) i.second = 0;
  for(auto& i :  __play_data) i.second = 0;
}

inline func Acc_M::loadJ(void) -> void {
  Acc_M::__runTimeClock.restart();
  if(Json_M::parseJ(Acc_M::dom, __PATH_ACCOUNT_JSON__)) {
    if(__CHECK_JVALUE__( Acc_M::dom,"enemy", Object)) {
      for(auto it = Acc_M::dom["enemy"].MemberBegin(); it != Acc_M::dom["enemy"].MemberEnd(); ++it) {
        if((it->value).IsUint()) __enemy_data.find((it->name).GetString())->second = (it->value).GetUint();
      }
    }
    if(__CHECK_JVALUE__( Acc_M::dom,"play", Object)) {
      for(auto it = Acc_M::dom["play"].MemberBegin(); it != Acc_M::dom["play"].MemberEnd(); ++it) {
        if((it->value).IsUint()) __play_data.find((it->name).GetString())->second = (it->value).GetUint();
      }
    }
  }
}

inline func Acc_M::saveJ(void) -> void {
  Acc_M::__play_data.find("time_play")->second += Acc_M::__runTimeClock.restart().asSeconds();
  
  __NEW_OBJECT__({
    Json_M::writer.Key("enemy"); __NEW_OBJECT__({
      for(const auto& i : __enemy_data)
        if(i.second) { Json_M::writer.Key(i.first.c_str()); Json_M::writer.Uint(i.second); }
    });
    Json_M::writer.Key("play"); __NEW_OBJECT__({
      for(const auto& i : __play_data)
        if(i.second) { Json_M::writer.Key(i.first.c_str()); Json_M::writer.Uint(i.second); }
    });
  });
  Json_M::writeJ(__PATH_ACCOUNT_JSON__); Acc_M::__signal_update = false;
}
