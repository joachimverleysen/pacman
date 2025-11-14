#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "PauseStateView.h"
#include "../../logic/PauseMenu.h"

PauseStateView::PauseStateView(std::shared_ptr<PauseMenu> state) : StateView(state) {
}
