
set(COCOS_AUDIO_SRC
    audio/AudioEngine.cpp
    )

if(WINDOWS)

    set(COCOS_AUDIO_PLATFORM_HEADER
        audio/win32/AudioDecoderManager.h
        audio/win32/AudioDecoder.h
        audio/win32/AudioPlayer.h
        audio/win32/AudioMacros.h
        audio/win32/AudioEngine-win32.h
        audio/win32/AudioDecoderMp3.h
        audio/win32/AudioCache.h
        )

    set(COCOS_AUDIO_PLATFORM_SRC
        audio/win32/AudioEngine-win32.cpp
        audio/win32/AudioCache.cpp
        audio/win32/AudioPlayer.cpp
        audio/win32/AudioDecoder.cpp
        audio/win32/AudioDecoderManager.cpp
        audio/win32/AudioDecoderMp3.cpp
        )

elseif(LINUX)
    set(COCOS_AUDIO_PLATFORM_HEADER
        audio/linux/AudioEngine-linux.h
        )

    set(COCOS_AUDIO_PLATFORM_SRC
        audio/linux/AudioEngine-linux.h
        audio/linux/AudioEngine-linux.cpp
        audio/linux/AudioCache.cpp
        audio/linux/AudioPlayer.cpp
        audio/linux/AudioDecoder.cpp
        audio/linux/AudioDecoderManager.cpp
        audio/linux/AudioDecoderMp3.cpp
        )

elseif(APPLE)
    # common
    set(COCOS_AUDIO_PLATFORM_HEADER
        audio/mac/AudioDecoder.h
        audio/mac/AudioPlayer.h
        audio/mac/AudioMacros.h
        audio/mac/AudioCache.h
        audio/mac/AudioEngine-inl.h
        )
    set(COCOS_AUDIO_PLATFORM_SRC
        audio/mac/AudioCache.mm
        audio/mac/AudioDecoder.mm
        audio/mac/AudioEngine-inl.mm
        audio/mac/AudioPlayer.mm
        )

    set_source_files_properties(
            ${COCOS_AUDIO_PLATFORM_SRC_C}
            PROPERTIES LANGUAGE C
    )
endif()

set(COCOS_AUDIO_HEADER ${COCOS_AUDIO_PLATFORM_HEADER})
list(APPEND COCOS_AUDIO_SRC ${COCOS_AUDIO_PLATFORM_SRC})
