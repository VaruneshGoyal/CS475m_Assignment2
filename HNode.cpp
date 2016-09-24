#include "HNode.hpp"

void vertexcopy(float *src,float *dest){
  dest[0]=src[0];
  dest[1]=src[1];
  dest[2]=src[2];
  dest[3]=src[3];
}

HNode::HNode(HNode* par){
  tx = 0;
  ty = 0;
  tz = 0;
  rx = 0;
  ry = 0;
  rz = 0;

  if(par!=NULL){
    parent=par;
    parent->add_child(this);
  }

  obj_type = -1;
  quad  = gluNewQuadric();
  base = inRadius = 0;
  top = outRadius = 0;
  height = 0;
  slices = nsides = 0;
  stacks = rings = 0;
  cuboid_height = cuboid_length = cuboid_breadth = 0;
}

void HNode::add_child(HNode *child){
  children.push_back(child);
}

void HNode::render(){
  //Translate the origin
  glTranslatef(tx,ty,tz);
  //Rotate at translated origin
  glRotatef(rx, 1.0, 0.0, 0.0);
  glRotatef(ry, 0.0, 1.0, 0.0);
  glRotatef(rz, 0.0, 0.0, 1.0);

  if(obj_type == 0){
    // glu
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluCylinder(quad, base, top, height, slices, stacks);
  }
  else if(obj_type == 1){
    //cuboid
    glBegin(GL_QUADS);
      glBegin(GL_QUADS);
 
      //Front
      glNormal3f(0.0f, 0.0f, 1.0f);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, 0.0f, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, cuboid_height, cuboid_breadth);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, cuboid_height, cuboid_breadth);
   
      //Right
      glNormal3f(1, 0, 0);
      glVertex3f(cuboid_length, 0.0f, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, 0, 0);
      //glNormal3f(1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, cuboid_height, 0);
      //glNormal3f(1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, cuboid_height, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, 1.0f);
   
      //Back
      glNormal3f(0.0f, 0.0f, -1.0f);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, 0, 0);
      glVertex3f(0, cuboid_height, 0);
      glVertex3f(cuboid_length, cuboid_height, 0);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, 0, 0);
   
      //Left
      glNormal3f(-1.0f, 0.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(0, 0.0f, cuboid_breadth);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(0, cuboid_height, cuboid_breadth);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, cuboid_height, 0);

      //top
      glNormal3f(0.0f, 1.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, cuboid_height, 0);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, cuboid_height, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, cuboid_height, cuboid_breadth);
      //glNormal3f(1.0f, 0.0f, -1.0f);
      glVertex3f(cuboid_length, cuboid_height, 0);
   
      //bottom
      glNormal3f(0.0f, -1.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, 0.0f, 0.0f);
      //glNormal3f(-1.0f, 0.0f, 1.0f);
      glVertex3f(cuboid_length, 0.0f, cuboid_breadth);
      //glNormal3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(0, 0, cuboid_breadth);
 
    glEnd();
  }
  else if(obj_type == 2){
    glutSolidTorus(inRadius, outRadius, nsides, rings);
  }
  else{
    //do nothing
  }
}



void HNode::change_parameters(float tx,float ty,float tz,float rx,float ry,float rz){
  this->tx=tx;
  this->ty=ty;
  this->tz=tz;
  this->rx=rx;
  this->ry=ry;
  this->rz=rz;
}

void HNode::render_tree(){
  glPushMatrix();
  render();
  for(int i=0;i<children.size();i++){
    children[i]->render_tree();
  }
  glPopMatrix();
}