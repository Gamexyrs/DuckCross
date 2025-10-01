#define __SEND_MSG__(str, n) { \
  PlayView_M::__msgBoxStr.push(std::make_pair<sf::String, size_t>(str, n)); }
#define __SEND_ITEM__(item, n) { \
  __SEND_MSG__(L"获得 " + sis::ItemName.find(item)->second.first, n); Storage_M::__buf.push(item, n); }

#include "./Item.hpp"
#include "./ItemVector.hpp"

typedef class Storage_Manager {
protected:
  inline static rj::Document dom{};

_data_public:
  inline static sis::ItemVector __buf{},
                                __safe{};
  
_func_public:
  // json
  static func loadJ(bool _safe = true) -> void;
  static func saveJ(bool _safe = true) -> void;
  
  static func reload(void) -> void;
  
} Storage_M;
