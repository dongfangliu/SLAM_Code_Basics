#include <iostream>
#include<chrono>
using namespace std;

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
int main(int argc, char **argv) {
  Mat image;
  image = imread(argv[1]);
  if(image.data == nullptr){
    cout<<"文件"<<argv[1]<<"不存在"<<endl;
    return 0;
  }
  
  cout<<"图像宽为"<<image.cols<<",高为"<<image.rows<<",通道数为"<<image.channels()<<endl;
  imshow("image",image);
  
  waitKey(0);
  
  if(image.type()!= CV_8UC1 &&image.type()!=CV_8UC3){
   cout<<"请输入一张彩色图或者灰度图"<<endl;
  return 0 ;
    
  }
  //遍历图像
  //使用std::chrono
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  for(size_t y = 0; y<image.rows;y++){
    for(size_t x = 0 ; x<image.cols;x++){
      //访问处于x,y处的像素
      //用cv::Mat::ptr 获得图像的行指针
      unsigned char * row_ptr = image.ptr<unsigned char>(y);
      unsigned char * data_ptr = &row_ptr[x*image.channels()];
      for(int c = 0 ; c!= image.channels();c++){
	unsigned char data = data_ptr[c];
	
      }
    }
  }
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
  cout<<"遍历图像用时："<< time_used.count()<<"秒"<<endl;
  
  //关于cv::Mat的拷贝
  //直接赋值并不会复制数据
  Mat image_another = image;
  image_another(Rect(0,0,100,100)).setTo(0);//左上角设置为0
  imshow("image",image);
  cv::waitKey(0);
  
  Mat image_clone = image.clone();
  image_clone(Rect(0,0,100,100)).setTo(255);
  imshow("image",image);
  imshow("image_clone",image_clone);
  cv::waitKey(0);
  
 destroyAllWindows();
 return 0;
}
