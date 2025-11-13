add_library(view
				Game.cpp
        view/EntityView.cpp
        view/WallView.cpp
        view/DrawableInterface.h
        view/SpriteDrawable.cpp
        view/ShapeDrawable.cpp
				EntityFactory.cpp
        TextureParser.cpp
				Visuals.cpp
				Renderer.cpp
				TextureManager.h
		state/StateView.h
		state/StateManager.h
		state/StateManager.cpp
		state/StateView.cpp
)
target_link_libraries(view PRIVATE logic sfml-graphics sfml-window sfml-system)
