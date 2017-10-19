#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
#include<Eigen/Geometry>
using namespace Eigen;
int main(int argc, char **argv) {
  //Eigen/Geometry提供了各种旋转和平移的表示
  //3D旋转矩阵直接使用 Matrix3d 或者 Matrix3f
    Matrix3d rotation_Matrix = Matrix3d::Identity();
    //旋转向量使用AngleAxisd , 它底层不直接是Matrix，但运算可以当作矩阵
    AngleAxisd rotation_vector (M_PI/4,Vector3d(0,0,1));
    cout .precision(3);
    cout<<"rotation matrix = \n "<<rotation_vector.matrix()<<endl;
    //用matrix()转化成矩阵
    //也可以直接赋值
    rotation_Matrix = rotation_vector.toRotationMatrix();
    //用AngleAxis可以进行坐标变换
    Vector3d v(1,0,0);
    Vector3d v_rotated = rotation_vector*v;
    cout<<"(1,0,0) after rotation ：\n"<<v_rotated.transpose()<<endl;
    //或者用旋转矩阵
    v_rotated = rotation_Matrix*v;
    cout<<"(1,0,0) after rotation ：\n"<<v_rotated.transpose()<<endl;
    
    Vector3d euler_angles  = rotation_Matrix.eulerAngles(2,1,0);
    //按照ZYX的顺序
    cout<<"yaw pitch roll = "<<euler_angles.transpose()<<endl;
    
    //欧氏变换矩阵使用Eigen::Isometry
    
    Isometry3d T = Isometry3d::Identity();
    T.rotate(rotation_vector);
    T.pretranslate(Vector3d(1,3,4));
    cout<<"Transform matrix = \n" <<T.matrix()<<endl;
    //用变换矩阵进行坐标变换
    Eigen::Vector3d v_transformed = T*v;
    cout<<"v_transformed = "<<v_transformed.transpose()<<endl;
    //对于仿射和射影变换，使用Eigen::Affine3d 和 Eigen::Projective3d即可
    
    //四元数
    //可以直接把AngleAixs赋值给四元数，反之亦然
    Quaterniond q = Quaterniond(rotation_vector);
    cout<<"quaternion = \n"<<q.coeffs()<<endl;//注意coeffs的顺序是（x,y,z,w),w是实部，其他是虚部
    
    q = Quaterniond(rotation_Matrix);
    cout<<"quaternion = \n"<<q.coeffs()<<endl;
    
    v_rotated = q*v;//注意数学上是qvq^(-1);
    
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
    return 0;
}
