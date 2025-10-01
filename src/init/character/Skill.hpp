#define __FUNC__ []([[maybe_unused]] int __level = -1) -> void
#define __REQUIRE_NULL__ [](void) -> bool {return true;}
#define __REQUIRE__(v) [](void) -> bool {return v;}

class Char_M::Skill {
_func_public:
  static func randOut(void) -> const std::vector<std::string>;
  static func require(const std::string&, bool actived = false) -> void;
  static func taken  (const std::string&) -> bool;
  static func reset  (void) -> void;
  static func call   (void) -> void;
  
_data_public:
  inline static bool __signal_reset_clock{false};
  inline static bool __signal_update_skills_actived{true};
  
  inline static bool __bulletTime{false};
  
  // new: 
  const inline static std::unordered_map<std::string, std::tuple<sf::String, sf::String, bool(*)(void)>> __explain_passive {
    {"diet",             {L"节食",     L"减少 40% 饱食消耗", __REQUIRE_NULL__}},
    {"skilled",          {L"熟练",     L"增加 10% 经验获取", __REQUIRE_NULL__}},
    {"loot",             {L"掠夺",     L"增加 35% 金币获取", __REQUIRE_NULL__}},
    
    {"puffy",            {L"发福",     L"增加 20% 最大生命; 减少 10% 移速", __REQUIRE_NULL__}},
    {"overweight",       {L"超重",     L"增加 40% 最大生命; 减少 20% 移速", __REQUIRE__(taken("puffy"))}},
    {"dope",             {L"兴奋剂",   L"增加 10% 移速", __REQUIRE_NULL__}},
    {"sneakers",         {L"运动爪",   L"增加 5% 移速", __REQUIRE_NULL__}},
    
    {"cruel",            {L"残忍",     L"增加 40% 暴击伤害", __REQUIRE_NULL__}},
    {"aim",              {L"瞄准",     L"增加 20% 暴击概率", __REQUIRE_NULL__}},
    {"quick",            {L"敏捷",     L"近战武器 增加 20% 攻速", __REQUIRE_NULL__}},
    {"grindstone",       {L"磨刀石",   L"近战武器 增加 40% 攻击", __REQUIRE_NULL__}},
    {"lightTrigger",     {L"轻型扳机", L"远程武器 增加 20% 攻速", __REQUIRE_NULL__}},
    {"heavyBullets",     {L"重型子弹", L"远程武器 增加 50% 攻击", __REQUIRE_NULL__}},
    {"fireBullets",      {L"火焰子弹", L"子弹可以安全地引爆炸弹鸡", __REQUIRE__(taken("heavyBullets"))}},
    
    {"treat",            {L"治疗 Ⅰ",     L"每 10秒 增加 5 生命值", __REQUIRE_NULL__}},
      {"treat_quick",    {L"快速治疗 Ⅱ", L"恢复生命值的时间 减少 3秒", __REQUIRE__(taken("treat"))}},
      {"treat_potent",   {L"强效治疗 Ⅱ", L"恢复生命值的量 增加 5",     __REQUIRE__(taken("treat"))}},
        {"vampirism",    {L"吸血",       L"每击杀一只怪物，有 20% 可能性获取其最大生命值的 10% 的生命值", __REQUIRE__(taken("treat_quick") && taken("treat_potent"))}},
        {"thorns",       {L"荆棘",       L"受到 普通攻击 时，自动对攻击者造成受到伤害 30% 的攻击", __REQUIRE__(taken("treat_quick") && taken("treat_potent"))}},
    
    {"explodedEyes",     {L"爆炸眼",   L"每 10秒 以自身为圆心发生一次安全的大爆炸", __REQUIRE_NULL__}},
    {"poison",           {L"毒液",     L"每秒对身边的敌人造成 毒元素 伤害", __REQUIRE_NULL__}},
  };
  
  const inline static std::unordered_map<std::string, std::tuple<sf::String, float, float, std::string>> __explain_actived {
    {"bulletTime",       {L"子弹时间", 30.0f, 10.0f, "./src/res/img/sgv/surface/skill_actived/bulletTime.png"}},
  };
  inline static std::unordered_map<std::string, sf::Timer> __clock_actived {
    {"bulletTime", sf::Timer{sf::Time::Zero, true}},
  };
  
  inline static std::vector<std::string>
    __enable_list{}, /* 已选择 */
    __enable_actived_list{}, /* 已选择 */
    __reload_list{}; /* 选择中 */
  
protected:
  static func level_up(const std::string&, int = 1) -> void;

  /* state -> false: byTime   true: once   2: out of use */
  inline static std::unordered_map<std::string, std::tuple</* valid */bool, /* state */int, /* function */void(*)(int), /* level */int>> __list {
    {"diet",    {false, true, __FUNC__{ Char_M::Value::__food_f *= 0.6f; }, -1}},
    // <节食>   [Once] 增加 20% 饮食消耗
    {"skilled", {false, true, __FUNC__{ Char_M::Value::__exp_f *= 1.1f; }, -1}},
    // <熟练>   [Once] 增加 10% 经验获取
    {"loot", {false, true, __FUNC__{ Char_M::Value::__coin_f *= 1.35f; }, -1}},
    // <掠夺>   [Each] 增加 35% 金币获取
    
    {"puffy",   {false, true, __FUNC__{
      Char_M::Value::__update_blood = true;
      Char_M::Value::__blood_max *= 1.2f;
      Char_M::Value::__speed_f *= 0.9f; }, -1}},
    // <发福>   [Once] 增加 20% 最大生命 + 减少 10% 移速
    {"overweight", {false, true, __FUNC__{
      Char_M::Value::__update_blood = true;
      Char_M::Value::__blood_max *= 1.4f;
      Char_M::Value::__speed_f *= 0.8f; }, -1}},
    // <超重>   [Once] 增加 40% 最大生命 + 减少 20% 移速
    {"dope",  {false, true, __FUNC__{ Char_M::Value::__speed_f *= 1.1f; }, -1}},
    // <兴奋剂> [Once] 增加 10% 移速
    {"sneakers", {false, true, __FUNC__{ Char_M::Value::__speed_f *= 1.05f; }, -1}},
    // <运动爪> [Once] 增加 5% 移速
    
    {"cruel",        {false, true, __FUNC__{ Char_M::Value::__attack_crit_f *= 1.4f; }, -1}},
    // <残忍>     [Once] 增加 40% 暴击
    {"aim",          {false, true, __FUNC__{ Char_M::Value::__attack_crit_p *= 1.2f; }, -1}},
    // <瞄准>     [Once] 增加 20% 爆率
    {"quick",        {false, true, __FUNC__{ Char_M::Value::__attack_speed_c_f *= 1.2f; }, -1}},
    // <敏捷>     [Once] 近战武器 增加 20% 攻速
    {"grindstone",   {false, true, __FUNC__{ Char_M::Value::__attack_c_f *= 1.4f; }, -1}},
    // <磨刀石>   [Once] 近战武器 增加 40% 攻击
    {"lightTrigger", {false, true, __FUNC__{ Char_M::Value::__attack_speed_r_f *= 1.2f; }, -1}},
    // <轻型扳机> [Once] 远程武器 增加 20% 攻速
    {"heavyBullets", {false, true, __FUNC__{ Char_M::Value::__attack_r_f *= 1.5f; }, -1}},
    // <重型子弹> [Once] 远程武器 增加 50% 攻击
    {"fireBullets", {false, true, __FUNC__{}, -1}},
    // <火焰子弹> [Each] 子弹可以安全地引爆炸弹鸡
    
    {"treat", {false, false, __FUNC__{
      static sf::Clock __clock{};
      if(Char_M::Skill::__signal_reset_clock) __clock.restart();
      if(__clock.getElapsedTime().asSeconds() >= ((__level >= 1) ? 7 : 10)) {
         __clock.restart(); Char_M::Value::effect.__blood += ((__level >= 2) ? 10 : 5);
      }
    }, 0}},
    // <治疗> [E10s] 增加 5 生命值
      {"treat_quick",  {false, true, __FUNC__{ level_up("treat", 1); }, -1}},
      // <快速治疗> [UP⁺] 恢复生命值的时间 减少 3秒
      {"treat_potent", {false, true, __FUNC__{ level_up("treat", 2); }, -1}},
      // <强效治疗> [UP⁺] 恢复生命值的量 增加 5
    {"vampirism", {false, true, __FUNC__{ Char_M::Value::__vampirism_f *= 1.1f; }, -1}},
    // <吸血> [Each] 每击杀一只怪物，有 20% 可能性获取其最大生命值的 10% 的生命值
    {"thorns", {false, true, __FUNC__{ Char_M::Value::__thorns_f *= 1.3f; }, -1}},
    // <荆棘> [Each] 受到攻击时，自动对攻击者造成受到伤害 30% 的攻击
    
    {"explodedEyes", {false, false, __FUNC__{
      static sf::Clock __clock{};
      if(Char_M::Skill::__signal_reset_clock) __clock.restart();
      else if(__clock.getElapsedTime().asSeconds() >= 10) {
         __clock.restart(); Char_M::Explode::make(sf::Fm::getCenter(Char_M::Duck::__v->__realRect), 200, true);
      }
    }, -1}},
    // <爆炸眼> [E10s] 以自身为圆心发生一次安全的大爆炸
    {"poison", {false, false, __FUNC__{
      static sf::Clock __clock{};
      if(Char_M::Skill::__signal_reset_clock) __clock.restart();
      else if(__clock.getElapsedTime().asSeconds() >= 1) {
         __clock.restart(); Char_M::Explode::make_poison();
      }
    }, -1}},
    // <毒液> [E1s] 每秒对身边的敌人造成 毒元素 伤害
  };
};

#undef __FUNC__
#undef __REQUIRE_NULL__
#undef __REQUIRE__
