//OpenCV function filter2D() to create our own linear filters//


#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
int main ( int argc, char** argv )
{
    // Declare variables
	
    Mat src; // Source image
	Mat dst; // Destination image
	
    Mat kernel;
	/*A kernel is essentially a fixed size array of numerical coefficients along with an anchor point in that array, 
	which is typically located at the center. The kernel is scanned through the image.*/
	
    Point anchor;//The position of the anchor relative to its kernel. The location Point(-1, -1) indicates the center by default.
	
    double delta;//A value to be added to each pixel during the correlation. By default it is 0
	
    int ddepth;//The depth of dst. A negative value (such as −1) indicates that the depth is the same as the source.
	
    int kernel_size;
    const char* window_name = "filter2D Demo";
    const char* imageName = "download.jpeg";
	
	
    // Loads an image
	/*imread() method loads an image from the specified file. 
	If the image cannot be read (because of missing file, improper permissions, unsupported or invalid format) then this method returns an empty matrix.*/
    src = imread( imageName); 
    if( src.empty() )
    {
        printf(" Error opening image\n");
        printf(" Program Arguments: [ default download.jpeg] \n");
        return EXIT_FAILURE;
    }
	
	
    // Initialize arguments for the filter
    anchor = Point( -1, -1 );
    delta = 0;
    ddepth = -1;
	
	
    // Loop - Will filter the image with different kernel sizes each 0.5 seconds
    int ind = 0;
    for(;;)
    {
        // Update kernel size for a normalized box filter
		
        kernel_size = 3 + 2*( ind%5 );
        kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);
		
        // Apply filter
		//The program will perform the filter operation with kernels of sizes 3, 5, 7, 9 and 11.
        filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
		imwrite("results/filtering/custom_filter.jpg",dst);
		// imshow() method is used to display an image in a window. The window automatically fits to the image size
        imshow( window_name, dst );
		
		//The filter output (with each kernel) will be shown during 500 milliseconds
        char c = (char)waitKey(500);
		
        // Press 'ESC' to exit the program
        if( c == 27 )
        { break; }
        ind++;
    }
    return EXIT_SUCCESS;
}