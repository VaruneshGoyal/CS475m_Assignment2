#include <GL/glut.h>
#include<iostream>
#include<vector>
#include "HNode.hpp"

using namespace std;


HNode *node[3];
int curr=0; //Index of current oprational node


//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key) {
    case '1':
      curr=0;
      break;
    case '2':
      curr=1;
      break;
    case '3':
      curr=2;
      break;
  }
  if (key == 27)
  exit(0);
}

//Our function for processing Non-ASCII keys
// void processSpecialKeys(int key, int x, int y) {
//   switch(key) {
//     case GLUT_KEY_LEFT :
//     node[curr]->dec_ry();
//     break;
//     case GLUT_KEY_RIGHT :
//     node[curr]->inc_ry();
//     break;
//     case GLUT_KEY_UP :
//     node[curr]->dec_rx();
//     break;
//     case GLUT_KEY_DOWN :
//     node[curr]->inc_rx();
//     break;
//     case GLUT_KEY_PAGE_UP :
//     node[curr]->dec_rz();
//     break;
//     case GLUT_KEY_PAGE_DOWN :
//     node[curr]->inc_rz();
//     break;
//   }
//   //Redraw
//   glutPostRedisplay();
// }

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
  gluPerspective(80.0, 1.0, 1.0, 20.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 25.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{

  //Parent Node
  node[0] = new HNode(NULL);
  node[0]->obj_type = 0;
  node[0]->base=2;
  node[0]->top=1;
  node[0]->height=10;
  node[0]->slices=50;
  node[0]->stacks=10;
  // node[0]->change_parameters(0, 0, 0, 0, 45, 0);

  // node[0]->obj_type=1;
  // node[0]->cuboid_length=1;
  // node[0]->cuboid_height=2;
  // node[0]->cuboid_breadth=5;

  // node[0]->obj_type = 2;
  // node[0]->inRadius=1;
  // node[0]->outRadius=2;
  // node[0]->nsides=50;
  // node[0]->rings=4;

  //Child Nodes
  // node[1] = new HNode(node[0],36,v_positions,v_colors);
  // node[1]->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
  // node[2] = new HNode(node[1],36,v_positions,v_colors);
  // node[2]->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,400);
  glutCreateWindow("Hierarchical Modeling");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  // glutSpecialFunc(processSpecialKeys);
  init();
  glutMainLoop();
  return 0;
}