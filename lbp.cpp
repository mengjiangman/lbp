#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <string>
#include  <cxcore.h>  

using namespace std;
using namespace cv;
#include "stdafx.h"  


   
using namespace std;  
using namespace cv;  
   
  
//»ùÓÚopencvµÄLBPËã·¨ 
void LBP (IplImage *src,IplImage *dst)  
{  
    int tmp[8]={0};  
    CvScalar s;  
  
    IplImage * temp = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U,1);  
    uchar *data=(uchar*)src->imageData;  
    int step=src->widthStep; //Ã¿ÐÐµÄ×Ö½ÚÊý 
  
    cout<<"step"<<step<<endl;  
  
    for (int i=1;i<src->height-1;i++)  
      for(int j=1;j<src->width-1;j++)  
      {  
          int sum=0;  
          if(data[(i-1)*step+j-1]>data[i*step+j])  
            tmp[0]=1;  
          else  
            tmp[0]=0;  
          if(data[i*step+(j-1)]>data[i*step+j])  
            tmp[1]=1;  
          else  
            tmp[1]=0;  
          if(data[(i+1)*step+(j-1)]>data[i*step+j])  
            tmp[2]=1;  
          else  
            tmp[2]=0;  
          if (data[(i+1)*step+j]>data[i*step+j])  
            tmp[3]=1;  
          else  
            tmp[3]=0;  
          if (data[(i+1)*step+(j+1)]>data[i*step+j])  
            tmp[4]=1;  
          else  
            tmp[4]=0;  
          if(data[i*step+(j+1)]>data[i*step+j])  
            tmp[5]=1;  
          else  
            tmp[5]=0;  
          if(data[(i-1)*step+(j+1)]>data[i*step+j])  
            tmp[6]=1;  
          else  
            tmp[6]=0;  
          if(data[(i-1)*step+j]>data[i*step+j])  
            tmp[7]=1;  
          else  
            tmp[7]=0;     
          //¼ÆËãLBP±àÂë  
            s.val[0]=(tmp[0]*1+tmp[1]*2+tmp[2]*4+tmp[3]*8+tmp[4]*16+tmp[5]*32+tmp[6]*64+tmp[7]*128);  
          
        cvSet2D(dst,i,j,s);//Ð´ÈëLBPÍ¼Ïñ  
      }  
}  
  
  
  
int _tmain(int argc, _TCHAR* argv[])  
{  
   
    IplImage* face = cvLoadImage("F://myproject////picture//lena.jpg",CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);  
    IplImage* Gray_face = cvCreateImage( cvSize( face->width,face->height ), face->depth, 1);//ÏÈ·ÖÅäÍ¼Ïñ¿Õ¼ä  
    cvCvtColor(face, Gray_face ,CV_BGR2GRAY);//°ÑÔØÈëÍ¼Ïñ×ª»»Îª»Ò¶ÈÍ¼  
    IplImage* lbp_face =   cvCreateImage(cvGetSize(Gray_face), IPL_DEPTH_8U,1);//·ÖÅäÍ¼Ïñ¿Õ¼ä  
  
    cvNamedWindow("Gray Image",1);  
    cvShowImage("Gray Image",Gray_face); 
  
  
    //ÏÔÊ¾Ô­Ê¼µÄÊäÈëÍ¼Ïñ  
    cvNamedWindow("Src Image",CV_WINDOW_AUTOSIZE);  
    cvShowImage("Src Image",face);    
  
    //¼ÆËãÊäÈëÍ¼ÏñµÄLBPÎÆÀíÌØÕ÷  
    LBP(Gray_face,lbp_face);  
  
  
      
    //ÏÔÊ¾Í¼ÏñµÄLBPÎÆÀíÌØÕ÷Í¼  
    cvNamedWindow("LBP Image",CV_WINDOW_AUTOSIZE);  
    cvShowImage("LBP Image",lbp_face);  
    waitKey();  
  
    //cvReleaseImage(&face);  
    cvDestroyWindow("Src Image");  
   
    return 0;  
  
}  