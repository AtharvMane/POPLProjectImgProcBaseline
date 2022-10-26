//Smoothing images: this program loads an image, and applies 4 different kind of filters, and shows the filtered images. We use OpenCV
//functions such as cv::blur(), cv::GaussianBlur(), cv::medianBlur() and cv::bilateralFilter().

#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp" 
using namespace std;
using namespace cv;



int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;
Mat src; Mat dst;

char window_name[] = "Smoothing Demo";
int display_caption( const char* caption );
int display_dst( int delay );
int main( int argc, char ** argv )
{
    namedWindow( window_name, WINDOW_AUTOSIZE );
    const char* filename ="download.jpeg";
    src = imread( filename );
    if (src.empty())
    {
        printf(" Error opening image\n");
        printf(" Usage:\n %s [image_name-- default lena.jpg] \n", argv[0]);
        return EXIT_FAILURE;
    }
    if( display_caption( "Original Image" ) != 0 )
    {
        return 0;
    }
    dst = src.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
    {
        return 0;
    }
    if( display_caption( "Homogeneous Blur" ) != 0 )
    {
        return 0;
    }

//NORMALIZED BLOCK FILTER:

//The blur() function is used to perform smoothing with this filter. Arguments are the source image, destination image, and the size of the filter. The size of the filter is given as a Size object, which is a structure with two elements: width and height. The size of the filter must be odd and positive. Another argument that is used is Point, which indicates where the anchor point is located. If there is a negative value then the center of the kernel is considered as the anchor point. The default value is (-1,-1), which means that the center of the kernel is the anchor point. The function returns the destination image.

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        blur( src, dst, Size( i, i ), Point(-1,-1) );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }



    if( display_caption( "Gaussian Blur" ) != 0 )
    {
        return 0;
    }


//GAUSSIAN FILTER:

//This filter uses the function GaussianBlur(). The arguments that are used are: src(source image), dst(destination image), size(width, height), which represents the size of the kernel to be used. Width  and height have to be odd and positive numbers otherwise the size will be calculated using the σx and σy arguments. The fourth argument is the standard deviation in the X direction, which if zero in value, is calculated using kernel size. The fifth argument is the standard deviation in the Y direction, which if zero in value, is calculated using kernel size
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        GaussianBlur( src, dst, Size( i, i ), 0, 0 );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    //saving last blur
    imwrite("results/gaussian_blur.jpg",dst);



    if( display_caption( "Median Blur" ) != 0 )
    {
        return 0;
    }

//MEDIAN FILTER:
//This filter is provided by the medianBlur() function: We use three arguments: src (source image), dst (destination image), must be the same type as src, and the size of the kernel. The size of the kernel must be odd and positive. 

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        medianBlur ( src, dst, i );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }

    imwrite("results/median_blur.jpg",dst);

    if( display_caption( "Bilateral Blur" ) != 0 )
    {
        return 0;
    }


//BILATERAL FILTER:
//This filter is provided by the bilateralFilter() function. It uses four arguments: src (source image), dst (destination image), d (diameter of each pixel neighborhood), which must be positive and odd, σColor, which is the filter sigma in the color space, and represents the standard deviation in the color space, σSpace, which is the filter sigma in the coordinate space, and this represents the standard deviation in the coordinate space.

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        bilateralFilter ( src, dst, i, i*2, i/2 );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    imwrite("results/bilateral_blur.jpg",dst);



    display_caption( "Done!" );
    return 0;
}

int display_caption( const char* caption )
{
    dst = Mat::zeros( src.size(), src.type() );
    putText( dst, caption,
             Point( src.cols/4, src.rows/2),
             FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );
    return display_dst(DELAY_CAPTION);
}

int display_dst( int delay )
{
    imshow( window_name, dst );
    int c = waitKey ( delay );
    if( c >= 0 ) { return -1; }
    return 0;
}