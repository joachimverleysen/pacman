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

  /// Cleans up sounds
  void update();

  /// Plays a sound
  void play(const char* file);;

  /// Plays a sound that will be interrupted by the next sound
  void playInterruptable(const char* file);;

  /// Plays the eathost sound
  void playEatghost();

  /// Properly handles destruction
  void shutDown();

  /// Visits an event
  void visit(CoinEatenEvent &event) override;;

  void visit(FruitEatenEvent &event) override;

  void visit(GhostEatenEvent &event) override;

  void visit(FrightenGhostsEvent &event) override;

  void visit(PacmanDiesEvent &event) override;

  void visit(NewLevelEvent &event) override;
};



#endif //PACMAN_SOUNDPLAYER_H
