#pragma once

// load_rapidjson - 745.19K
#pragma   GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wtype-limits"
  #include "./rapidjson/document.h"
  #include "./rapidjson/writer.h"
#pragma GCC diagnostic pop

#define __CHECK_JVALUE__(dom, member, Is_) \
  (dom.HasMember(member) && dom[member].Is##Is_())
  
#define __IF_JVALUE_OK__(dom, member, Is_, DOF_) \
  if(__CHECK_JVALUE__(dom, member, Is_)) DOF_
  
#define __GET_JVALUE__(dom, member, Is_, Var_) \
  if(__CHECK_JVALUE__(dom, member, Is_)) \
    Var_ = dom[member].Get##Is_();
  
#define __SET_JVALUE_IF_NULL__(dom, member, Is_, Set_) { \
  if(!__CHECK_JVALUE__(dom, member, Is_)) dom.AddMember(member, Set_, A_); }
  
#define __SET_JVALUE_VECTOR2__(member, Is_, Set_) { \
  member[0].Set##Is_(Set_.x); \
  member[1].Set##Is_(Set_.y); }
  
#define __NEW_OBJECT__(f) {       \
  Json_M::writer.StartObject(); f \
  Json_M::writer.EndObject(); }
   
#define __NEW_ARRAY__(f) {       \
  Json_M::writer.StartArray(); f \
  Json_M::writer.EndArray(); }

#define __NEW_ARRAY_V2i__(v) { \
  Json_M::writer.StartArray(); \
  Json_M::writer.Int(v.x);     \
  Json_M::writer.Int(v.y);     \
  Json_M::writer.EndArray(); }

#define __NEW_ARRAY_V2f__(v) { \
  Json_M::writer.StartArray(); \
  Json_M::writer.Double(v.x);  \
  Json_M::writer.Double(v.y);  \
  Json_M::writer.EndArray(); }

#ifdef __SFUI_OBJECT__
namespace rapidjson {
  inline func arrayToVector2(const Value& array) -> sf::Vector2f {
    if(array.IsArray() && array.Size() == 2 && array[0].IsDouble() && array[1].IsDouble())
         return{array[0].GetFloat(), array[1].GetFloat()};
    else return{};
  }
}
#endif

namespace rj = rapidjson;
