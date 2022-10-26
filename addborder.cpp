 //OpenCV function copyMakeBorder() to set the borders (extra padding to our image).

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

// Declare the variables
Mat src, dst;
int top, bottom, left, right;
int borderType = BORDER_CONSTANT; //Pad the image with a constant value (i.e. black or 0), value used to fill the border pixels.//
const char* window_name = "copyMakeBorder Demo";

RNG rng(12345);// rng  is a random number generator. We use it to generate the random border color//
int main( int argc, char** argv )
{
    const char* imageName ="download.jpeg";
	
    // Loads an image
    src = imread( imageName, IMREAD_COLOR ); 
    // Check if image is loaded fine
    if( src.empty()) {
        printf(" Error opening image\n");
        printf(" Program Arguments: [ default download.jpg] \n");
        return -1;
    }
    // Brief how-to for this program
    printf( "\n \t copyMakeBorder Demo: \n" );
    printf( "\t -------------------- \n" );
    printf( " ** Press 'c' to set the border to a random constant value \n");
    printf( " ** Press 'r' to set the border to be replicated \n");
    printf( " ** Press 'ESC' to exit the program \n");
	
	
	/*namedWindow() method is used to create a window with a suitable name and size to display images and videos on the screen.
	The image by default is displayed in its original size, so we may need to resize the image for it to fit our screen.*/
    namedWindow( window_name, WINDOW_AUTOSIZE );
	
	
    // Initialize arguments for the filter
	// top and left are 5% the size of src.
    top = (int) (0.05*src.rows); bottom = top;
    left = (int) (0.05*src.cols); right = left;
	
	
    for(int i=0;;i++)
    {  //in each iteration (after 0.5 seconds), the random border color (value) is updated
		//This value is a set of three numbers picked randomly in the range [0,255]//
        Scalar value( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );
		
		// function copyMakeBorder()is called to apply the respective padding//
        copyMakeBorder( src, dst, top, bottom, left, right, borderType, value );
		imwrite("results/addingBorder/borders.jpg",dst);
		imshow( window_name, dst );
		
		/*The program runs in an infinite loop while the key ESC isn't pressed. 
		If the user presses 'c' or 'r', the borderType variable takes the value of BORDER_CONSTANT or BORDER_REPLICATE respectively:*/
        char c = (char)waitKey(500);
        if( c == 27 )
        { break; }
        else if( c == 'c' )
		//Applies a padding of a constant value for the whole border. This value will be updated randomly each 0.5 seconds//
        { borderType = BORDER_CONSTANT; }
	   
        else if( c == 'r' )
		 //The border will be replicated from the pixel values at the edges of the original image.//
        { borderType = BORDER_REPLICATE; }
    }
    return 0;
}