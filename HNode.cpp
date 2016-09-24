#include "HNode.hpp"



//agscvx<sdhvcjdv

// void vertexcopy(float *src,float *dest){
  dest[0]=src[0];
  dest[1]=src[1];
}

HNode::HNode(HNode* parent){
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

  obj = 0;
  quad  = gluNewQuadric();
  base_inRadius = 0;
  top_outRadius = 0;
  height = 0;
  slices_nsides = 0;
  stacks_rings = 0;
}

// HNode::HNode(HNode* par, int num_v, float pos_v4[][4],  float col_v4[][4]){
//   if(par!=NULL){
//     parent=par;
//     parent->add_child(this);
//   }
//   num_vertices=num_v;
//   vertex_pos = new float*[num_vertices];
//   vertex_col = new float*[num_vertices];
//   for(int i=0;i<num_v;i++){
//     vertex_pos[i]=new(float[4]);
//     vertexcopy(pos_v4[i],vertex_pos[i]);

//     vertex_col[i]=new(float[4]);
//     vertexcopy(col_v4[i],vertex_col[i]);
//   }
//   tx=ty=tz=rx=ry=rz=0;
// }

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

  // glBegin(GL_TRIANGLES);
  // for (int i=0;i<num_vertices;i++){
  //   glColor3fv(vertex_col[i]);
  //   glVertex3fv(vertex_pos[i]);
  // }
  // glEnd();

  render_function();
   // = (void*) render
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
