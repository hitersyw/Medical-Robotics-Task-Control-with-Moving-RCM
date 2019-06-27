/**
 * \file      RCM.cpp
 *
 * \brief     C++ Source File template
 *
 * \author    Jean Pierre Richa 
 *
 * Project:   Medical Robotics
 */

/*******************************************************************************
 *       I N C L U D E - F I L E S
 ******************************************************************************/

#include <iostream>
#include <vector>
#include "kukaDynRCM.h"

using namespace std;

/*******************************************************************************
 *       C L A S S - M E M B E R - F U N C T I O N S
 ******************************************************************************/

void DYN::RCM::kukaDynRCM(vecxd& q){

  double q1=q(0), q2=q(1), q3=q(2), q4=q(3), q5=q(4), q6=q(5), q7=q(6), lambda=q(7);
  double s1=sin(q1), s2=sin(q2), s3=sin(q3), s4=sin(q4), s5=sin(q5), s6=sin(q6), s7=sin(q7);
  double c1=cos(q1), c2=cos(q2), c3=cos(q3), c4=cos(q4), c5=cos(q5), c6=cos(q6), c7=cos(q7);

  double l0=1, l1=2, l2=3, l3=4, l4=4, l5=4, l6=4, l7=4, off=10;

  vec3d p0(0, 0, 0);

  vec3d p1(0, 0, l0+l1);

  vec3d p2(0, 0, l0+l1);

  vec3d p3(-c1*c2*(l2+l3), -s1*s2*(l2+l3), c2*(l2+l3)+(l0+l1)*(l2+l3));

  vec3d p4(-c1*c2*(l2+l3), -s1*s2*(l2+l3), c2*(l2+l3)+(l0+l1)*(l2+l3));

  vec3d p5((c1*c2*c3*s4 - s1*s3*s4 - c1*s2*c4)*(l4+l5) - c1*s2*(l2+l3),
           (s1*c2*c3*s4 + c1*s3*s4 - s1*s2*c4)*(l4+l5) - s1*s2*(l2+l3),
           (s2*c3*s4 + c2*c4)*(l4*l5) + c2*(l2+l3) + (l0+l1)*(l2+l3)) ;

  vec3d p6((c1*c2*c3*s4 - s1*s3*s4 - c1*s2*c4)*(l4+l5) - c1*s2*(l2+l3),
           (s1*c2*c3*s4 + c1*s3*s4 - s1*s2*c4)*(l4+l5) - s1*s2*(l2+l3),
           (s2*c3*s4 + c2*c4)*(l4*l5) + c2*(l2+l3) + (l0+l1)*(l2+l3) );

  vec3d p7((-c1*c2*c3*c4*c5*s6 + s1*s3*c4*c5*s6 - c1*s2*s4*c5*s6 + c1*c2*s3*s5*s6 + s1*c3*s5*s6 + c1*c2*c3*s4*c6 - s1*s3*s4*c6 - c1*s2*s4*c6)*(l7 + off) + p6(0),
           (-s1*c2*c3*c4*c5*s6 - c1*s3*c4*c5*s6 - s1*s2*s4*c5*s6 + s1*c2*s3*s5*s6 - c1*c3*s5*s6 + s1*c2*c3*s4*c6 + c1*s3*s4*c6 - s1*s2*c4*c6)*(l7 + off) + p6(1),
           (-s2*c3*c4*c5*s6 + c2*s4*c5*s6 + s2*s3*s5*s6 + s2*c3*s4*c6 + c2*c4*c6)*(l7 + off) + p6(2));

  MatXd J_6(6,7);

  // Jacobian Matrix
  J_6(0,0) = -(l4 + l5)*(s4*(c1*s3 + c2*c3*s1) - c4*s1*s2) + (l2 + l3)*s1*s2;
  J_6(1,0) = -(l4 + l5)*(s4*(s1*s3 - c1*c2*c3) + c1*c4*s2) - (l2 + l3)*c1*s2;
  J_6(5,0) = 1;

  J_6(0,1) = -c1*((l4 + l5)*(c2*c4 + c3*s2*s4) + (l2 + l3)*c2);
  J_6(1,1) = -s1*((l4 + l5)*(c2*c4 + c3*s2*s4) + (l2 + l3)*c2);
  J_6(2,1) = -(l2 + l3)*s2 - (l4 + l5)*c4*s2 + (l4 + l5)*c2*c3*s4;
  J_6(3,1) = s1;
  J_6(4,1) = -c1;


  J_6(0,2) = -(l4 + l5)*s4*(c3*s1 + c1*c2*s3);
  J_6(1,2) = (l4 + l5)*s4*(c1*c3 - c2*s1*s3);
  J_6(2,2) = -(l4 + l5)*s2*s3*s4;
  J_6(3,2) = -c1*s2;
  J_6(4,2) = -s1*s2;
  J_6(5,2) = c2;

  J_6(0,3) = (l4 + l5)*c1*s2*s4 - (l4 + l5)*c4*s1*s3 + (l4 + l5)*c1*c2*c3*c4;
  J_6(1,3) = (l4 + l5)*s1*s2*s4 + (l4 + l5)*c1*c4*s3 + (l4 + l5)*c2*c3*c4*s1;
  J_6(2,3) = -(l4 + l5)*c2*s4 + (l4 + l5)*c3*c4*s2;
  J_6(3,3) = -c3*s1 - c1*c2*s3;
  J_6(4,3) = -c2*s1*s3 + c1*c3;
  J_6(5,3) =-s2*s3;

  J_6(3,4) = -s4*(s1*s3 - c1*c2*c3) - c1*c4*s2;
  J_6(4,4) = s4*(c1*s3 + c2*c3*s1) - c4*s1*s2;
  J_6(5,4) = c2*c4 + c3*s2*s4;

  J_6(3,5) = c5*(c3*s1 + c1*c2*s3) - s5*(c4*(s1*s3 - c1*c2*c3) - c1*s2*s4);
  J_6(4,5) = s5*(c4*(c1*s3 + c2*c3*s1) + s1*s2*s4) - c5*(c1*c3 - c2*s1*s3);
  J_6(5,5) = -s5*(c2*s4 - c3*c4*s2) + c5*s2*s3;

  MatXd linJ6(3,7);
  linJ6 = J_6.block<3,7>(0,0);

  MatXd J_7(6,7);

  J_7(0,0)=-(l4 + l5)*(s4*(c1*s3 + c2*c3*s1) - c4*s1*s2) - (off + l7)*(c6*(s4*(c1*s3 + c2*c3*s1) - c4*s1*s2) - s6*(c5*(c4*(c1*s3 + c2*c3*s1) + s1*s2*s4) + s5*(c1*c3 - c2*s1*s3))) + (l2 + l3)*s1*s2;
  J_7(1,0)=-(l4 + l5)*(s4*(s1*s3 - c1*c2*c3) + c1*c4*s2) - (off + l7)*(c6*(s4*(s1*s3 - c1*c2*c3) + c1*c4*s2) - s6*(c5*(c4*(s1*s3 - c1*c2*c3) - c1*s2*s4) + s5*(c3*s1 + c1*c2*s3))) - (l2 + l3)*c1*s2;
  J_7(5,0)=1;

  J_7(0,1)=-(off + l7)*c1*(s6*(c5*(c2*s4 - c3*c4*s2) + s2*s3*s5) + c6*(c2*c4 + c3*s2*s4)) - (l2 + l3)*c1*c2 - (l4 + l5)*c1*(c2*c4 + c3*s2*s4);
  J_7(1,1)=-(off + l7)*s1*(s6*(c5*(c2*s4 - c3*c4*s2) + s2*s3*s5) + c6*(c2*c4 + c3*s2*s4)) - (l2 + l3)*c2*s1 - (l4 + l5)*s1*(c2*c4 + c3*s2*s4);
  J_7(2,1)=(off + l7)*c2*s3*s5*s6 - (l4 + l5)*c4*s2 + (l4 + l5)*c2*c3*s4 - (off + l7)*c4*c6*s2 + (off + l7)*c2*c3*c6*s4 - (l2 + l3)*s2 - (off + l7)*c5*s2*s4*s6 - (off + l7)*c2*c3*c4*c5*s6;
  J_7(3,1)=s1;
  J_7(4,1)=-c1;

  J_7(0,2)=-(l4 + l5)*c3*s1*s4 - (l4 + l5)*c1*c2*s3*s4 + (off + l7)*c3*c6*s1*s4 - (off + l7)*s1*s3*s5*s6 - (off + l7)*c1*c2*c6*s3*s4 + (off + l7)*c1*c2*c3*s5*s6 + (off + l7)*c3*c4*c5*s1*s6 + (off + l7)*c1*c2*c4*c5*s3*s6;
  J_7(1,2)=-(l4 + l5)*c2*s1*s3*s4 + (off + l7)*c1*c3*c6*s4 + (l4 + l5)*c1*c3*s4 + (off + l7)*c1*s3*s5*s6 - (off + l7)*c1*c3*c4*c5*s6 - (off + l7)*c2*c6*s1*s3*s4 + (off + l7)*c2*c3*s1*s5*s6 + (off + l7)*c2*c4*c5*s1*s3*s6;
  J_7(2,2)=-s2*((l4 + l5)*s3*s4 + (off + l7)*c6*s3*s4 - (off + l7)*c3*s5*s6 - (off + l7)*c4*c5*s3*s6);
  J_7(3,2)=-c1*s2;
  J_7(4,2)=-s1*s2;
  J_7(5,2)=c2;

  J_7(0,3)=(l4 + l5)*c1*s2*s4 - (l4 + l5)*c4*s1*s3 + (l4 + l5)*c1*c2*c3*c4 + (off + l7)*c1*c6*s2*s4 - (off + l7)*c4*c6*s1*s3 - (off + l7)*c1*c4*c5*s2*s6 - (off + l7)*c5*s1*s3*s4*s6 + (off + l7)*c1*c2*c3*c4*c6 + (off + l7)*c1*c2*c3*c5*s4*s6;
  J_7(1,3)=(l4 + l5)*s1*s2*s4 + (l4 + l5)*c1*c4*s3 + (l4 + l5)*c2*c3*c4*s1 + (off + l7)*c1*c4*c6*s3 + (off + l7)*c6*s1*s2*s4 + (off + l7)*c2*c3*c4*c6*s1 - (off + l7)*c4*c5*s1*s2*s6 + (off + l7)*c1*c5*s3*s4*s6 + (off + l7)*c2*c3*c5*s1*s4*s6;
  J_7(2,3)=(off + l7)*c3*c5*s2*s4*s6 + (l4 + l5)*c3*c4*s2 - (off + l7)*c2*c6*s4 + (off + l7)*c3*c4*c6*s2 + (off + l7)*c2*c4*c5*s6 - (l4 + l5)*c2*s4;
  J_7(3,3)=-c3*s1 - c1*c2*s3;
  J_7(4,3)=-c2*s1*s3 + c1*c3;
  J_7(5,3)=-s2*s3;

  J_7(0,4)=(off + l7)*s6*(c3*c5*s1 + c1*c2*c5*s3 + c1*s2*s4*s5 - c4*s1*s3*s5 + c1*c2*c3*c4*s5);
  J_7(1,4)=(off + l7)*s6*(c2*c5*s1*s3 - c1*c3*c5 + c1*c4*s3*s5 + s1*s2*s4*s5 + c2*c3*c4*s1*s5);
  J_7(2,4)=(off + l7)*s6*(c5*s2*s3 - c2*s4*s5 + c3*c4*s2*s5);
  J_7(3,4)=-s4*(s1*s3 - c1*c2*c3) - c1*c4*s2;
  J_7(4,4)=s4*(c1*s3 + c2*c3*s1) - c4*s1*s2;
  J_7(5,4)=c2*c4 + c3*s2*s4;

  J_7(0,5)=(off + l7)*c1*c4*s2*s6 + (off + l7)*c3*c6*s1*s5 + (off + l7)*s1*s3*s4*s6 - (off + l7)*c1*c2*c3*s4*s6 + (off + l7)*c1*c2*c6*s3*s5 - (off + l7)*c1*c5*c6*s2*s4 + (off + l7)*c4*c5*c6*s1*s3 - (off + l7)*c1*c2*c3*c4*c5*c6;
  J_7(1,5)=(off + l7)*c4*s1*s2*s6 - (off + l7)*c1*c3*c6*s5 - (off + l7)*c1*s3*s4*s6 - (off + l7)*c1*c4*c5*c6*s3 - (off + l7)*c2*c3*s1*s4*s6 + (off + l7)*c2*c6*s1*s3*s5 - (off + l7)*c5*c6*s1*s2*s4 - (off + l7)*c2*c3*c4*c5*c6*s1;
  J_7(2,5)=-(off + l7)*c3*s2*s4*s6 + (off + l7)*c2*c5*c6*s4 - (off + l7)*c2*c4*s6 + (off + l7)*c6*s2*s3*s5 - (off + l7)*c3*c4*c5*c6*s2;
  J_7(3,5)=c5*(c3*s1 + c1*c2*s3) - s5*(c4*(s1*s3 - c1*c2*c3) - c1*s2*s4);
  J_7(4,5)=s5*(c4*(c1*s3 + c2*c3*s1) + s1*s2*s4) - c5*(c1*c3 - c2*s1*s3);
  J_7(5,5)=-s5*(c2*s4 - c3*c4*s2) + c5*s2*s3;

  J_7(3,6)=-c6*(s4*(s1*s3 - c1*c2*c3) + c1*c4*s2) + s6*(c5*(c4*(s1*s3 - c1*c2*c3) - c1*s2*s4) + s5*(c3*s1 + c1*c2*s3));
  J_7(4,6)=c6*(s4*(c1*s3 + c2*c3*s1) - c4*s1*s2) - s6*(c5*(c4*(c1*s3 + c2*c3*s1) + s1*s2*s4) + s5*(c1*c3 - c2*s1*s3));
  J_7(5,6)=c6*(c2*c4 + c3*s2*s4) + s6*(c5*(c2*s4 - c3*c4*s2) + s2*s3*s5);

  MatXd linJ7(3,7); // 3x7 matrix
  linJ7 = J_7.block<3,7>(0,0);

  // RCM Kinematics
  MatXd J_lambda(3,7); // 3x7 matrix
  J_lambda = ((1-lambda)*linJ7)+(lambda*(linJ6)); //3x7 matrix
  MatXd Jt(3,8);
  Jt.block<3,7>(0,0)=linJ6;
  vec3d g=p6-p7;

  // J_RCM =





  // RCM and additional task errors
  x_rcm=p7(1)+lambda*(p6(1)-p7(1))





}