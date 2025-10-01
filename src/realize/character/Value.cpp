inline func Char_M::Value::autophagy(void) -> void {
  Char_M::Value::__update_blood = true;
  Char_M::Value::__blood = 0;
  Char_M::Value::__food  = 0;
}

inline func Char_M::Value::reset(void) -> void {
  // Duck
  Char_M::Value::__speed_f   = 1;
  Char_M::Value::__blood_max = 50;
  Char_M::Value::__blood     = __blood_max; Char_M::Value::__update_blood = true;
  Char_M::Value::__food_f    = 1;
  Char_M::Value::__food      = 100;
  Char_M::Value::__level     = 0;           Char_M::Value::__update_level = false;
  Char_M::Value::__exp_f     = 1;
  Char_M::Value::__exp       = 0;           Char_M::Value::__update_exp = true;
  
  // Weapon
  Char_M::Value::__attack_f = 1.0f;         // 加成倍数
  Char_M::Value::__attack_crit_p = 0.15f;   // 暴击概率
  Char_M::Value::__attack_crit_f = 1.8f;    // 暴击倍数
  Char_M::Value::__attack_r_f = 1.0f;       // 远程加成倍数
  Char_M::Value::__attack_c_f = 1.0f;       // 近程加成倍数
  Char_M::Value::__attack_speed_r_f = 1.0f; // 远程攻速倍数
  Char_M::Value::__attack_speed_c_f = 1.0f; // 近程攻速倍数
  
  Char_M::Value::__attack_e_fire = 1.0f;    // 火加成倍数
  Char_M::Value::__attack_e_ice = 1.0f;     // 冰加成倍数
  Char_M::Value::__attack_e_water = 1.0f;   // 水加成倍数
  Char_M::Value::__attack_e_poison = 1.0f;  // 毒加成倍数
  
  // Enemy
  Char_M::Value::__vampirism_f = 1.0f; // 吸血
  Char_M::Value::__thorns_f = 1.0f;    // 荆棘
  
  // Storage
  Char_M::Value::__coin_f = 1.0f; // 金币收益
  Char_M::Value::__luck = 0; // 幸运
  
  // Record
  Char_M::Value::__total_attkV = 0; // 累计攻击量
  Char_M::Value::__total_cureV = 0; // 累计治疗量
  Char_M::Value::__total_move = 0; // 总移动距离
  Char_M::Value::__total_attk = 0; // 攻击次数
  Char_M::Value::__total_hit = 0; // 命中次数
  
}
