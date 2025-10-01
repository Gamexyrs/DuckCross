func Audio_M::update(void) -> void {
  // 循环
  if(this->__music.getStatus() == sf::Music::Status::Playing
  && this->__music.getPlayingOffset().asSeconds() >= this->__music.getDuration().asSeconds() - 3) {
    if(sys_acti::__actype == sys_acti::ActivityType::Play) this->call_next_play();

    this->__music.setPlayingOffset(sf::Time::Zero);
    this->__music.setVolume(0);
    
    this->__signal_music_update = true;
  }
  
  // NO UPDATE
  if(!this->__signal_music_update) return;
  
  // 暂停
  if(!sys::__jcontext["Audio"]["BackgroundMusic"].GetBool() || this->__music_inline == ".stop") {
    if(this->__music.getVolume() > 1)
       this->__music.setVolume(this->__music.getVolume() - 1);
    else if(this->__music.getStatus() == sf::Music::Status::Playing)
            this->__music.stop();
    else this->__signal_music_update = false;
  }
  // 切换
  else if(!this->__music_inline.empty()) {
    if(this->__music.getVolume() > 1)
       this->__music.setVolume(this->__music.getVolume() - 1);
    else {
      if(!this->__music.openFromFile(this->__music_now))
        sf::err() << ("unknown music: " + this->__music_now);
      // 继续
      if(this->__music_now.find("bgm_play") != std::string::npos)
         this->__music.setPlayingOffset(this->__music_play_offset);
      
      this->__music_inline = "";
    }
  }
  // 开始
  else {
    if(this->__music.getStatus() == sf::Music::Status::Stopped) {
       this->__waitForMusic.restart();
       this->__music.play();
    }
    if(this->__waitForMusic.getElapsedTime().asSeconds() >= 0.8) {
      if(  this->__music.getVolume() < 55)
           this->__music.setVolume(this->__music.getVolume() + 1);
      else this->__signal_music_update = false;
    }
  }
}

func Audio_M::call_next(const std::string& __n) -> void {
  std::string __music_next{"./src/res/audio/music/" + __n + ".ogg"};

  if(this->__music_now == __music_next) return;
  
  if(this->__music_now.find("bgm_play") != std::string::npos)
     this->__music_play_offset = this->__music.getPlayingOffset();
  
  if(__n == ".stop")
       this->__music_now = __n;
  else this->__music_now = __music_next;
  
  this->__music_inline = this->__music_now;
  this->__signal_music_update = true;
}

func Audio_M::call_next_play(void) -> void {
  // int __i{-1};
  // do  __i = sys::rand({0, 1});
    // while(__i == this->__play_music_code); // adaption: unknown error
  // this->__play_music_code = __i;
  
  this->__play_music_code = !this->__play_music_code;
  
  this->__music_play_offset = sf::Time::Zero;
}

Audio_M::Audio_Manager(void) {
  this->__music.setLoop(true);
  this->__music.setVolume(0);
  
  this->__sound.__levelup.second = sys::__jcontext["Audio"]["LevelupSound"].GetBool();
  this->__sound.__levelup.first.setBuffer(*res::__soundbf_levelup);
  
  this->__sound.__kill.second = sys::__jcontext["Audio"]["KillSound"].GetBool();
  this->__sound.__kill.first.setBuffer(*res::__soundbf_kill);
  
  this->__sound.__scissors.second = sys::__jcontext["Audio"]["ScissorsSound"].GetBool();
  this->__sound.__scissors.first.setBuffer(*res::__soundbf_scissors);
  
  this->__sound.__pistol.second = sys::__jcontext["Audio"]["PistolSound"].GetBool();
  this->__sound.__pistol.first.setBuffer(*res::__soundbf_pistol);
}
