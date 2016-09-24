#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <tuple>

#ifndef _HNODE_HPP_
#define _HNODE_HPP_

void vertexcopy(float *src,float *dest);

// A simple class that represents a node in the hierarchy tree
class HNode {
private:
  float tx,ty,tz;		//translation from its origin
  float rx,ry,rz;		//rotation about x, y, z
  // int num_vertices;		//no of vertices
  // float **vertex_pos;	//pointer to array of all vertices
  // float **vertex_col;	//pointer to array of colors of vertices

  std::vector<HNode*> children;		//vector containing pointers to children nodes
  HNode* parent;					//pointer to parent node

  GLUquadric* quad;
  GLdouble base;
  GLdouble inRadius;
  GLdouble top;
  GLdouble outRadius;
  GLdouble height;
  GLint slices;
  GLint nsides;
  GLint stacks;
  GLint rings;

  int obj;
  //0 - cylinder - default
  //1 - cuboid
  //2 - torus

public:
  // HNode (HNode* parent, int num_vertices, float pos_v4[][4],  float col_v4[][4]);		//default constructor of the node
  HNode (HNode* parent);
  void add_child(HNode*);		//function to add a child node to this node
  void render();				//function to render(create) this node
  void change_parameters(float tx,float ty,float tz,float rx,float ry,float rz);		//change parameters of this node - rotate/translate it
  void render_tree();			//function to render the whole tree - this + children (NOT parents)
  // void (*render_function)();

  // void make_cuboid();
  // void make_cylinder();
  // void make_torus();
  //increment/decrement parameters
  // void inc_rx();
  // void inc_ry();
  // void inc_rz();
  // void dec_rx();
  // void dec_ry();
  // void dec_rz();
};

#endif