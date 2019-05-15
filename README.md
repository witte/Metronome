# Metronome
A simple metronome made with Qt and Juce


## Dependencies
CMake: https://cmake.org/<br>
Qt:    https://www.qt.io/<br>
Juce:  https://github.com/WeAreROLI/JUCE (included)<br>

Linux only: ALSA Development headers (libasound2-dev on Ubuntu)


## Building

```
# Install ALSA dev headers (Linux only)
sudo apt install libasound2-dev

git clone https://github.com/witte/Metronome.git
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/Path/to/your/qt/installation
cmake --build .
```


## License
GPL-3.0

