#include "ReconnectButton.h"

ReconnectButton::ReconnectButton(cv::Mat img_, cv::Point center_, int radius, cv::Scalar on_Color_, 
cv::Scalar off_Color_, cv::VideoCapture &cap_, char* data_):
Button(img_, center_, radius, on_Color_, off_Color_){
    render();
    
}

void ReconnectButton::render(){
    cv::Mat img = getImg();
    cv::putText(img, "Reset: ", cv::Point(this->getCenter().x - 80, this->getCenter().y),
    cv::FONT_HERSHEY_TRIPLEX, 0.6, CV_RGB(255, 255, 0), 1);
    Button::render();
}

void ReconnectButton::pressed(int x, int y){
    int rec_x = this->getCenter().x;
    int rec_y = this->getCenter().y;
    int rad = this->getRadius();
    if(x >= rec_x - rad && x<= rec_x + rad && y >= rec_y - rad && y <= rec_y + rad){
        this->reconnect();
    }
}

void ReconnectButton::reconnect(){
    Sleep(10);
    changeState();
    cap.release();
    //printf("hello\n");
    //cap = cv::VideoCapture();
    //cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
    //cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    //cap.set(cv::CAP_PROP_CODEC_PIXEL_FORMAT, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    //cap.open(data, cv::CAP_FFMPEG);
    //Sleep(1000);
    //changeState();
}
