#include "SoundPlayer.h"
#include "../../configure/constants.h"


SoundPlayer *SoundPlayer::instance_ = nullptr;

void SoundPlayer::update() {
  sounds_.erase(
    std::remove_if(sounds_.begin(), sounds_.end(),
      [](const std::shared_ptr<Sound> &sound) {
        return sound->sound_->getStatus() == sf::SoundSource::Status::Stopped;
      }),
      sounds_.end());
}

void SoundPlayer::play(const char *file) {
  update();
  auto buffer = std::make_shared<sf::SoundBuffer>();
  if (!buffer->loadFromFile(file))
    throw(std::invalid_argument("Invalid sound file"));
  auto sound = std::make_shared<sf::Sound>(*buffer);
  auto sound_struct = std::make_shared<Sound>(buffer, sound);
  sounds_.push_back(sound_struct);
  sound->setVolume(Config::Sound::VOLUME);
  sound->play();
  update();
}

void SoundPlayer::playInterruptable(const char *file) {
  auto buffer = std::make_shared<sf::SoundBuffer>();
  if (!buffer->loadFromFile(file))
    throw(std::invalid_argument("Invalid sound file"));
  auto sound = std::make_shared<sf::Sound>(*buffer);
  interruptable_ = std::make_shared<Sound>(buffer, sound);
  sound->setVolume(Config::Sound::VOLUME);
  sound->play();
}

void SoundPlayer::playEatghost() {
  if (eatghost_) eatghost_ = nullptr;
  update();
  auto buffer = std::make_shared<sf::SoundBuffer>();
  if (!buffer->loadFromFile("assets/audio/pacman-eatghost.wav"))
    throw(std::invalid_argument("Invalid sound file"));
  auto sound = std::make_shared<sf::Sound>(*buffer);
  auto sound_struct = std::make_shared<Sound>(buffer, sound);
  eatghost_ = sound_struct;
  sound->setVolume(Config::Sound::VOLUME);
  sound->play();
}

void SoundPlayer::shutDown() {
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

void SoundPlayer::visit(CoinEatenEvent &event) {
  playInterruptable("assets/audio/pacman-munch.wav");
}

void SoundPlayer::visit(FruitEatenEvent &event) {
  play("assets/audio/pacman-eatfruit.wav");
}

void SoundPlayer::visit(GhostEatenEvent &event) {
  playEatghost();
}

void SoundPlayer::visit(FrightenGhostsEvent &event) {
}

void SoundPlayer::visit(PacmanDiesEvent &event) {
  play("assets/audio/pacman-death.wav");
}

void SoundPlayer::visit(NewLevelEvent &event) {
  play("assets/audio/beginning.wav");
}
