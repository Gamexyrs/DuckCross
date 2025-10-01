#define __BLOOD_PROGRESS__                    \
  ((!(Char_M::Value::__blood                  \
   && Char_M::Value::__blood_max)) ? -1 :     \
  (static_cast<float>(Char_M::Value::__blood) \
 / static_cast<float>(Char_M::Value::__blood_max)))

inline func PlayView_M::Blood_init(void) -> void {
  this->bl.__prog.setFillColor(sf::ColorEx::LightPink | 70);
  this->bl.__prog.getText().setStyle(sf::Text::Style::Bold);
  this->bl.__prog.getInside().setFillColor(sf::Color::Red);
  this->bl.__prog.setOutlineThickness(2);
  this->bl.__prog.setPerHeight("8%");
  this->bl.__prog.setPerWidth("25%");
  this->bl.__prog.setBuilder(ui_m->__viewpos,
    rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["View_Blood"]));
  this->bl.__prog.setText(L"--", res::__font_en, 80);
  this->bl.__prog.setTextAlign(sf::Align::LT);
  this->bl.__prog.setTextDeviat({30, -8});
  
  if(sys_acti::__actype == sys_acti::ActivityType::Play)
       this->bl.__prog.setProgress(__BLOOD_PROGRESS__);
  else this->bl.__prog.setProgress(1);
}

inline func PlayView_M::Blood_act(void) -> void {
  static bool __nMove{false};
  
  if(Char_M::Value::__update_blood) {
     Char_M::Value::__update_blood = false;
    if(Char_M::Duck::__v->noBlood()) {
      this->bl.__prog.setTextString(L"");
      this->bl.__prog.setProgress(-1);
    } else if(sys::__cheat___allow_duck_unlimited_blood__) {
      this->bl.__prog.setTextString(L"∞");
      this->bl.__prog.setProgress(1);
    } else {
      this->bl.__prog.setTextString(std::to_wstring(Char_M::Value::__blood));
      if(this->__signal_reload__) {
        this->bl.__prog.setProgress(__BLOOD_PROGRESS__);
      } else __nMove = true;
    }
  } else if(__nMove) {
         if(this->bl.__prog.getProgress() - __BLOOD_PROGRESS__ < -0.02)
            this->bl.__prog.movProgress( 0.008f / sys::tickSync());
    else if(Char_M::Value::__blood == Char_M::Value::__blood_max) {
            this->bl.__prog.setProgress(1); __nMove = false; }
    else if(this->bl.__prog.getProgress() - __BLOOD_PROGRESS__ >  0.02)
            this->bl.__prog.movProgress(-0.008f / sys::tickSync());
    else __nMove = false;
  }
}

#undef __BLOOD_PROGRESS__
