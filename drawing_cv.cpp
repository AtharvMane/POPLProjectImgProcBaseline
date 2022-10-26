//BASIC DRAWING:
// We can use the various OpenCV functions to draw some basic figures. For example, to draw a line, we need to pass the starting and ending coordinates of the line. The function used is cv::line(). To draw a rectangle, we need the top-left corner and the bottom-right corner of the rectangle. The function used is cv::rectangle(). To draw a circle, we need the center coordinates and the radius of the circle. The function used is cv::circle(). To write some text, we need the bottom-left corner of the text and the font to be used. The function used is cv::putText().

// We are using mainly two structures: Point and Scalar. 
// Point is a structure that contains two integers, x and y, which are the coordinates of the point.
// Scalar is a structure that contains three integers, B, G and R, which are the values of the color of the point.


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define w 400

using namespace cv;

void MyEllipse( Mat img, double angle );

void MyFilledCircle( Mat img, Point center );

void MyPolygon( Mat img );

void MyLine( Mat img, Point start, Point end );

int main( void ){

  //Because we intend to draw two examples (an atom and a rook), we must create two images as well as two windows to display them.

  char atom_window[] = "Drawing 1: Atom";
  char rook_window[] = "Drawing 2: Rook";
  Mat atom_image = Mat::zeros( w, w, CV_8UC3 );
  Mat rook_image = Mat::zeros( w, w, CV_8UC3 );


  //We wrote functions to draw various geometric shapes. For example, we used MyEllipse and MyFilledCircle to draw the atom:
  
  MyEllipse( atom_image, 90 );
  MyEllipse( atom_image, 0 );
  MyEllipse( atom_image, 45 );
  MyEllipse( atom_image, -45 );
  MyFilledCircle( atom_image, Point( w/2, w/2) );


  //To draw the rook we employed MyLine, rectangle and a MyPolygon:
  MyPolygon( rook_image );

  //The rectangle will be drawn on rook_image, and the vertices are defined, and the colour of the rectangle is defined in BGR. Since the thickness of the rectangle is negative, the rectangle will be filled.
  rectangle( rook_image,
         Point( 0, 7*w/8 ),
         Point( w, w),
         Scalar( 0, 255, 255 ),
         FILLED,
         LINE_8 );


  MyLine( rook_image, Point( 0, 15*w/16 ), Point( w, 15*w/16 ) );
  MyLine( rook_image, Point( w/4, 7*w/8 ), Point( w/4, w ) );
  MyLine( rook_image, Point( w/2, 7*w/8 ), Point( w/2, w ) );
  MyLine( rook_image, Point( 3*w/4, 7*w/8 ), Point( 3*w/4, w ) );


  imshow( atom_window, atom_image );
  moveWindow( atom_window, 0, 200 );
  imshow( rook_window, rook_image );
  moveWindow( rook_window, w, 200 );
  waitKey( 0 );
  return(0);
}

//The function ellipse() draws an ellipse, which is displayed in img, and the center location and the size of box are specified. The ellipse is rotated by angle degrees, and it extends an arc with measure between 0 to 360 degrees. The colour is specified in BGR. The thickness is specified in pixels. If the thickness is negative, the ellipse is filled.

void MyEllipse( Mat img, double angle )
{
  int thickness = 2;
  int lineType = 8;
  ellipse( img,
       Point( w/2, w/2 ),
       Size( w/4, w/16 ),
       angle,
       0,
       360,
       Scalar( 255, 0, 0 ),
       thickness,
       lineType );
}


//The function circle() draws a circle, which is displayed in img, and the center location is specified, the radius, colour, and thickness details are also provided.

void MyFilledCircle( Mat img, Point center )
{
  circle( img,
      center,
      w/32,
      Scalar( 0, 0, 255 ),
      FILLED,
      LINE_8 );
}


//We use the fillPoly() function to draw a polygon which will be drawn on img, and the vertices are set of points in ppt, and the colour of the polygon is specified in BGR.

void MyPolygon( Mat img )
{
  int lineType = LINE_8;
  Point rook_points[1][20];
  rook_points[0][0]  = Point(    w/4,   7*w/8 );
  rook_points[0][1]  = Point(  3*w/4,   7*w/8 );
  rook_points[0][2]  = Point(  3*w/4,  13*w/16 );
  rook_points[0][3]  = Point( 11*w/16, 13*w/16 );
  rook_points[0][4]  = Point( 19*w/32,  3*w/8 );
  rook_points[0][5]  = Point(  3*w/4,   3*w/8 );
  rook_points[0][6]  = Point(  3*w/4,     w/8 );
  rook_points[0][7]  = Point( 26*w/40,    w/8 );
  rook_points[0][8]  = Point( 26*w/40,    w/4 );
  rook_points[0][9]  = Point( 22*w/40,    w/4 );
  rook_points[0][10] = Point( 22*w/40,    w/8 );
  rook_points[0][11] = Point( 18*w/40,    w/8 );
  rook_points[0][12] = Point( 18*w/40,    w/4 );
  rook_points[0][13] = Point( 14*w/40,    w/4 );
  rook_points[0][14] = Point( 14*w/40,    w/8 );
  rook_points[0][15] = Point(    w/4,     w/8 );
  rook_points[0][16] = Point(    w/4,   3*w/8 );
  rook_points[0][17] = Point( 13*w/32,  3*w/8 );
  rook_points[0][18] = Point(  5*w/16, 13*w/16 );
  rook_points[0][19] = Point(    w/4,  13*w/16 );
  const Point* ppt[1] = { rook_points[0] };
  int npt[] = { 20 };
  fillPoly( img,
        ppt,
        npt,
        1,
        Scalar( 255, 255, 255 ),
        lineType );
}


//Myline() calls the function line, and draws a line from start to end, which is displayed in img, and the line color is defined by (x, y, z) in RGB format, and the thickness, and lineType are specified.

void MyLine( Mat img, Point start, Point end )
{
  int thickness = 2;
  int lineType = LINE_8;
  line( img,
    start,
    end,
    Scalar( 0, 0, 0 ),
    thickness,
    lineType );
}