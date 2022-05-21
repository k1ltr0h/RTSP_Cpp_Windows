#include "RecButton.h"

RecButton::RecButton(cv::Mat &img_, cv::Point center_, int radius, 
cv::Scalar on_Color_, cv::Scalar off_Color_, cv::VideoWriter* video_):
Button(img_, center_, radius, on_Color_, off_Color_){
    video = video_;
    render();
}

RecButton::~RecButton(){

}

void RecButton::render(){
    cv::Mat img = getImg();
    cv::putText(img, "Grabar: ", cv::Point(this->getCenter().x - 100, this->getCenter().y),
    cv::FONT_HERSHEY_TRIPLEX, 0.6, CV_RGB(255, 255, 0), 1);
    Button::render();
}

void RecButton::pressed(int x, int y){
    int rec_x = this->getCenter().x;
    int rec_y = this->getCenter().y;
    int rad = this->getRadius();
    if(x >= rec_x - rad && x<= rec_x + rad && y >= rec_y - rad && y <= rec_y + rad){
        this->record(video);
    }
}

void RecButton::record(cv::VideoWriter* video){
    Sleep(10);
    if(this->getState() == ON){
        changeState();
        printf("Stop recording\n");
        video->release();
    }
    else{
        printf("Start recording\n");
        video->open("video.avi", cv::CAP_FFMPEG, cv::VideoWriter::fourcc('M','J','P','G'), 10, 
        cv::Size(REC_WIDTH, REC_HEIGHT), true);
        //Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT)), true);
        changeState();

        if(!video->isOpened()){
            printf("No se ha podido grabar :c\n");
        }
    }
}

cv::VideoWriter* RecButton::getVideoWritter(){
    return video;
}