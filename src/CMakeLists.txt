
set(SRC main main.cpp
        model/World.cpp
        model/entity/Player.cpp
        view/Game.cpp
        view/EntityView.cpp
        controller/GameController.cpp
        model/observer/Observer.cpp
        utils/JSONParser.cpp
        model/entity/EntityFactory.cpp
        utils/Utils.cpp
        view/TextureParser.cpp
        model/entity/Entity.cpp
        model/Stopwatch.cpp
        view/Visuals.cpp
        model/CollisionHandler.cpp
        model/Random.cpp
		view/Renderer.cpp
		view/EntityViewFactory.cpp
)

add_executable(main ${SRC})
