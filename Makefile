
GPP=g++ -Wall -o video
CPP=rtsp.cpp Button.cpp RecButton.cpp ReconnectButton.cpp
LIBS=-L "C:\opencv455\install\x64\mingw\lib"
INCLUDE=-I "C:\opencv455\install\include"\
	-lopencv_highgui455 -lopencv_imgcodecs455 -lopencv_core455 -lopencv_videoio455\
	-lopencv_imgproc455
ICON=icon.res
MWIN=-mwindows

all:
	$(GPP) $(CPP) $(LIBS) $(INCLUDE) $(ICON) $(MWIN)
test:
	$(GPP) $(CPP) $(LIBS) $(INCLUDE) $(ICON)