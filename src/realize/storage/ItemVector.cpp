/* system_ item serve */
namespace sis {
  inline func ItemVector::clear(const sis::Item& v) -> void {
    this->__signal_update = true;
    if(v == sis::Item::Unknown) {
      this->__list.clear();
      this->__list.insert(
        std::make_pair<sis::Item, size_t>(sis::Item::Unknown, 0));
    } else this->size(v) = 0;
  }
  
  inline func ItemVector::find(const sis::Item& v) -> item_t {
    static sis::item_t it{};
    return ((it = this->__list.find(v)) == this->__list.end())
                ? this->__list.find(sis::Item::Unknown) : it;
  }
  
  inline func ItemVector::size(const sis::Item& v) -> size_t& {
    return this->__list[v];
  }
  
  inline func ItemVector::push(const sis::Item& v, size_t n) -> size_t& {
    this->__signal_update = true;
    return this->size(v) += n * ((v == sis::Item::Coin) ? Char_M::Value::__coin_f : 1.0f);
  }
  
  inline func ItemVector::pop (const sis::Item& v, size_t n) -> size_t& {
    this->__signal_update = true;
    return this->size(v) -= n;
  }
}
