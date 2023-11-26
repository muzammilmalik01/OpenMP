#include <opencv2/opencv.hpp>
#include <cmath>
#include <chrono> 
#include <omp.h>

using namespace std::chrono;
using namespace std;
using namespace cv;

void applyTwistTransformation(const Mat& inputImage, Mat& twistedImage, double theta) {
    
    // set the center of the image
    double cx = inputImage.cols / 2.0;
    double cy = inputImage.rows / 2.0;

    // copy the image 
    twistedImage = inputImage.clone();

    #pragma omp parallel for collapse(2) //pragma construct for 2 for loops which will be divided into n number of cores provided by the user.
    for (int y = 0; y < inputImage.rows; ++y) {
        for (int x = 0; x < inputImage.cols; ++x) {
            double x0 = (x - cx) * cos(theta) + (y - cy) * sin(theta) + cx;
            double y0 = -(y - cy) * sin(theta) + (y - cy) * cos(theta) + cy;

            // check if the transformed coordinates are within the image bounds
            if (x0 >= 0 && x0 < inputImage.cols && y0 >= 0 && y0 < inputImage.rows) {
                twistedImage.at<Vec3b>(y, x) = inputImage.at<Vec3b>(static_cast<int>(y0), static_cast<int>(x0));
            }
        }
    }
}

int main() {
    // Read the input image
    Mat inputImage = imread("image.jpg");

    if (inputImage.empty()) {
        cout << "Error: Could not read the image." << endl;
        return -1;
    }

    Mat twistedImage;

    int cores = 1;
    cout << "\nPlease enter the number of cores to use:";
    cin >> cores;


    omp_set_num_threads(cores); // set total number of cores to use.
    auto start = high_resolution_clock::now(); // note timestap for starting time.

    applyTwistTransformation(inputImage, twistedImage, 45); // apply the image warp.

    auto stop = high_resolution_clock::now(); // // note timestap for ending time.
    auto duration = duration_cast<milliseconds>(stop - start).count(); // calculate the total execution time.

    waitKey(0); // wait for user to press a key to quit
    cout << "\nTotal cores used: " << cores;
    cout << "\nDuration: " << duration << " ms";
    string twisted_image_path = "twisted_image.jpg";
    imwrite(twisted_image_path, twistedImage); //saving the twisted image
    cout << "\nThe twisted image has been saved." << endl;

    return 0;
}