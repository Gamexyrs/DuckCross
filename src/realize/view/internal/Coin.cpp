inline func PlayView_M::Coin_init(void) -> void {
  this->co.__t.loadFromFile("./src/res/img/sgv/coin.png");
  this->co.__t.setSmooth(sys::__smoothTex);
  
  this->co.__pic.setSize({60, 60});
  this->co.__pic.setBuilder(ui_m->__viewpos);
  this->co.__pic.getBase().setTexture(&this->co.__t);
  this->co.__pic.setOutlineThickness(0);
  this->co.__pic.align(sf::Align::L)
    += rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["View_Coin"]);
  
  this->co.__num.setText("--", res::__font_en);
  this->co.__num.setTextColor(sf::ColorEx::Orange);
  this->co.__num.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->co.__num.setBuilder(this->co.__pic, sf::Vector2f{6, 12}, sf::Vector2b{true, false});
}

inline func PlayView_M::Coin_act(void) -> void {
  if(!Storage_M::__buf.__signal_update && !this->__signal_reload__) return;
  size_t __coinNum = Storage_M::__buf.size(sis::Item::Coin);
	std::wstringstream ss; ss << std::setiosflags(std::ios::fixed);
       if(__coinNum < 1'000) {
    ss << __coinNum;
    this->co.__num.setTextString(ss.str());
  }
  else if(__coinNum < 1'000'000) {
    ss << std::setprecision(2) << __coinNum / 1'000.0f;
    this->co.__num.setTextString(ss.str() + L"k");
  }
  else if(__coinNum < 1'000'000'000) {
    ss << std::setprecision(4) << __coinNum / 1'000'000.0f;
    this->co.__num.setTextString(ss.str() + L"M");
  }
  else {
    ss << std::setprecision(6) << __coinNum / 1'000'000'000.0f;
    this->co.__num.setTextString(ss.str() + L"B");
  }
}
