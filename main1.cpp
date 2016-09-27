#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "HNode.hpp"

using namespace std;


HNode *node[3];
int curr=0; //Index of current oprational node


//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key) {
    case '1':
      //curr=0;
      cout<<"rz "<<node[0]->rz<<endl;
      cout<<"rx "<<node[0]->rx<<endl;
      cout<<"ry "<<node[0]->ry<<endl;
      break;
    case '2':
      //curr=1;
      cout<<"tx "<<node[0]->tx<<endl;
      cout<<"ty "<<node[0]->ty<<endl;
      cout<<"tz "<<node[0]->tz<<endl;
      break;
    case '3':
      //curr=0;
      cout<<"rz1 "<<node[1]->rz<<endl;
      cout<<"rx1 "<<node[1]->rx<<endl;
      cout<<"ry1 "<<node[1]->ry<<endl;
      break;
    case '4':
      //curr=1;
      cout<<"tx1 "<<node[1]->tx<<endl;
      cout<<"ty1 "<<node[1]->ty<<endl;
      cout<<"tz1 "<<node[1]->tz<<endl;
      break;
    case '5':
      //curr=0;
      cout<<"rz1 "<<node[2]->rz<<endl;
      cout<<"rx1 "<<node[2]->rx<<endl;
      cout<<"ry1 "<<node[2]->ry<<endl;
      break;
    case '6':
      //curr=1;
      cout<<"tx1 "<<node[2]->tx<<endl;
      cout<<"ty1 "<<node[2]->ty<<endl;
      cout<<"tz1 "<<node[2]->tz<<endl;
      break;
    // case '3':
    //   //curr=2;

    //   break;
  }
  if (key == 27)
  exit(0);
}

//Our function for processing Non-ASCII keys
void processSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT :
    //node[curr]->dec_ry();
    node[1]->dec_tx();
    // node[0]->dec_rx();
    break;
    case GLUT_KEY_RIGHT :
    //node[curr]->inc_ry();
    node[1]->inc_tx();
    // node[0]->inc_rx();
    break;
    case GLUT_KEY_UP :
    //node[curr]->dec_rx();
    node[1]->inc_ty();
    // node[0]->inc_ry();
    break;
    case GLUT_KEY_DOWN :
    // node[curr]->inc_rx();
    node[1]->dec_ty();
    // node[0]->dec_ry();
    break;
    case GLUT_KEY_PAGE_UP :
    //node[curr]->dec_rz();
    node[1]->inc_tz();
    // node[0]->inc_tz();
    break;
    case GLUT_KEY_PAGE_DOWN :
    //node[curr]->inc_rz();
    node[1]->dec_tz();
    // node[0]->dec_tz();
    break;
  }
  //Redraw
  glutPostRedisplay();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  node[0]->render_tree();
  glutSwapBuffers();
}

void init(void)
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);
  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);
  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(80.0, 1.0, 1.0, 120.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 5.0, 100.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{

  //Parent Node

  //of the first node - tilted cylinder connecting front handle and gear
  // node[2] = new HNode(node[0]);
  // node[2]->obj_type = 0;
  // node[2]->base=4.5;
  // node[2]->top=4.5;
  // node[2]->height=45;
  // node[2]->slices=50;
  // node[2]->stacks=10;
  // node[2]->change_parameters(-9, 4, 0, 53, 61, 56);

  // // //of the first node - tilted cylinder connecting front handle and seat
  // node[1] = new HNode(node[0]);
  // node[1]->obj_type = 0;
  // node[1]->base=4.5;
  // node[1]->top=4.5;
  // node[1]->height=90;
  // node[1]->slices=50;
  // node[1]->stacks=10;
  // node[1]->change_parameters(-9, 0, 0, 90, 70, 0);


  // of the first node - vetical cylinder containing the front handle
  node[0] = new HNode(NULL);
  node[0]->obj_type = 0;
  node[0]->base=4.5;
  node[0]->top=4.5;
  node[0]->height=45;
  node[0]->slices=50;
  node[0]->stacks=10;
  node[0]->add_child(node[1]);
  // node[0]->add_child(node[2]);
  node[0]->change_parameters(-60, 0, -22.5, -90, 20, 0);


  //trial - cuboid
  // node[0]->obj_type=1;
  // node[0]->cuboid_length=5;
  // node[0]->cuboid_height=5;
  // node[0]->cuboid_breadth=5;
  // node[0]->change_parameters(0, 0, 0, 45, 0, 0);

  //trial - torus
  // node[0]->obj_type = 2;
  // node[0]->inRadius=1;
  // node[0]->outRadius=2;
  // node[0]->nsides=50;
  // node[0]->rings=50;
  // node[0]->change_parameters(0, 0, 0, 90, 0, 45);

  //Child Nodes
  // node[1] = new HNode(node[0],36,v_positions,v_colors);
  // node[1]->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
  // node[2] = new HNode(node[1],36,v_positions,v_colors);
  // node[2]->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512,512);
  glutCreateWindow("Hierarchical Modeling");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  init();
  glutMainLoop();
  return 0;
}