#include <iostream>
#include <boost/iterator/iterator_concepts.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
  if(argc!=3){
    cout<<"usage: featrue _extration img1 img2"<<endl;
    return 1;    
  }
  Mat img_1 = imread(argv[1],CV_LOAD_IMAGE_COLOR);
  Mat img_2 = imread(argv[2],CV_LOAD_IMAGE_COLOR);
  //--初始化
  vector<KeyPoint> keypoints_1,keypoints_2;
  Mat descriptors_1,descriptors_2;
  Ptr<ORB> orb = ORB::create(500,1.2f,8,31,0,2,ORB::HARRIS_SCORE,31,20);
  //--第一步，检测 Oriented FAST 角点位置
  orb->detect(img_1,keypoints_1);
  orb->detect(img_2,keypoints_2);
  //--第二步，根据角点位置计算BRIEF描述子
  orb->compute(img_1,keypoints_1,descriptors_1);
  orb->compute(img_2,keypoints_2,descriptors_2);
  Mat outimg1;
  drawKeypoints(img_1,keypoints_1,outimg1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
  cv::imshow("ORB特征点",outimg1 );
  // 第三步：对两幅图像中的BRIEF描述子进行匹配，使用hamming距离
  vector<DMatch> matches;
  BFMatcher matcher(NORM_HAMMING);
  matcher.match(descriptors_1,descriptors_2,matches);
  //第四步，匹配点对筛选
  double min_dist = 1000,max_dist = 0;
  for(int i = 0 ; i<descriptors_1.rows;i++){
    double dist = matches[i].distance;
    if(dist<min_dist) min_dist = dist;
    if(dist>max_dist) max_dist = dist;
  }
  printf("-- Max dist : %f \n",max_dist);printf("-- Min dist : %f \n",min_dist);
  vector<DMatch> good_matches;
  for ( int i =0 ; i<descriptors_1.rows;i++){
    if(matches[i].distance<= max(2*min_dist,30.0)){
      good_matches.push_back(matches[i]);
    }
  }
  //第5步： 绘制匹配结果
  Mat img_match;Mat img_goodmatch;
  drawMatches(img_1,keypoints_1,img_2,keypoints_2,matches,img_match);
  drawMatches(img_1,keypoints_1,img_2,keypoints_2,good_matches,img_goodmatch);
  cv::imshow("所有匹配点对",img_match);
  cv::imshow("优化后的匹配点对",img_goodmatch);
  waitKey(0);return 0 ;
}
