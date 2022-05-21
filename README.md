## RTSP LIVE CAMERA C++ on Windows

* Opencv-4.5.5
* MinGW

### Compilation and execution

`g++ rtsp.cpp Button.cpp RecButton.cpp -Wall -o video -L "C:\opencv455\install\x64\mingw\lib" -I "C:\opencv455\install\include" -lopencv_highgui455 -lopencv_imgcodecs455 -lopencv_core455 -lopencv_videoio455 -lopencv_imgproc455 icon.res -mwindows`

`video.exe`

### Details

* I used `camera_credentials.txt` for confidential data.
* I used `env.h` for important global variables.