#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
static void help(char ** argv)
{
    cout << endl
        <<  "This program demonstrated the use of the discrete Fourier transform (DFT). " << endl
        <<  "The dft of an image is taken and it's power spectrum is displayed."  << endl << endl
        <<  "Usage:"                                                                      << endl
        << argv[0] << " [image_name -- default lena.jpg]" << endl << endl;
}

/**
The Fourier Transform will decompose an image into its sinus and cosines components.
In other words, it will transform an image from its spatial domain to its frequency domain.
The idea is that any function may be approximated exactly with the sum of infinite sinus and cosines functions.
The Fourier Transform is a way how to do this. Mathematically a two dimensional images Fourier transform is:

F(k,l)=∑i=0N−1∑j=0N−1f(i,j)e−i2π(kiN+ljN)
eix=cosx+isinx
Here f is the image value in its spatial domain and F in its frequency domain.
The result of the transformation is complex numbers.
Displaying this is possible either via a real image and a complex image or via a magnitude and a phase image. However, throughout the image processing algorithms only the magnitude image is interesting as this contains all the information we need about the images geometric structure. Nevertheless, if you intend to make some modifications of the image in these forms and then you need to retransform it you'll need to preserve both of these.

In this sample I'll show how to calculate and show the magnitude image of a Fourier Transform.
In case of digital images are discrete. This means they may take up a value from a given domain value.
For example in a basic gray scale image values usually are between zero and 255.
Therefore the Fourier Transform too needs to be of a discrete type resulting in a Discrete Fourier Transform (DFT).
You'll want to use this whenever you need to determine the structure of an image from a geometrical point of view.
*/

int main(int argc, char ** argv)
{
    const char* filename = "download.jpeg";
    Mat I = imread( filename, IMREAD_GRAYSCALE);
    if( I.empty()){
        cout << "Error opening image" << endl;
        return EXIT_FAILURE;
    }

/**
The performance of a DFT is dependent of the image size.
It tends to be the fastest for image sizes that are multiple of the numbers two, three and five.
Therefore, to achieve maximal performance it is generally a good idea to pad border values to the image to get a size with such traits.
The getOptimalDFTSize() returns this optimal size and we can use the copyMakeBorder() function to expand the borders of an image (the appended pixels are initialized with zero)
*/

    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

/**
The result of a Fourier Transform is complex.
This implies that for each image value the result is two image values (one per component).
Moreover, the frequency domains range is much larger than its spatial counterpart.
Therefore, we store these usually at least in a float format.
Therefore we'll convert our input image to this type and expand it with another channel to hold the complex values:
*/

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
    dft(complexI, complexI);            // this way the result may fit in the source matrix
    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))

/**
A complex number has a real (Re) and a complex (imaginary - Im) part. The results of a DFT are complex numbers. The magnitude of a DFT is:
M=(Re(DFT(I))2+Im(DFT(I))2)^0.5
*/

    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

/**
It turns out that the dynamic range of the Fourier coefficients is too large to be displayed on the screen.
We have some small and some high changing values that we can't observe like this.
Therefore the high values will all turn out as white points, while the small ones as black.
To use the gray scale values to for visualization we can transform our linear scale to a logarithmic one:
M1=log(1+M)
*/

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);
    // crop the spectrum, if it has an odd number of rows or columns

/**
Remember, that at the first step, we expanded the image? Well, it's time to throw away the newly introduced values.
For visualization purposes we may also rearrange the quadrants of the result, so that the origin (zero, zero) corresponds with the image center.
*/

    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;
    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

/**
This is done again for visualization purposes.
We now have the magnitudes, however this are still out of our image display range of zero to one.
We normalize our values to this range using the cv::normalize() function.
*/
    imwrite("results/fourier/fourier.jpg",magI);

    normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).
    imshow("Input Image"       , I   );    // Show the result
    imshow("spectrum magnitude", magI);
    waitKey();
    return EXIT_SUCCESS;
}