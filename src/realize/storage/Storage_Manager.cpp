#include "./ItemVector.cpp"

inline func Storage_M::loadJ(bool _safe) -> void {
  sis::ItemVector& __refer = (_safe ? Storage_M::__safe : Storage_M::__buf);

  if(Json_M::parseJ(Storage_M::dom, _safe ? __PATH_STORAGE_JSON__ : __PATH_STORBUF_JSON__)) {
         __GET_JVALUE__(Storage_M::dom, "coin", Uint64, __refer.size(sis::Item::Coin)) else return;
    if(__CHECK_JVALUE__(Storage_M::dom, "item", Object)) {
      for(auto it = Storage_M::dom["item"].MemberBegin(); it != Storage_M::dom["item"].MemberEnd(); ++it) {
        if((it->value).IsUint64()) {
          __refer.size(sis::ItemName_Callback[(it->name).GetString()]) = (it->value).GetUint64();
        } else return;
      }
    }
  }
}

inline func Storage_M::saveJ(bool  _safe) -> void {
  sis::ItemVector& __refer = (_safe ? Storage_M::__safe : Storage_M::__buf);
  
  __NEW_OBJECT__({
    Json_M::writer.Key("coin"); Json_M::writer.Uint64(__refer.size(sis::Item::Coin));
    
    Json_M::writer.Key("item"); __NEW_OBJECT__({
      for(const auto& i : __refer.__list) {
        if(i.first == sis::Item::Unknown
        || i.first == sis::Item::Coin
        ||!i.second) continue;
        
        Json_M::writer.Key(sis::ItemName.find(i.first)->second.second
          .toAnsiString().c_str()); Json_M::writer.Uint64(i.second);
      }
    });
  });
  Json_M::writeJ(_safe ? __PATH_STORAGE_JSON__ : __PATH_STORBUF_JSON__);
  __refer.__signal_update = false;
}

inline func Storage_M::reload(void) -> void {
  Storage_M::loadJ(false);
  Storage_M::__buf.__signal_update = true;
}
