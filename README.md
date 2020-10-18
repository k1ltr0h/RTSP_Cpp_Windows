## RTSP LIVE CAMERA C++ on Windows

* Opencv-4.4.0
* MinGW

### Compilation and execution

`g++ cam_2.cpp -o video -L "D:\opencv-4.4.0\build\lib" -I "D:\opencv-4.4.0\build\include" -lopencv_highgui440 -lopencv_imgcodecs440 -lopencv_core440 -lopencv_videoio440`

`rtsp.exe`

### Details

* I used `env.h` for confidential global variables