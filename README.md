## RTSP LIVE CAMERA C++ on Windows

* Opencv-4.4.0
* MinGW

### Compilation and execution

`g++ rtsp.cpp -o video -L "C:\opencv440\install\x64\mingw\lib" -I "C:\opencv440\install\include" -lopencv_highgui440 -lopencv_imgcodecs440 -lopencv_core440 -lopencv_videoio440 icon.res -mwindows`

`video.exe`

### Details

* I used `env.h` for confidential global variables