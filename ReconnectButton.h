#include "Button.h"

class ReconnectButton: public Button{
public:
    ReconnectButton(cv::Mat img_, cv::Point center_, int radius, cv::Scalar on_Color_, cv::Scalar off_Color_, 
    cv::VideoCapture &cap_, char* data_);
    void render();
    void pressed(int x_, int y_);
    void reconnect();

private:
    cv::VideoCapture cap;
    char* data;
};