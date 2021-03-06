#ifndef OPENGLINTERFACEI_H
#define OPENGLINTERFACEI_H

#include "OpenGLSymbols.h"
#include "OpenGLfunctions.h"
#include "OpenGLFunctor.h"
#include "OpenGL.h"

#include <Triangle.h>

extern GLfloat cam_x;  //camera position
extern GLfloat cam_y;
extern GLfloat cam_z;

extern GLfloat lookat_x;  // look at
extern GLfloat lookat_y;
extern GLfloat lookat_z;
void MakeLeaveTable();
void MakeWireModel(float radius,float lngth);

template <class TS, class BUD, class S>
void MakeLeaveList(Tree<TS,BUD> &tree, int xsize, int ysize)
{
        MakeLeaveTable();


	if (glIsList(FOLIAGE))
		glDeleteLists(FOLIAGE, 1);

	glPushMatrix();
	glNewList(FOLIAGE, GL_COMPILE);	
	UseTextures();


	glEndList();
	glPopMatrix();

	//DrawLeavesFunctor<TS, BUD> leaves_functor(xsize, ysize);
		//ForEach(tree, leaves_functor);

	glPushMatrix();
	glNewList(LGMFOLIAGE, GL_COMPILE);
	DrawLignumLeavesFunctor<TS,BUD,S> leaves_functor;
	ForEach(tree, leaves_functor);		
	glEndList();
	glPopMatrix();
}

template <class TS,class BUD>
void MakeNeedlesList(Tree<TS,BUD> &tree)
{

        if (glIsList(NEEDLES_TEX))
                glDeleteLists(NEEDLES_TEX, 1);

        glPushMatrix();
        glNewList(NEEDLES_TEX, GL_COMPILE);     
        UseTextures();
        DrawNeedlesFunctor<TS, BUD> needles_functor;
        ForEach(tree, needles_functor);
                
        glEndList();
        glPopMatrix();
}


template <class TS,class BUD>
void ForestNeedles(Tree<TS,BUD> &tree)
{
  glPushMatrix();
  UseTextures();
  DrawNeedlesFunctor<TS, BUD> needles_functor;
  ForEach(tree, needles_functor);
  glPopMatrix();               
}


template <class TS,class BUD>
void ForestLeaves(Tree<TS,BUD> &tree,int xsize, int ysize)
{
  glPushMatrix();
  UseTextures();
  DrawLeavesFunctor<TS, BUD> leaves_functor(xsize, ysize);
  ForEach(tree, leaves_functor);
  glPopMatrix();
}

template <class TS,class BUD>
void MakeBudList(Tree<TS,BUD> &tree, bool alive)
{
 
  glPushMatrix();
  DrawBudFunctor<TS,BUD> budsfunctor;

  if (alive)
    {
      if (glIsList(BUDS_ALIVE))
	glDeleteLists(BUDS_ALIVE, 1);
      glNewList(BUDS_ALIVE, GL_COMPILE);
      budsfunctor.mode = buds_alive;
    }
  else
    {
      if (glIsList(BUDS_DEAD))
	glDeleteLists(BUDS_DEAD, 1);
      glNewList(BUDS_DEAD, GL_COMPILE);
      budsfunctor.mode = buds_dead;
    }

  ForEach(tree, budsfunctor);
  glEndList();
  glPopMatrix();
}


template <class TS,class BUD>
void MakeForestTree(Tree<TS,BUD> &tree)
{
  glPushMatrix();
  
  DrawStemFunctor<TS,BUD> stemfunctor;
  stemfunctor.min_rad = 0;
  stemfunctor.max_rad = 999;
  ForEach(tree, stemfunctor);
  
  glPopMatrix();
}

template <class TS,class BUD>
void MakeTreeList(Tree<TS,BUD> &tree, LGMdouble limit)
{
  
	if (glIsList(TREE_BIG))
		glDeleteLists(TREE_BIG, 1);
	if (glIsList(TREE_SMALL))
		glDeleteLists(TREE_SMALL, 1);
	if (glIsList(ROOT_LIST))
		glDeleteLists(ROOT_LIST, 1);
	
  
	cout << "MakeTreeList22:tehdaan puu" << endl;

	glPushMatrix();
	glNewList(TREE_BIG, GL_COMPILE);
	DrawStemFunctor<TS,BUD> stemfunctor;
	stemfunctor.min_rad = limit;
	stemfunctor.max_rad = 999;
	ForEach(tree, stemfunctor);
	glEndList();
	glPopMatrix();


	glPushMatrix();
	glNewList(TREE_SMALL, GL_COMPILE);
	stemfunctor.min_rad = 0;
	stemfunctor.max_rad = limit;
	ForEach(tree, stemfunctor);
	glEndList();
	glPopMatrix();


	glPushMatrix();
	glNewList(ROOT_LIST, GL_COMPILE);
	DrawRootFunctor<Tree<TS,BUD> > rootfunctor;
	ForEach(GetRootAxis(tree), rootfunctor);
	glEndList();
	glPopMatrix();

}


inline void SetViewPort()
{
	gluLookAt (cam_x, cam_y, cam_z,				   // camera x,y,z  
			   lookat_x, lookat_y, lookat_z,	   // look at x,y,z    
			   0.0, 0.0, 1.0);					   // which way up 	
}

template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DrawWireModelFunctor<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS *>(tc))
	{  			
	  LGMdouble radius = GetValue(*ts, LGAR);
	
	  //cout << "radius " << radius << endl;

	      float length;
	      float radius_top;
	      float rot_x;
	      float rot_y;
	      float rot_angle;

	      Point position;
	      PositionVector direction = GetDirection(*ts);

	      length = GetValue(*ts, LGAL); 
			
	      radius_top = GetValue(*ts, LGARTop);
	      position = GetPoint(*ts);
		
	      direction.normalize();
	      rot_x = -1*direction.getVector()[1];
	      rot_y =    direction.getVector()[0];
	      rot_angle = (360/(2*PI_VALUE))*acos((double)direction.getVector()[2]);
	      glPushMatrix();
	      glTranslatef(position.getX(), position.getY(), position.getZ());
	      if (rot_angle == 180.0){
		rot_y = 1.0;
	      }
	      glRotatef( rot_angle, rot_x, rot_y, 0);
	      //   MakeWireModel(0.05, 0.1); 
              MakeWireModel(radius,length);
	      //     cout << "makin a cylinder. Radius:" << radius << "Height "<< length << ".  Position "<< position << endl; 
	      glPopMatrix();
			
	    
		
	} 
      return tc;
    }


#endif
