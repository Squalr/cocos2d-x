
if(WINDOWS AND BUILD_SHARED_LIBS)
    add_definitions(-D_USEGUIDLL)
endif()

set(COCOS_UI_HEADER
    ${COCOS_UI_SPECIFIC_HEADER}
    ui/UIHelper.h
    ui/UIRichText.h
    ui/UITextField.h
    ui/UIWidget.h
    )

set(COCOS_UI_SRC
    ${COCOS_UI_SPECIFIC_SRC}
    ui/UIHelper.cpp
    ui/UIRichText.cpp
    ui/UITextField.cpp
    ui/UIWidget.cpp
    )
