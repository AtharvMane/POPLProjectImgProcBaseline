#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
int main(int argc, char*argv[]){
    using cv::Mat;
    using std::cout;
    using std::endl;
    Mat A(2,2,CV_8UC1,cv::Scalar(0)); //initialization CV_8UC3==> CV_[number of bits in each place][data tyome (in this case unsigned char)][number of channels]
    Mat B(A); //Only Header assigned
    Mat C(2,2,CV_8UC1,cv::Scalar(25));
    Mat D(2,2,CV_8UC1,cv::Scalar(50));
    Mat E(D);//Only Header assigned

    cout<<"A= "<<endl<<A<<endl;
    cout<<"B= "<<endl<<B<<endl;
    cout<<"C= "<<endl<<C<<endl;
    cout<<"D= "<<endl<<D<<endl;
    cout<<"E= "<<endl<<E<<endl;
    cout<<endl<<endl;
    cout<<"D=E"<<endl;

    D=C;//only pointer changed so E will not change
    cout<<"A= "<<endl<<A<<endl;
    cout<<"B= "<<endl<<B<<endl;
    cout<<"C= "<<endl<<C<<endl;
    cout<<"D= "<<endl<<D<<endl;
    cout<<"E= "<<endl<<E<<endl;
    cout<<endl<<endl;
    cout<<"C.copy(A)"<<endl;

    C.copyTo(A); //matrix if A is changed so B will change
    cout<<"A= "<<endl<<A<<endl;
    cout<<"B= "<<endl<<B<<endl;
    cout<<"C= "<<endl<<C<<endl;
    cout<<"D= "<<endl<<D<<endl;
    cout<<"E= "<<endl<<E<<endl;


}