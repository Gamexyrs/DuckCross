inline func Char_M::Skill::randOut(void) -> const std::vector<std::string> {
  std::vector<std::string> __available{};
  
  // 重新加载
  if(     !Char_M::Skill::__reload_list.empty()) {
    return Char_M::Skill::__reload_list;
  }

  // 搜索可用的技能
  for(auto& i : Char_M::Skill::__list)
    if(!std::get<0>(i.second) && std::get<2>(Char_M::Skill::__explain_passive.find(i.first)->second)()) __available.emplace_back(i.first);
  
  // 无可用技能
  if(!__available.size()) {
    __SEND_MSG__(L"⚠ 当前状态无可用技能", 0);
    return Char_M::Skill::__reload_list;
  }

  // 技能不足
  if(__available.size() <= 3) {
    Char_M::Skill::__reload_list = __available;
    Char_M::Skill::__reload_list.resize(3);
  } else for(int i = 0; i < 3; ++i) {
refor:
    std::string __tmp{__available.at(sys::rand<size_t>({0, __available.size() - 1}))};
    // 防重复
    if(__available.size() > 3)
      for(const auto& r : Char_M::Skill::__reload_list) if(__tmp == r) goto refor;
      
           Char_M::Skill::__reload_list.emplace_back(__tmp);
  } return Char_M::Skill::__reload_list;
}

inline func Char_M::Skill::require(const std::string& __require, bool actived) -> void {
  if(actived) {
    Char_M::Skill::__enable_actived_list.emplace_back(__require);
    Char_M::Skill::__signal_update_skills_actived = true;
    
  } else {
    auto& __this{Char_M::Skill::__list.find(__require)->second};
    
    if(std::get<0>(__this)) { return; }
       std::get<0>(__this) = true;
    if(std::get<1>(__this)) {
       std::get<2>(__this)
      (std::get<3>(__this));
       std::get<1>(__this) = 2;
    } Char_M::Skill::__enable_list.emplace_back(__require);
  }
}

inline func Char_M::Skill::taken(const std::string& v) -> bool {
  return std::find(Char_M::Skill::__enable_list.begin(),
                   Char_M::Skill::__enable_list.end(),v)
                != Char_M::Skill::__enable_list.end();
}

inline func Char_M::Skill::reset(void) -> void {
  for(auto& i : Char_M::Skill::__list) {
    std::get<3>(i.second) = ((std::get<3>(i.second) == -1) ? -1 : 0);
    std::get<1>(i.second) = static_cast<bool>(std::get<1>(i.second));
    std::get<0>(i.second) = false;
  } __enable_list.clear();
    __enable_actived_list.clear();
    __reload_list.clear();
  Char_M::Skill::__signal_update_skills_actived = true;
  Char_M::Value::reset();
}

inline func Char_M::Skill::call(void) -> void {
  if(Char_M::Duck::__v->noBlood() || sf::Msgable::getLocked())
     Char_M::Skill::__signal_reset_clock = true;
  else {
    for(auto& i : Char_M::Skill::__list)
      if(std::get<0>(i.second)
      &&!std::get<1>(i.second))
         std::get<2>(i.second)
        (std::get<3>(i.second));
    Char_M::Skill::__signal_reset_clock = false;
  }
}

inline func Char_M::Skill::level_up(const std::string& __t, int __n) -> void {
  std::get<3>(Char_M::Skill::__list.find(__t)->second) += __n;
}
