// red_color_detection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

//Fungsi treshold gambar ke biner & kode warna untuk mendeteksi warna merah
IplImage* GetThresholdedImage(IplImage* imgHSV){        
       IplImage* imgThresh=cvCreateImage(cvGetSize(imgHSV),IPL_DEPTH_8U, 1);
       cvInRangeS(imgHSV, cvScalar(170,160,60), cvScalar(180,256,256), imgThresh); 
       return imgThresh;
} 
 
int main(){
      CvCapture* ambil =0;       

      ambil = cvCaptureFromCAM(0);
      if(!ambil){
            printf("Capture failure\n");
            return -1;
      }
      
      IplImage* frame=0;
      cvNamedWindow("Video");      
      cvNamedWindow("Deteksi Warna");

      //iterasi     
      while(true){

            frame = cvQueryFrame(ambil);            
            if(!frame) break;

            frame=cvCloneImage(frame); 
            cvSmooth(frame, frame, CV_GAUSSIAN,3,3); //menghasilkan penghalusan gambar dengan metode Gaussian kernel

            IplImage* imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3); 
            cvCvtColor(frame, imgHSV, CV_BGR2HSV); //Merubah format warna from RGB to HSV
            IplImage* imgThresh = GetThresholdedImage(imgHSV);
          
            cvSmooth(imgThresh, imgThresh, CV_GAUSSIAN,3,3);
            
            cvShowImage("Deteksi Warna", imgThresh);            
            cvShowImage("Video", frame);
            
          
            cvReleaseImage(&imgHSV);
            cvReleaseImage(&imgThresh);            
            cvReleaseImage(&frame);

            
            int c = cvWaitKey(10);
            //If 'ESC' is pressed, break the loop
            if((char)c==27 ) break;      
      }

      cvDestroyAllWindows() ;
      cvReleaseCapture(&ambil);     

      return 0;
}