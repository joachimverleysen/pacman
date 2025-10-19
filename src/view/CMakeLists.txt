add_library(view
				Game.cpp
				EntityView.cpp
				DrawableInterface.h
				SpriteDrawable.cpp
				ShapeDrawable.h
				EntityFactory.cpp
        TextureParser.cpp
				Visuals.cpp
				Renderer.cpp
				TextureManager.h
)
target_link_libraries(view PRIVATE logic sfml-graphics sfml-window sfml-system)
