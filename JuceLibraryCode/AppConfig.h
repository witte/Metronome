#pragma once

/* ==============================================================================
    In accordance with the terms of the JUCE 5 End-Use License Agreement, the
    JUCE Code in SECTION A cannot be removed, changed or otherwise rendered
    ineffective unless you have a JUCE Indie or Pro license, or are using JUCE
    under the GPL v3 license.

    End User License Agreement: www.juce.com/juce-5-licence
   ============================================================================== */

// BEGIN SECTION A
#define JUCE_DISPLAY_SPLASH_SCREEN 0
#define JUCE_REPORT_APP_USAGE 0
// END SECTION A


#define JUCE_API


#define JUCE_MODULE_AVAILABLE_juce_core             1
#define JUCE_MODULE_AVAILABLE_juce_events           1
#define JUCE_MODULE_AVAILABLE_juce_audio_basics		1
#define JUCE_MODULE_AVAILABLE_juce_audio_devices	1


#define JUCE_STANDALONE_APPLICATION                 1
#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED		1


// juce_audio_devices flags:    ============================
#define JUCE_USE_WINRT_MIDI                             0
#define JUCE_ASIO                                       0
#define JUCE_WASAPI                                     0
#define JUCE_WASAPI_EXCLUSIVE                           0
#define JUCE_DIRECTSOUND                                0
//#define JUCE_ALSA                                       1
//#define JUCE_ALSA_MIDI_NAME                             "Metronome"
#define JUCE_JACK                                       0
#define JUCE_JACK_CLIENT_NAME                           "Metronome"
#define JUCE_BELA                                       0
#define JUCE_USE_ANDROID_OBOE                           0
#define JUCE_USE_ANDROID_OPENSLES                       0
#define JUCE_DISABLE_AUDIO_MIXING_WITH_OTHER_APPS       0

// juce_core flags:     ====================================
#define DEBUG                                           0
#define JUCE_DEBUG                                      0
#define JUCE_FORCE_DEBUG                                0
#define JUCE_LOG_ASSERTIONS                             0
#define JUCE_CHECK_MEMORY_LEAKS                         0
//#define JUCE_INCLUDE_ZLIB_CODE                          1
#define JUCE_USE_CURL                                   0
#define JUCE_LOAD_CURL_SYMBOLS_LAZILY                   0
#define JUCE_CATCH_UNHANDLED_EXCEPTIONS                 0
#define JUCE_ALLOW_STATIC_NULL_VARIABLES                0
#define JUCE_STRICT_REFCOUNTEDPOINTER                   1

// juce_events flags:   ====================================
#define JUCE_EXECUTE_APP_SUSPEND_ON_IOS_BACKGROUND_TASK 0

