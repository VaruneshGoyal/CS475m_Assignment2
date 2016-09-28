#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "HNode.hpp"

using namespace std;


HNode *node[10];
HNode *frame[5];
HNode *wheel_front;
HNode *wheel_back;
HNode *spoke_front[9];
HNode *spoke_back[9];
HNode *spoke_front2[9];
HNode *spoke_back2[9];
HNode *spoke_front_extra[9];
HNode *spoke_back_extra[9];
HNode *spoke_front2_extra[9];
HNode *spoke_back2_extra[9];
HNode *wheel_axis_f, *wheel_axis_b;


HNode *handle_connect_with_frame, *handle_connect_front_wheel_across, 
      *handle_connect_front_wheel_left, *handle_connect_front_wheel_right,
      *handlebar_connector, *handlebar_connector_across, *handlebar_left, *handlebar_right;

//static variables
  float wheel_outer_radius = 24;
  float wheel_tyre_radius = 1;
  float bar_radius = 2;
  float handlebar_connector_across_length = 23;
  float handlebar_connector_length = 15;
  float spoke_length = 21;
  float spoke_radius = 0.3;
  float extra_spoke_length = 2;
  float extra_spoke_radius = 0.4;
  float handle_connect_with_frame_length = 23;
  float handle_connect_front_wheel_across_length = 8;
  float handle_connect_front_wheel_length = wheel_outer_radius + bar_radius + 0.5;
  float handlebar_handle_length = 10;
  float wheel_axis_length = handle_connect_front_wheel_across_length - 2*bar_radius;

//dynamic variables  
  float handle_rotation = 0;
  float wheel_rotation = 0;


int curr=0; //Index of current oprational node


//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 'X':
      glRotatef(1,1,0,0);
      glutPostRedisplay();
      break;
    case 'Y':
      glRotatef(1,0,1,0);
      glutPostRedisplay();
      break;      
    case 'Z':
      glRotatef(1,0,0,1);
      glutPostRedisplay();
      break;     
    case 'x':
      glRotatef(1,-1,0,0);
      glutPostRedisplay();
      break;
    case 'y':
      glRotatef(1,0,-1,0);
      glutPostRedisplay();
      break;      
    case 'z':
      glRotatef(1,0,0,-1);
      glutPostRedisplay();
      break;     
    case 'H':
      handle_rotation++;
      handle_connect_with_frame->rz++;
      glutPostRedisplay();
      break;
    case 'h':
      handle_rotation--;
      handle_connect_with_frame->rz--;
      glutPostRedisplay();
      break;
    case 'F':
      wheel_rotation++;
      wheel_front->rz++;
      wheel_back->rz++;
      glutPostRedisplay();
      break;
    case 'B':
      wheel_rotation--;
      wheel_front->rz--;
      wheel_back->rz--;
      glutPostRedisplay();
      break;
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
      cout<<"rz1 "<<frame[0]->rz<<endl;
      cout<<"rx1 "<<frame[0]->rx<<endl;
      cout<<"ry1 "<<frame[0]->ry<<endl;
      break;
    case '4':
      //curr=1;
      cout<<"tx1 "<<frame[0]->tx<<endl;
      cout<<"ty1 "<<frame[0]->ty<<endl;
      cout<<"tz1 "<<frame[0]->tz<<endl;
      break;
    case '5':
      //curr=0;
      cout<<"rz1 "<<wheel_front->rz<<endl;
      cout<<"rx1 "<<wheel_front->rx<<endl;
      cout<<"ry1 "<<wheel_front->ry<<endl;
      break;
    case '6':
      //curr=1;
      cout<<"tx1 "<<wheel_front->tx<<endl;
      cout<<"ty1 "<<wheel_front->ty<<endl;
      cout<<"tz1 "<<wheel_front->tz<<endl;
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
    frame[0]->dec_tx();
    // node[0]->dec_rx();
    break;
    case GLUT_KEY_RIGHT :
    //node[curr]->inc_ry();
    frame[0]->inc_tx();
    // node[0]->inc_rx();
    break;
    case GLUT_KEY_UP :
    //node[curr]->dec_rx();
    frame[0]->inc_ty();
    // node[0]->inc_ry();
    break;
    case GLUT_KEY_DOWN :
    // node[curr]->inc_rx();
    frame[0]->dec_ty();
    // node[0]->dec_ry();
    break;
    case GLUT_KEY_PAGE_UP :
    //node[curr]->dec_rz();
    frame[0]->inc_tz();
    // node[0]->inc_tz();
    break;
    case GLUT_KEY_PAGE_DOWN :
    //node[curr]->inc_rz();
    frame[0]->dec_tz();
    // node[0]->dec_tz();
    break;
  }
  //Redraw
  glutPostRedisplay();
}

void display(void)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
  gluPerspective(80.0, 1.0, 1.0, 200.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 100.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{

//Parent Node

  //of the first node - tilted cylinder connecting front handle and gear
  // wheel_front = new HNode(node[0]);
  // wheel_front->obj_type = 0;
  // wheel_front->base=4.5;
  // wheel_front->top=4.5;
  // wheel_front->height=45;
  // wheel_front->slices=50;
  // wheel_front->stacks=10;
  // wheel_front->change_parameters(-9, 4, 0, 53, 61, 56);

  // // //of the first node - tilted cylinder connecting front handle and seat
  // frame[0] = new HNode(node[0]);
  // frame[0]->obj_type = 0;
  // frame[0]->base=4.5;
  // frame[0]->top=4.5;
  // frame[0]->height=90;
  // frame[0]->slices=50;
  // frame[0]->stacks=10;
  // frame[0]->change_parameters(-9, 0, 0, 90, 70, 0);


// of the first node - vetical cylinder containing the front handle
  node[0] = new HNode(NULL);
  
  frame[0] = new HNode(NULL);
  node[0]->add_child(frame[0]);

  wheel_front = new HNode(NULL);
  wheel_back = new HNode(NULL);
  node[0]->add_child(wheel_back);

  for(int i=0; i<9; i++){
    spoke_back[i] = new HNode(NULL);
    spoke_front[i] = new HNode(NULL);
    wheel_front->add_child(spoke_front[i]);
    wheel_back->add_child(spoke_back[i]);

    spoke_back2[i] = new HNode(NULL);
    spoke_front2[i] = new HNode(NULL);
    wheel_front->add_child(spoke_front2[i]);
    wheel_back->add_child(spoke_back2[i]);

    spoke_back2_extra[i] = new HNode(NULL);
    spoke_back_extra[i] = new HNode(NULL);
    spoke_front_extra[i] = new HNode(NULL);
    spoke_front2_extra[i] = new HNode(NULL);
    spoke_back[i]->add_child(spoke_back_extra[i]);
    spoke_back2[i]->add_child(spoke_back2_extra[i]);
    spoke_front[i]->add_child(spoke_front_extra[i]);
    spoke_front2[i]->add_child(spoke_front2_extra[i]);
  }

  wheel_axis_f = new HNode(NULL);
  wheel_axis_b = new HNode(NULL);
  wheel_front->add_child(wheel_axis_f);
  wheel_back->add_child(wheel_axis_b);

//handle
  handle_connect_with_frame = new HNode(NULL);
  node[0]->add_child(handle_connect_with_frame);

  handle_connect_front_wheel_across = new HNode(NULL);
  handle_connect_front_wheel_across->add_child(wheel_front);
  handle_connect_front_wheel_right = new HNode(NULL);
  handle_connect_front_wheel_left = new HNode(NULL);
  handle_connect_with_frame->add_child(handle_connect_front_wheel_across);
  handle_connect_front_wheel_across->add_child(handle_connect_front_wheel_left);
  handle_connect_front_wheel_across->add_child(handle_connect_front_wheel_right);

  handlebar_connector = new HNode(NULL);
  handle_connect_with_frame->add_child(handlebar_connector);
  handlebar_connector_across = new HNode(NULL);
  handlebar_connector->add_child(handlebar_connector_across);
  handlebar_left = new HNode(NULL);
  handlebar_right = new HNode(NULL);
  handlebar_connector_across->add_child(handlebar_left);
  handlebar_connector_across->add_child(handlebar_right);


//trial - cuboid
  // node[0]->obj_type=1;
  // node[0]->cuboid_length=5;
  // node[0]->cuboid_height=5;
  // node[0]->cuboid_breadth=5;
  // node[0]->change_parameters(0, 0, 0, 45, 0, 0);

//front wheel...this is child of handle_with_wheel_across!
  wheel_front->obj_type = 2;
  wheel_front->inRadius=wheel_tyre_radius;
  wheel_front->outRadius=wheel_outer_radius;
  wheel_front->nsides=50;
  wheel_front->rings=50;
  wheel_front->change_parameters(0,-26.5, handle_connect_front_wheel_across_length/2, 0, 0, 0);


//back wheel...this is child of nothing as of now
  wheel_back->obj_type = 2;
  wheel_back->inRadius=wheel_tyre_radius;
  wheel_back->outRadius=wheel_outer_radius;
  wheel_back->nsides=50;  
  wheel_back->rings=50;
  wheel_back->change_parameters(50, 0, 0, 0, 0, 0);

//the spokes
for(int i=0; i<9; i++){
  spoke_front[i]->obj_type = 0;
  spoke_front[i]->base=spoke_radius;
  spoke_front[i]->top=spoke_radius;
  spoke_front[i]->height=spoke_length;
  spoke_front[i]->slices=50;
  spoke_front[i]->stacks=10;
  spoke_front[i]->change_preparameters(2,0,0);
  spoke_front[i]->change_parameters(0,0,0,90,40*i,0);
  spoke_front[i]->set_color(0.6,0.6,0.6);             //silverish color

  spoke_front_extra[i]->obj_type = 0;
  spoke_front_extra[i]->base=extra_spoke_radius;
  spoke_front_extra[i]->top=extra_spoke_radius;
  spoke_front_extra[i]->height=extra_spoke_length;
  spoke_front_extra[i]->slices=50;
  spoke_front_extra[i]->stacks=10;
  //spoke_front_extra[i]->change_preparameters(2,0,0);
  spoke_front_extra[i]->change_parameters(0,0,21,0,0,0);
  spoke_front_extra[i]->set_color(0.855,0.647,0.125);       //goldenrod color

  spoke_back[i]->obj_type = 0;
  spoke_back[i]->base=spoke_radius;
  spoke_back[i]->top=spoke_radius;
  spoke_back[i]->height=spoke_length;
  spoke_back[i]->slices=50;
  spoke_back[i]->stacks=10;
  spoke_back[i]->change_preparameters(2,0,0);
  spoke_back[i]->change_parameters(0,0,0,90,40*i,0);
  spoke_back[i]->set_color(0.6,0.6,0.6);

  spoke_back_extra[i]->obj_type = 0;
  spoke_back_extra[i]->base=extra_spoke_radius;
  spoke_back_extra[i]->top=extra_spoke_radius;
  spoke_back_extra[i]->height=extra_spoke_length;
  spoke_back_extra[i]->slices=50;
  spoke_back_extra[i]->stacks=10;
  //spoke_back_extra[i]->change_preparameters(2,0,0);
  spoke_back_extra[i]->change_parameters(0,0,21,0,0,0);
  spoke_back_extra[i]->set_color(0.855,0.647,0.125);

  spoke_front2[i]->obj_type = 0;
  spoke_front2[i]->base=spoke_radius;
  spoke_front2[i]->top=spoke_radius;
  spoke_front2[i]->height=spoke_length;
  spoke_front2[i]->slices=50;
  spoke_front2[i]->stacks=10;
  spoke_front2[i]->change_preparameters(-2,0,0);
  spoke_front2[i]->change_parameters(0,0,0,90,40*i-10,0);
  spoke_front2[i]->set_color(0.6,0.6,0.6);

  spoke_front2_extra[i]->obj_type = 0;
  spoke_front2_extra[i]->base=extra_spoke_radius;
  spoke_front2_extra[i]->top=extra_spoke_radius;
  spoke_front2_extra[i]->height=extra_spoke_length;
  spoke_front2_extra[i]->slices=50;
  spoke_front2_extra[i]->stacks=10;
  //spoke_front2_extra[i]->change_preparameters(2,0,0);
  spoke_front2_extra[i]->change_parameters(0,0,21,0,0,0);
  spoke_front2_extra[i]->set_color(0.855,0.647,0.125);

  spoke_back2[i]->obj_type = 0;
  spoke_back2[i]->base=spoke_radius;
  spoke_back2[i]->top=spoke_radius;
  spoke_back2[i]->height=spoke_length;
  spoke_back2[i]->slices=50;
  spoke_back2[i]->stacks=10;
  spoke_back2[i]->change_preparameters(-2,0,0);
  spoke_back2[i]->change_parameters(0,0,0,90,40*i-10,0);
  spoke_back2[i]->set_color(0.6,0.6,0.6);

  spoke_back2_extra[i]->obj_type = 0;
  spoke_back2_extra[i]->base=extra_spoke_radius;
  spoke_back2_extra[i]->top=extra_spoke_radius;
  spoke_back2_extra[i]->height=extra_spoke_length;
  spoke_back2_extra[i]->slices=50;
  spoke_back2_extra[i]->stacks=10;
  //spoke_back2_extra[i]->change_preparameters(2,0,0);
  spoke_back2_extra[i]->change_parameters(0,0,21,0,0,0);
  spoke_back2_extra[i]->set_color(0.855,0.647,0.125);
}

//the wheel axes
  wheel_axis_f->obj_type=0;
  wheel_axis_f->base=bar_radius;
  wheel_axis_f->top=bar_radius;
  wheel_axis_f->height=wheel_axis_length;
  wheel_axis_f->slices=50;
  wheel_axis_f->stacks=10;
  wheel_axis_f->change_parameters(0,0,-wheel_axis_length/2,0,0,0);

  wheel_axis_b->obj_type=0;
  wheel_axis_b->base=bar_radius;
  wheel_axis_b->top=bar_radius;
  wheel_axis_b->height=wheel_axis_length;
  wheel_axis_b->slices=50;
  wheel_axis_b->stacks=10;
  wheel_axis_b->change_parameters(0,0,-wheel_axis_length/2,0,0,0);

//handle of the cycle
  handle_connect_with_frame->obj_type=0;
  handle_connect_with_frame->base=bar_radius;
  handle_connect_with_frame->top=bar_radius;
  handle_connect_with_frame->height=handle_connect_with_frame_length;
  handle_connect_with_frame->slices=50;
  handle_connect_with_frame->stacks=10;
  handle_connect_with_frame->change_parameters(-30,26.5,0,-90,25,0);
  handle_connect_with_frame->set_color(1,0,0);    

  handlebar_connector->obj_type=0;
  handlebar_connector->base=bar_radius;
  handlebar_connector->top=bar_radius;
  handlebar_connector->height=handlebar_connector_length;
  handlebar_connector->slices=50;
  handlebar_connector->stacks=10;
  handlebar_connector->change_preparameters(0,0,0);
  handlebar_connector->change_parameters(0,0,handle_connect_with_frame->height,0,-90,0);
  handlebar_connector->set_color(0,1,0);  

  handlebar_connector_across->obj_type=0;
  handlebar_connector_across->base=bar_radius;
  handlebar_connector_across->top=bar_radius;
  handlebar_connector_across->height=handlebar_connector_across_length;
  handlebar_connector_across->slices=50;
  handlebar_connector_across->stacks=10;
  handlebar_connector_across->change_preparameters(0,0,-handlebar_connector_across->height/2);
  handlebar_connector_across->change_parameters(0,0,handlebar_connector->height,90,0,0);
  handlebar_connector_across->set_color(0,1,0);   

  handlebar_left->obj_type=0;
  handlebar_left->base=bar_radius;
  handlebar_left->top=bar_radius;
  handlebar_left->height=handlebar_handle_length;
  handlebar_left->slices=50;
  handlebar_left->stacks=10;
  handlebar_left->change_parameters(0,0,handlebar_connector_across->height,0,0,0);
  handlebar_left->set_color(0,0,0);

  handlebar_right->obj_type=0;
  handlebar_right->base=bar_radius;
  handlebar_right->top=bar_radius;
  handlebar_right->height=handlebar_handle_length;
  handlebar_right->slices=50;
  handlebar_right->stacks=10;
  handlebar_right->change_parameters(0,0,-handlebar_right->height,0,0,0);
  handlebar_right->set_color(0,0,0);

  handle_connect_front_wheel_across->obj_type=0;
  handle_connect_front_wheel_across->base=bar_radius;
  handle_connect_front_wheel_across->top=bar_radius;
  handle_connect_front_wheel_across->height=handle_connect_front_wheel_across_length;
  handle_connect_front_wheel_across->slices=50;
  handle_connect_front_wheel_across->stacks=10;
  handle_connect_front_wheel_across->change_preparameters(0,0,-handle_connect_front_wheel_across->height/2);
  handle_connect_front_wheel_across->change_parameters(0,0,0,90,0,0);
  handle_connect_front_wheel_across->set_color(0,0,0);  

  handle_connect_front_wheel_left->obj_type=0;
  handle_connect_front_wheel_left->base=bar_radius;
  handle_connect_front_wheel_left->top=bar_radius;
  handle_connect_front_wheel_left->height=handle_connect_front_wheel_length;
  handle_connect_front_wheel_left->slices=50;
  handle_connect_front_wheel_left->stacks=10;
  //handle_connect_front_wheel_left->change_preparameters(0,0,0);
  handle_connect_front_wheel_left->change_parameters(0,0,handle_connect_front_wheel_across->height,90,0,0);
  handle_connect_front_wheel_left->set_color(0,1,0); 

  handle_connect_front_wheel_right->obj_type=0;
  handle_connect_front_wheel_right->base=bar_radius;
  handle_connect_front_wheel_right->top=bar_radius;
  handle_connect_front_wheel_right->height=25.5;
  handle_connect_front_wheel_right->slices=50;
  handle_connect_front_wheel_right->stacks=10;
  //handle_connect_front_wheel_right->change_preparameters(0,0,0);
  handle_connect_front_wheel_right->change_parameters(0,0,0,90,0,0);
  handle_connect_front_wheel_right->set_color(0,1,0);   

//trial nodes
  // HNode *cylin = new HNode(NULL);
  // node[0]->add_child(cylin);
  // cylin->obj_type = 0;
  // cylin->base=0.5;
  // cylin->top=0.5;
  // cylin->height=22;
  // cylin->slices=50;
  // cylin->stacks=10;
  // //cylin->change_preparameters(1,-3,0);
  // cylin->change_parameters(0,0,0,0,0,0);

  //Child Nodes
  // frame[0] = new HNode(node[0],36,v_positions,v_colors);
  // frame[0]->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
  // wheel_front = new HNode(frame[0],36,v_positions,v_colors);
  // wheel_front->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);

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