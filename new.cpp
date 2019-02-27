#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#define path "/home/joe/Desktop/pers.jpg"
using namespace std;
using namespace cv;

int main(){
    vector <Point2f> mx;
Mat image=imread(path,IMREAD_COLOR);
Mat image_binary,image_2;
cvtColor(image,image_2,COLOR_BGR2HSV);
inRange(image_2,Scalar(0,165,171),Scalar(12,255,255),image_binary);
dilate(image_binary,image_binary,Mat::ones(Size(4,4),CV_8UC1));
vector<vector<Point> > contours;
findContours(image_binary,contours,RETR_LIST,CHAIN_APPROX_SIMPLE);
for (int x=0;x<contours.size();x++){
    if(contourArea(contours[x])>100){
        Point2f pp;
        pp.x=moments(contours[x]).m10/moments(contours[x]).m00;
        pp.y=moments(contours[x]).m01/moments(contours[x]).m00;
        mx.push_back(pp);
        putText(image,to_string(x),pp,FONT_HERSHEY_PLAIN,2,Scalar(0,255,0),2);
    }
}
imshow("image",image);
waitKey(0);
for(int x=0;x<mx.size();x++){
    circle(image,mx[x],2,Scalar(255,0,0),-1,LINE_AA);
}
int len[4];
for(int x=0;x<mx.size();x++){
    len[x]=(mx[x].x*mx[x].x+mx[x].y*mx[x].y);
}
int len_2[4];
for(int x=0;x<4;x++){
    len_2[x]=len[x];
}
sort(len,len+4);
vector<Point2f> mx_x;
for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
        if(len[x]==len_2[y]){
            mx_x.push_back(mx[y]);
        }
    }
}






vector<Point2f> newvector;
newvector.push_back(Point2f(0,0));
newvector.push_back(Point2f(600,0));
newvector.push_back(Point2f(0,600));
newvector.push_back(Point2f(600,600));
Mat matrix=getPerspectiveTransform(mx_x,newvector);
Mat newmat;
warpPerspective(image,newmat,matrix,newmat.size(),INTER_LINEAR);
Rect a(0,0,500,500);
Mat imm=newmat(a);
imshow("image_binary",imm);

waitKey(0);

}
