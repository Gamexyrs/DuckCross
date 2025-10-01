inline func sys_acti::call(void) -> void {
    while(sys_acti::__actype != sys_acti::ActivityType::Exit && _Renderer.isOpen()) {
    sys::__jcontext["Actype"] = static_cast<unsigned>(sys_acti::__actype);
    sys::saveJ();
    ui_m->reset();
    
    try { switch(static_cast<sys_acti::ActivityType>(sys::__jcontext["Actype"].GetUint())) {
        case(sys_acti::ActivityType::Play):          sys_acti::__actype = play();          break;
        case(sys_acti::ActivityType::Dever):         sys_acti::__actype = dever();         break;
        case(sys_acti::ActivityType::Settle):        sys_acti::__actype = settle();        break;
        case(sys_acti::ActivityType::Settings):      sys_acti::__actype = settings();      break;
        case(sys_acti::ActivityType::UpdateLog):     sys_acti::__actype = updateLog();     break;
        case(sys_acti::ActivityType::ControlLayout): sys_acti::__actype = controlLayout(); break;
        default: break;
    } } catch(...) { sf::err() << "unknown activity error ... ... ...\n\n"; }
  }
}
