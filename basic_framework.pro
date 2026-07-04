QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    entry_window.cpp \
    explorer_map_widget.cpp \
    explorer_site_pin.cpp \
    finish_window.cpp \
    wake_window.cpp \
    ending_window.cpp \
    story_event_widget.cpp \
    game_answers.cpp \
    dialogue_text.cpp \
    game_progress.cpp \
    intro_window.cpp \
    pku_explorer_window.cpp \
    site_answer_book.cpp \
    site_window.cpp

HEADERS += \
    entry_window.h \
    explorer_map_widget.h \
    explorer_window_layout.h \
    explorer_site_pin.h \
    finish_window.h \
    wake_window.h \
    ending_window.h \
    story_event_widget.h \
    dialogue_text.h \
    game_answers.h \
    game_progress.h \
    intro_window.h \
    pku_explorer_window.h \
    site_answer_book.h \
    site_dialogues.h \
    site_graph.h \
    site_state.h \
    site_window.h

FORMS += \
    entry_window.ui \
    finish_window.ui \
    wake_window.ui \
    ending_window.ui \
    intro_window.ui \
    pku_explorer_window.ui \
    site_window.ui

!exists($$PWD/images/entry.png):!exists($$PWD/images/entry_bg.png) {
    error("缺少资源文件: images/entry.png 或 entry_bg.png — 请将入场背景放入 images 文件夹")
}

!exists($$PWD/images/campus_map_fantasy_named_v2.png) {
    error("缺少资源文件: $$PWD/images/campus_map_fantasy_named_v2.png — 请将 v2 地名地图放入 images（保留其它地图文件勿覆盖）")
}

!exists($$PWD/images/bar_background_1.png):!exists($$PWD/images/bar_background_1.jpg) {
    error("缺少场景图: images/bar_background_1.png 或 bar_background_1.jpg（酒馆老板）")
}

!exists($$PWD/images/bar_background_2.png):!exists($$PWD/images/bar_background_2.jpg) {
    error("缺少场景图: images/bar_background_2.png 或 bar_background_2.jpg（酒馆旅人）")
}

!exists($$PWD/images/classroom_background_1.png) {
    error("缺少场景图: images/classroom_background_1.png（咒术大楼·小魔女出现前）")
}

!exists($$PWD/images/classroom_background_2.png) {
    error("缺少场景图: images/classroom_background_2.png（咒术大楼·小魔女出现后）")
}

!exists($$PWD/images/classroom_background_3.png) {
    error("缺少场景图: images/classroom_background_3.png（咒术大楼·走出教室）")
}

!exists($$PWD/images/lake_background_1.png) {
    error("缺少场景图: images/lake_background_1.png（镜湖·登舫前）")
}

!exists($$PWD/images/lake_background_2.png) {
    error("缺少场景图: images/lake_background_2.png（镜湖·登上石舫后）")
}

!exists($$PWD/images/lake_background_3.png) {
    error("缺少场景图: images/lake_background_3.png（镜湖·石舫唤醒后）")
}

!exists($$PWD/images/tower_background_1.png) {
    error("缺少场景图: images/tower_background_1.png（奥术尖塔·远观）")
}

!exists($$PWD/images/tower_background_2.png) {
    error("缺少场景图: images/tower_background_2.png（奥术尖塔·近前）")
}

!exists($$PWD/images/tower_background_3.png) {
    error("缺少场景图: images/tower_background_3.png（奥术尖塔·门前）")
}

!exists($$PWD/images/tower_in.png) {
    error("缺少场景图: images/tower_in.png（奥术尖塔·塔内）")
}

!exists($$PWD/images/tower_on.png) {
    error("缺少场景图: images/tower_on.png（奥术尖塔·塔顶）")
}

!exists($$PWD/images/tower_leave.png) {
    error("缺少场景图: images/tower_leave.png（奥术尖塔·离去回望）")
}

!exists($$PWD/images/witch.png) {
    error("缺少立绘: images/witch.png（小魔女）")
}

!exists($$PWD/images/bar_publican.png) {
    error("缺少立绘: images/bar_publican.png（老板老金）")
}

!exists($$PWD/images/bar_stranger.png) {
    error("缺少立绘: images/bar_stranger.png（旅人）")
}

!exists($$PWD/images/theater_background_1.png) {
    error("缺少场景图: images/theater_background_1.png（吟游剧场·到达）")
}

!exists($$PWD/images/theater_background_2.png) {
    error("缺少场景图: images/theater_background_2.png（吟游剧场·工作人员）")
}

!exists($$PWD/images/theater_background_3.png) {
    error("缺少场景图: images/theater_background_3.png（吟游剧场·聊壁画）")
}

!exists($$PWD/images/theater_paint_sleeping.png) {
    error("缺少场景图: images/theater_paint_sleeping.png（吟游剧场·壁画沉睡）")
}

!exists($$PWD/images/theater_paint_awaken.png) {
    error("缺少场景图: images/theater_paint_awaken.png（吟游剧场·壁画唤醒）")
}

!exists($$PWD/images/theater_staff.png) {
    error("缺少立绘: images/theater_staff.png（吟游剧场·工作人员）")
}

!exists($$PWD/images/library_assistance.png) {
    error("缺少立绘: images/library_assistance.png（禁书收藏馆·管理员）")
}

!exists($$PWD/images/gate_background_1.png) {
    error("缺少场景图: images/gate_background_1.png（天门·抵达）")
}

!exists($$PWD/images/gate_background_2.png) {
    error("缺少场景图: images/gate_background_2.png（天门·抉择前）")
}

!exists($$PWD/images/gate_background_3.png) {
    error("缺少场景图: images/gate_background_3.png（天门·往外走）")
}

!exists($$PWD/images/gate_background_4.png) {
    error("缺少场景图: images/gate_background_4.png（天门·再走走看）")
}

!exists($$PWD/images/yannan_background_1.png) {
    error("缺少场景图: images/yannan_background_1.png（旧日之境·入园）")
}

!exists($$PWD/images/yannan_background_2.png) {
    error("缺少场景图: images/yannan_background_2.png（旧日之境·深院）")
}

!exists($$PWD/images/yannan_background_3.png) {
    error("缺少场景图: images/yannan_background_3.png（旧日之境·小径）")
}

!exists($$PWD/images/yannan_house.png) {
    error("缺少场景图: images/yannan_house.png（旧日之境·无门小屋）")
}

!exists($$PWD/images/yannan_door.png) {
    error("缺少场景图: images/yannan_door.png（旧日之境·店门浮现）")
}

!exists($$PWD/images/yannan_in.png) {
    error("缺少场景图: images/yannan_in.png（旧日之境·店内）")
}

!exists($$PWD/images/library_background_1.png) {
    error("缺少场景图: images/library_background_1.png（禁书收藏馆·大厅）")
}

!exists($$PWD/images/library_background_2.png) {
    error("缺少场景图: images/library_background_2.png（禁书收藏馆·展廊）")
}

!exists($$PWD/images/library_background_3.png) {
    error("缺少场景图: images/library_background_3.png（禁书收藏馆·古分馆）")
}

!exists($$PWD/images/library_shelf.png) {
    error("缺少场景图: images/library_shelf.png（禁书收藏馆·书架）")
}

!exists($$PWD/images/library_book.png) {
    error("缺少场景图: images/library_book.png（禁书收藏馆·原神之力）")
}

!exists($$PWD/images/island.png) {
    error("缺少场景图: images/island.png（湖心岛·终章）")
}

!exists($$PWD/images/garden_entry.png) {
    error("缺少场景图: images/garden_entry.png（遗迹花园·入园）")
}

!exists($$PWD/images/garden_light_1.png) {
    error("缺少场景图: images/garden_light_1.png（遗迹花园·分岔·光侧）")
}

!exists($$PWD/images/garden_light_2.png) {
    error("缺少场景图: images/garden_light_2.png（遗迹花园·光径）")
}

!exists($$PWD/images/garden_shadow_1.png) {
    error("缺少场景图: images/garden_shadow_1.png（遗迹花园·分岔·影侧）")
}

!exists($$PWD/images/garden_shadow_2.png) {
    error("缺少场景图: images/garden_shadow_2.png（遗迹花园·影径）")
}

!exists($$PWD/images/garden_pool.png) {
    error("缺少场景图: images/garden_pool.png（遗迹花园·园心池）")
}

!exists($$PWD/images/garden_leave.png) {
    error("缺少场景图: images/garden_leave.png（遗迹花园·告别）")
}

RESOURCES += \
    $$PWD/resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
