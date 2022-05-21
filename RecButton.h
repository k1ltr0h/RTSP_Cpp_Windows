#include "Button.h"

class RecButton : public Button{
public:
    RecButton(cv::Mat &img_, cv::Point center_, int radius, cv::Scalar on_Color_, cv::Scalar off_Color_, 
    cv::VideoWriter* video_);
    ~RecButton();
    void render();
    void pressed(int x, int y);
    void record(cv::VideoWriter* video_);
    cv::VideoWriter* getVideoWritter();
private:
    cv::VideoWriter* video;
};