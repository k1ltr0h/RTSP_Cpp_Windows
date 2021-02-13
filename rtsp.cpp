#include "opencv2\opencv.hpp" 
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <thread>
#include <queue>
#include "env.h"
#define WIDTH 1024
#define HEIGHT 600

using namespace cv;
using namespace std;

// Grabar video (Detener o Comenzar)
void pressRecord(int state, void* var);
// Buscar video en directorio y guardarlo en grabaciones(sobreescribir archivo en grabaciones).
void mvVideo();
void displayAndRec(Mat* frame);
void receive(Mat* frame);

int value = 0;
enum recording {NO, YES};
//--- INITIALIZE VIDEOCAPTURE
VideoCapture cap;
VideoWriter video;
std::queue<Mat> frames;

bool keepRecording = false;

int main(int, char**){
    mvVideo();
    //Create window
    namedWindow("Live", WINDOW_NORMAL);
    resizeWindow("Live", WIDTH, HEIGHT);
    createTrackbar( "Grabar", "Live", &value, 1, pressRecord, &keepRecording);
    cap.set(CAP_PROP_BUFFERSIZE, 3);
    //cap.set(CAP_PROP_FPS, 10);
    //createButton("Grabar",record,NULL,QT_CHECKBOX,0);
    // Set OPENCV environment RTSP UDP
    _putenv_s("OPENCV_FFMPEG_CAPTURE_OPTIONS", "rtsp_transport;udp");
    Mat frame;

    // Define the codec and create VideoWriter object.The output is stored in 'video.avi' file.
	// Define the fps to be equal to 10. Also frame size is passed.
	//VideoWriter video;//("video.avi", VideoWriter::fourcc('M','J','P','G'),10, Size(WIDTH, HEIGHT));

    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    
    //int deviceID = 0;             // 0 = open default camera
    //int apiID = cv::CAP_ANY;      // 0 = autodetect default API

    // open selected camera using selected API
    //"rtsp://user:pass@ip:port"

    //int ex = static_cast<int>(video.get(CAP_PROP_FOURCC));
    //--- GRAB AND WRITE LOOP
    printf("Start grabbing\nPress any key to terminate\n");
    //cap.read(frame);
    //printf("%d-%d\n", cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
    thread read(receive, &frame);
    thread disp(displayAndRec, &frame);
    //thread recVideo(rec, &frame);
    read.detach();
    disp.detach();
    //recVideo.detach();

    while(true){

        // show live and wait for a key with timeout long enough to show images
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    // When everything done, release the video capture and write object
    //Kill threads
    disp.~thread();
    read.~thread();

	cap.release();
	video.release();
    destroyAllWindows();
    
    return 0;
}
void receive(Mat* frame){
    cap.open(rtsp.c_str(), cv::CAP_FFMPEG);
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        printf("Press enter to exit");
        scanf("Press Enter", NULL);
        return;
    }
    while(true){
        cap.read(*frame);
        if (frame->empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            return;
        }
        frames.push(*frame);
    }
}

void displayAndRec(Mat* frame){
    Mat tmp;
    while(true){
        if(!frames.empty()){
            *frame = frames.front();
            frames.pop();
            // Write the frame into the file 'video.avi'
            if(keepRecording){
                resize(*frame, tmp, Size(WIDTH, HEIGHT));
                video.write(tmp);
            }
            imshow("Live", *frame);
        }
    }
}

void pressRecord(int state, void* var){
    bool *rec = (bool*)var;
    if(state == NO){
        printf("Stop recording");
        *rec = false;
        video.release();
    }
    else{
        printf("Start recording");
        video.open("video.avi",cv::CAP_FFMPEG, VideoWriter::fourcc('M','J','P','G'), 15.0, 
        Size(WIDTH, HEIGHT), true);
        //Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT)), true);

        if(!video.isOpened()){
            printf("No se ha podido grabar :c\n");
        }
        *rec = true;
    }
}

void mvVideo(){
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d){
        while ((dir = readdir(d)) != NULL){
            if(dir->d_name[6] == 'a' && dir->d_name[7] == 'v' && dir->d_name[8] == 'i'){
                system("move video.avi ./grabaciones/");
            }
        }
        closedir(d);
    }
}