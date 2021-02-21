#include <stdio.h>
#include <windows.h>
#include "opencv2\opencv.hpp" 
#include "env.h"

class Button{
public:
    Button(cv::Mat img_, cv::Point center_, int radius, cv::Scalar on_Color_, cv::Scalar off_Color_);
    virtual ~Button();
    void changeState();
    void render();
    virtual void pressed(int x, int y);
    cv::Point getCenter();
    int getRadius();
    bool getState();
    enum pressed{OFF, ON};
private:
    cv::Mat img;
    cv::Scalar on_Color;
    cv::Scalar off_Color;
    cv::Scalar actual_Color;
    cv::Point center;
    int radius;
    bool state;
};