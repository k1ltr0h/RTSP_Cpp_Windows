#include "button.h"

Button::Button(cv::Mat img_, cv::Point center_, int radius_, cv::Scalar on_Color_, cv::Scalar off_Color_){
    img = img_;
    state = OFF;
    center = center_;
    on_Color = on_Color_;
    off_Color = off_Color_;
    actual_Color = off_Color;
    radius = radius_;
    render();
    //circle(img, center, radius, off_Color, cv::FILLED, cv::LINE_AA);
}
Button::~Button(){

}
void Button::changeState(){
    if(state == OFF){
        state = ON;
        actual_Color = on_Color;
        render();
    }
    else{
        state = OFF;
        actual_Color = off_Color;
        render();
    }
}

void Button::render(){
    circle(img, center, radius, actual_Color, cv::FILLED, cv::LINE_AA);
}

cv::Point Button::getCenter(){
    return center;
}

int Button::getRadius(){
    return radius;
}

bool Button::getState(){
    return state;
}