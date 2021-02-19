#include <stdio.h>
#include "opencv2\opencv.hpp" 

class Button{
public:
    Button(cv::Mat img_, cv::Point center_, int radius, cv::Scalar on_Color_, cv::Scalar off_Color_);
    ~Button();
    void changeState();
    void render();
    cv::Point getCenter();
    int getRadius();
    bool getState();
private:
    enum pressed{OFF, ON};
    cv::Mat img;
    cv::Scalar on_Color;
    cv::Scalar off_Color;
    cv::Scalar actual_Color;
    cv::Point center;
    int radius;
    bool state;
};