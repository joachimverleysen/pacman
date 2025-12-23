#ifndef PACMAN_SOUNDPLAYER_H
#define PACMAN_SOUNDPLAYER_H

#include <SFML/Audio.hpp>
#include <memory>
#include "../../logic/utils/Visitor.h"

struct Sound {
  Sound(std::shared_ptr<sf::SoundBuffer> buffer, std::shared_ptr<sf::Sound> sound)
    : buffer_(buffer), sound_(sound) {}
  std::shared_ptr<sf::SoundBuffer> buffer_;
  std::shared_ptr<sf::Sound> sound_;
};

// Singleton
class SoundPlayer : public Visitor {
  static SoundPlayer* instance_;
  std::vector<std::shared_ptr<Sound>> sounds_;
  std::shared_ptr<Sound> eatghost_ = nullptr;
  std::shared_ptr<Sound> interruptable_ = nullptr;

private:
  SoundPlayer() {};
public:
  static SoundPlayer* getInstance() {
    if (!instance_)
      instance_ = new SoundPlayer;
    return instance_;
  }

  void update();

  void play(const char* file) {
    update();
    auto buffer = std::make_shared<sf::SoundBuffer>();
    if (!buffer->loadFromFile(file))
      throw(std::invalid_argument("Invalid sound file"));
    auto sound = std::make_shared<sf::Sound>(*buffer);
    auto sound_struct = std::make_shared<Sound>(buffer, sound);
    sounds_.push_back(sound_struct);
    sound->setVolume(50.f);
    sound->play();
    update();
  };

  void playInterruptable(const char* file) {
    auto buffer = std::make_shared<sf::SoundBuffer>();
    if (!buffer->loadFromFile(file))
      throw(std::invalid_argument("Invalid sound file"));
    auto sound = std::make_shared<sf::Sound>(*buffer);
    interruptable_ = std::make_shared<Sound>(buffer, sound);
    sound->setVolume(50.f);
    sound->play();
  };

  void playEatghost() {
    if (eatghost_) eatghost_ = nullptr;
    update();
    auto buffer = std::make_shared<sf::SoundBuffer>();
    if (!buffer->loadFromFile("assets/audio/pacman-eatghost.wav"))
      throw(std::invalid_argument("Invalid sound file"));
    auto sound = std::make_shared<sf::Sound>(*buffer);
    auto sound_struct = std::make_shared<Sound>(buffer, sound);
    eatghost_ = sound_struct;
    sound->setVolume(50.f);
    sound->play();
  }

  void shutDown() {
    for (auto &s : sounds_)
      s->sound_->stop();

    if (interruptable_)
      interruptable_->sound_->stop();
    if (eatghost_)
      eatghost_->sound_->stop();

    sounds_.clear();
    interruptable_ = nullptr;
    eatghost_ = nullptr;

  }

  void visit(CoinEatenEvent &event) override {
    playInterruptable("assets/audio/pacman-munch.wav");
  };

  void visit(FruitEatenEvent &event) override {
    play("assets/audio/pacman-eatfruit.wav");
  }

  void visit(GhostEatenEvent &event) override {
    playEatghost();
  }

  void visit(FrightenGhostsEvent &event) override {
  }

  void visit(PacmanDiesEvent &event) override {
    play("assets/audio/pacman-death.wav");
  }

  void visit(NewLevelEvent &event) override {
    play("assets/audio/beginning.wav");
  }
};

inline SoundPlayer *SoundPlayer::instance_ = nullptr;

inline void SoundPlayer::update() {
  sounds_.erase(
    std::remove_if(sounds_.begin(), sounds_.end(),
      [](const std::shared_ptr<Sound> &sound) {
        return sound->sound_->getStatus() == sf::SoundSource::Status::Stopped;
      }),
      sounds_.end());
}


#endif //PACMAN_SOUNDPLAYER_H
