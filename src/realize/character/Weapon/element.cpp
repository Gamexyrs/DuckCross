inline func Char_M::Element::attCast(const Type& v1, const Type& v2) -> float {
  if(v1 == Char_M::Element::None) return 1.0f;
  
  if(v1 == Char_M::Element::Fire) {
    if(v2 == Char_M::Element::Ice)   return 2.0f * Char_M::Value::__attack_e_fire;
    if(v2 == Char_M::Element::Water) return 1.5f * Char_M::Value::__attack_e_fire;
    return 1.0f * Char_M::Value::__attack_e_fire;
  }
  
  if(v1 == Char_M::Element::Ice) {
    if(v2 == Char_M::Element::Water) return 1.5f * Char_M::Value::__attack_e_ice;
    return 1.0f * Char_M::Value::__attack_e_ice;
  }
  
  if(v1 == Char_M::Element::Water)  return 1.0f * Char_M::Value::__attack_e_water;
  if(v1 == Char_M::Element::Poison) return 1.0f * Char_M::Value::__attack_e_poison;
  
  return 1.0f;
}
