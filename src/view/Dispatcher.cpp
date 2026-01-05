#include "Dispatcher.h"
#include "../logic/utils/Event.h"
#include "../logic/Score.h"
#include "audio/SoundPlayer.h"

void Dispatcher::handle(FruitEatenEvent &event) {
  event.accept(*SoundPlayer::getInstance());
  event.accept(*Score::getInstance());
}

void Dispatcher::handle(GhostEatenEvent &event) {
  event.accept(*SoundPlayer::getInstance());
  event.accept(*Score::getInstance());
}

void Dispatcher::handle(CoinEatenEvent &event) {
  event.accept(*SoundPlayer::getInstance());
  event.accept(*Score::getInstance());
}

void Dispatcher::handle(FrightenGhostsEvent &event) {
  event.accept(*SoundPlayer::getInstance());
}

void Dispatcher::handle(PacmanDiesEvent &event) {
 event.accept(*SoundPlayer::getInstance());
}

void Dispatcher::handle(NewLevelEvent &event) {
  event.accept(*SoundPlayer::getInstance());
}
