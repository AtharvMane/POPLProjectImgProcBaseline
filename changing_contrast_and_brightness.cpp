#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
using namespace cv;
int main( int argc, char** argv )
{

    Mat image = imread("download.jpeg");
    if( image.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }

/**
Now, since we will make some transformations to this image, we need a new Mat object to store it. Also, we want this to have the following features:
Initial pixel values equal to zero
Same size and type as the original image
*/

    Mat new_image = Mat::zeros( image.size(), image.type() ); //We observe that cv::Mat::zeros returns a Matlab-style zero initializer based on image.size() and image.type()

//We ask now the values of α and β to be entered by the user

    double alpha = 1.0; /*< Simple contrast control */
    int beta = 0;       /*< Simple brightness control */
    cout << " Basic Linear Transforms " << endl;
    cout << "-------------------------" << endl;
    cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
    cout << "* Enter the beta value [0-100]: ";    cin >> beta;

/**
Now, to perform the operation g(i,j)=α⋅f(i,j)+β we will access to each pixel in image.
Since we are operating with BGR images, we will have three values per pixel (B, G and R), so we will also access them separately.
Here is the piece of code:
*/

    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < image.channels(); c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }

/**
To access each pixel in the images we are using this syntax: image.at<Vec3b>(y,x)[c] where y is the row, x is the column and c is B, G or R (0, 1 or 2).
Since the operation α⋅p(i,j)+β can give values out of range or not integers (if α is float), we use cv::saturate_cast to make sure the values are valid.
Finally, we create windows and show the images, the usual way.
*/
    imwrite("results/contrast_and_brightness/contrast_and_brightness.jpg",new_image);

    imshow("Original Image", image);
    imshow("New Image", new_image);
    waitKey();
    return 0;
}