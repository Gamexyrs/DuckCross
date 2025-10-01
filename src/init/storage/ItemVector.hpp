/* system_ item serve */
namespace sis {
  class ItemVector {
  _data_public:
    std::unordered_map<sis::Item, size_t>
         __list{{sis::Item::Unknown, 0}};
  
    bool __signal_update{true};
  
  _func_public:
    func clear(const sis::Item& = sis::Item::Unknown) -> void;
    
    func find (const sis::Item&)             -> item_t;
    
    func size (const sis::Item&)             -> size_t&;
    
    func push (const sis::Item&, size_t = 1) -> size_t&;
    func pop  (const sis::Item&, size_t = 1) -> size_t&;
    
  };
}
