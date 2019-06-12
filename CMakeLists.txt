cmake_minimum_required (VERSION 3.10)

project (Metronome)

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (Qt5 COMPONENTS Core Quick REQUIRED)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library (COCOA_LIBRARY      Cocoa           REQUIRED)
    find_library (IOKIT_LIBRARY      IOKit           REQUIRED)
    find_library (ACCEL_LIBRARY      Accelerate      REQUIRED)
    find_library (COREAUDIO_LIBRARY  CoreAudio       REQUIRED)
    find_library (COREMIDI_LIBRARY   CoreMIDI        REQUIRED)
    find_library (AUDIOTB_LIBRARY    AudioToolbox    REQUIRED)

    set (JUCE_SOURCES
        "JuceLibraryCode/include_juce_audio_basics.mm"
        "JuceLibraryCode/include_juce_audio_devices.mm"
        "JuceLibraryCode/include_juce_core.mm"
        "JuceLibraryCode/include_juce_events.mm"
    )

    add_definitions(-DMACOSX_DEPLOYMENT_TARGET=10.10)
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set (JUCE_SOURCES
        "JuceLibraryCode/include_juce_audio_basics.cpp"
        "JuceLibraryCode/include_juce_audio_devices.cpp"
        "JuceLibraryCode/include_juce_core.cpp"
        "JuceLibraryCode/include_juce_events.cpp"
    )

    add_compile_definitions (
        JUCE_ALSA=1
        JUCE_INCLUDE_ZLIB_CODE=1
    )
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")


set (SOURCES
        "r8brain-free-src/pffft.cpp"
        "r8brain-free-src/r8bbase.cpp"
        "ClickSample.cpp"
        "Metronome.cpp"
        "Main.cpp"
        "Qml/qml.qrc"
)
set (HEADERS
        "r8brain-free-src/CDSPBlockConvolver.h"
        "r8brain-free-src/CDSPFIRFilter.h"
        "r8brain-free-src/CDSPFracInterpolator.h"
        "r8brain-free-src/CDSPHBDownsampler.h"
        "r8brain-free-src/CDSPHBUpsampler.h"
        "r8brain-free-src/CDSPProcessor.h"
        "r8brain-free-src/CDSPRealFFT.h"
        "r8brain-free-src/CDSPResampler.h"
        "r8brain-free-src/CDSPSincFilterGen.h"
        "r8brain-free-src/fft4g.h"
        "r8brain-free-src/pffft.h"
        "r8brain-free-src/r8bbase.h"
        "r8brain-free-src/r8bconf.h"
        "r8brain-free-src/r8butil.h"
        "JuceLibraryCode/AppConfig.h"
        "JuceLibraryCode/JuceHeader.h"
        "JUCE/juce_audio_basics/juce_audio_basics.h"
        "JUCE/juce_audio_devices/juce_audio_devices.h"
        "JUCE/juce_core/juce_core.h"
        "JUCE/juce_events/juce_events.h"
        "JUCE/juce_data_structures/juce_data_structures.h"
        "Metronome.h"
)


add_executable (${PROJECT_NAME} MACOSX_BUNDLE ${JUCE_SOURCES} ${SOURCES})

target_include_directories (${PROJECT_NAME} PRIVATE
    "JuceLibraryCode"
    "JUCE"
)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries (${PROJECT_NAME} PRIVATE
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${ACCEL_LIBRARY}
        ${COREAUDIO_LIBRARY}
        ${COREMIDI_LIBRARY}
        ${AUDIOTB_LIBRARY}
        Qt5::Core Qt5::Quick
    )
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries (${PROJECT_NAME}
        rt dl pthread asound
        Qt5::Core Qt5::Quick
    )
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
