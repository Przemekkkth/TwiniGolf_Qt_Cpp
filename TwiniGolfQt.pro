greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    src/entity/ball.cpp \
    src/entity/entity.cpp \
    src/entity/hole.cpp \
    src/entity/point.cpp \
    src/entity/power_bar.cpp \
    src/entity/tile.cpp \
    src/scene/game_scene.cpp \
    src/main.cpp \
    src/scene/level_scene.cpp \
    src/scene/menu_scene.cpp \
    src/scene/title_scene.cpp \
    src/scene/win_scene.cpp \
    src/utils/font_manager.cpp \
    src/utils/pixmap_manager.cpp \
    src/view.cpp \
    src/world.cpp

HEADERS += \
    src/entity/ball.h \
    src/entity/entity.h \
    src/entity/hole.h \
    src/entity/point.h \
    src/entity/power_bar.h \
    src/entity/tile.h \
    src/scene/game_scene.h \
    src/scene/level_scene.h \
    src/scene/menu_scene.h \
    src/scene/title_scene.h \
    src/scene/win_scene.h \
    src/utils/font_manager.h \
    src/utils/pixmap_manager.h \
    src/utils/resource_holder.h \
    src/utils/utils.h \
    src/view.h \
    src/world.h

RESOURCES += \
    resource.qrc
