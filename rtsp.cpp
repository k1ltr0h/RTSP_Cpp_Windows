#include "opencv2\opencv.hpp" 
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <windows.h>
#include <thread>
#include <queue>
#include <mutex>          // std::mutex
#include "env.h"
#define WIDTH 1024
#define HEIGHT 600
#define REC_WIDTH 640
#define REC_HEIGHT 480
#define MAX_LENGHT 10

// Grabar video (Detener o Comenzar)
void pressRecord(int state, void* var);
// Buscar video en directorio y guardarlo en grabaciones(sobreescribir archivo en grabaciones).
void mvVideo();
void displayAndRec(cv::Mat* frame);
void receive(cv::Mat* frame);

int value = 0;
enum recording {NO, YES};
//--- INITIALIZE VIDEOCAPTURE
cv::VideoCapture cap;
cv::VideoWriter video;
std::queue<cv::Mat> frames;
std::mutex mtx;           // mutex for critical section

bool keepRecording = false;

int main(int, char**){
    mvVideo();
    //Create window
    cv::namedWindow("Live", cv::WINDOW_NORMAL);
    cv::resizeWindow("Live", WIDTH, HEIGHT);
    cv::createTrackbar( "Grabar", "Live", &value, 1, pressRecord, &keepRecording);
    cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H', '2', '6', '4'));
    cap.set(cv::CAP_PROP_CODEC_PIXEL_FORMAT, cv::VideoWriter::fourcc('H', '2', '6', '4'));
    //createButton("b",NULL); //Need QT
    //cap.setExceptionMode(true);
    //cap.set(CAP_PROP_FPS, 15);
    //createButton("Grabar",record,NULL,QT_CHECKBOX,0);// Need QT
    // Set OPENCV environment RTSP UDP
    _putenv_s("OPENCV_FFMPEG_CAPTURE_OPTIONS", "rtsp_transport;udp");
    cv::Mat frame;

    if(frames.empty()){
        printf("\nqueue empty\n");
    }
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
    printf("Start grabbing\nPress ESC key or X button to terminate\n");
    //cap.read(frame);
    //printf("%d-%d\n", cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
    std::thread read(receive, &frame);
    std::thread disp(displayAndRec, &frame);
    //thread recVideo(rec, &frame);
    read.detach();
    disp.detach();
    //recVideo.detach();

    while(true){
        //Cierra la ventana al apretar la X de la esquina superior derecha
        if(!cv::getWindowProperty("Live",cv::WND_PROP_VISIBLE)){
            break;
        }

        // show live and wait for a key with timeout long enough to show images
        if(cv::waitKey(0) == 27){
            break;
        }
        //printf("\nmain\n");
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    // When everything done, release the video capture and write object
    //Kill threads
    disp.~thread();
    read.~thread();

	cap.release();
	video.release();
    cv::destroyAllWindows();
    
    return 0;
}

void receive(cv::Mat* frame){
    cap.open(rtsp.c_str(), cv::CAP_FFMPEG);
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        printf("Press enter to exit");
        scanf("Press Enter", NULL);
        return;
    }
    while(true){
        try{
            mtx.lock();
            cap.read(*frame);
            //printf("\ntotal: %d\n", frame->total());
            resize(*frame, *frame, cv::Size(REC_WIDTH, REC_HEIGHT));
            if (frame->empty()) {
                std::cerr << "ERROR! blank frame grabbed\n";
                return;
            }
            if(frames.size() < MAX_LENGHT){
                frames.push(*frame);
                //printf("push\n");
            }
            mtx.unlock();
            //printf("\nReceive\n");
            Sleep(50);
        }

        catch(std::string str){
            printf("Ha ocurrido un error al leer el frame");
        }
    }
}

void displayAndRec(cv::Mat* frame){
    cv::Mat tmp, bar;
    bar = cv::Mat::zeros(cv::Size(REC_WIDTH, 100), CV_8UC3);
    while(true){
        //printf("%d", frames.empty());
        try{
            if(!frames.empty()){
                //printf("display");
                mtx.lock();
                tmp = frames.front();
                frames.pop();
                //hconcat(a, b, dst) // horizontal
                //vconcat(bar, tmp, tmp); // vertical
                // Write the frame into the file 'video.avi'
                //printf("queue size: %d\n", frames.size());
                if(keepRecording){
                    //resize(tmp, tmp, Size(WIDTH, HEIGHT));
                    video.write(tmp);
                }
                imshow("Live", tmp);
                //printf("show");
                //waitKey(500);
                mtx.unlock();
            }
            Sleep(50);
        }
        catch(std::string str){
            printf("Hubo un error al grabar o mostrar la imagen");
        }
    }
    printf("morí :c");
}

void pressRecord(int state, void* var){
    Sleep(10);
    bool *rec = (bool*)var;
    if(state == NO){
        printf("Stop recording");
        *rec = false;
        video.release();
    }
    else{
        printf("Start recording");
        video.open("video.avi",cv::CAP_FFMPEG, cv::VideoWriter::fourcc('M','J','P','G'), 10, 
        cv::Size(WIDTH, HEIGHT), true);
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