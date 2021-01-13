#include <iostream>
#include <opencv2/opencv.hpp>

void displayImage(cv::Mat& image) {
    system("cls");
    cv::namedWindow("Image Window", cv::WINDOW_AUTOSIZE);

    cv::imshow("Image Window", image);
    cv::waitKey(0);
    cv::destroyWindow("Image Window");
    
}

void RotateImage(std::string& str) {
    cv::Mat image = cv::imread(str, cv::IMREAD_UNCHANGED);
    std::cout << "Enter angle : ";
    double angle;           std::cin >> angle;

    // get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((image.cols - 1.0) / 2.0, (image.rows - 1.0) / 2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);

    // determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), image.size(), angle).boundingRect2f();

    // adjust transformation matrix
    rot.at<double>(0, 2) += bbox.width / 2.0 - image.cols / 2.0;
    rot.at<double>(1, 2) += bbox.height / 2.0 - image.rows / 2.0;

    cv::Mat dst;
    cv::warpAffine(image, dst, rot, bbox.size());
    
    cv::imwrite("rotatedSample.png", dst);

    displayImage(dst);

}

void LoadImage(std::string &str) {
    cv::Mat image = cv::imread(str, cv::IMREAD_UNCHANGED);
    displayImage(image);

    std::cout << std::endl << " Press 1 to rotate Image : ";
    int x;      std::cin >> x;
    
    if (x == 1) {
        RotateImage(str);
    }
}

int main() {
    system("cls");
    std::cout << std::endl << "----- Welcome to Image Rotator ------";
    
    std::string str;        std::cout << std::endl;
    std::cout << std::endl << "Enter name of image with extension : ";
    std::cin >> str;

    LoadImage(str);

    return 0;
}
