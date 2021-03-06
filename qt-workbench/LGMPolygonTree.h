#ifndef LGMPOLYGONTREE_H
#define LGMPOLYGONTREE_H
class Ellipse;
#include <list>
//#include <GLDrawer.h>
#include <BSPPolygon.h>
#include <BSPPolygonMaterial.h>
#include <SceneObject.h>
#include <QHash>
#include <QMultiHash>
#include <Lignum.h>

using namespace Lignum;
using namespace cxxadt;

#include <VisualizationParameters.h>

template <class TS, class BUD=DefaultBud<TS>, class S=cxxadt::Ellipse>
class PolygonTreeBuilder {
  public:
  PolygonTreeBuilder(VisualizationParameters params,
		     QHash<TreeCompartment<TS,BUD>*, int> compartmentHash,
		     QHash<BroadLeaf<S>*, int> leafHash):
  parameters(params), objectIndexForTreeCompartment(compartmentHash),
  objectIndexForLeaf(leafHash) { sceneObjects = new QMultiHash<int, SceneObject*>(); }
  QMultiHash<int, SceneObject*>* getSceneObjects();
  BSPPolygonSet* operator() (BSPPolygonSet* polygons, TreeCompartment<TS,BUD>* tc) const ;
  
  private:
  
  BSPPolygonSet*  makeCylinder(double radius,
			       double height,
			       Point point,
			       PositionVector direction,
			       bool drawBottom,
			       bool drawTop,
			       SceneObject* object,
			       int r_detail,
			       int y_detail) const;

  BSPPolygonSet* makeFoliage(double radius, double height, Point point, PositionVector direction,
			     int f_detail, int s_detail, double fmass, double spacing, SceneObject* object) const;
  BSPPolygonSet* makePetiole(Point sp, Point ep, int detail, double radius, SceneObject* object) const;
  BSPPolygonSet* makeTriangleLeaf(Point lc, Point rc, Point ac, bool use_tex, SceneObject* object) const;
  BSPPolygonSet* makeEllipseLeaf(const cxxadt::Ellipse* ellipse, int detail, bool use_tex, SceneObject* object) const;
  BSPPolygonSet* makeBud(Point point, PositionVector direction, int la_detail, int lo_detail, double size, SceneObject* object) const;

  //  mutable list<CylinderVolume>* cylinders;
  VisualizationParameters parameters;
  mutable QMultiHash<int, SceneObject*>* sceneObjects;
  QHash<TreeCompartment<TS,BUD>*, int> objectIndexForTreeCompartment;
  QHash<BroadLeaf<S>*, int> objectIndexForLeaf;

};


template <class TS, class BUD=DefaultBud<TS>, class S=cxxadt::Ellipse>
class LGMPolygonTree {
public:
  LGMPolygonTree() { }
  BSPPolygonSet* buildTree(Tree<TS,BUD>& tree, VisualizationParameters params,
			   QHash<TreeCompartment<TS,BUD>*, int> compartmentHash,
			   QHash<BroadLeaf<S>*, int> leafHash);
  QMultiHash<int, SceneObject*>* getSceneObjects();

  private:
  QMultiHash<int, SceneObject*>* s_objects;
};

template <class TS, class BUD, class S>
QMultiHash<int, SceneObject*>* PolygonTreeBuilder<TS,BUD,S>::getSceneObjects() {
  return sceneObjects;
}

template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::operator() (BSPPolygonSet* polygons, TreeCompartment<TS,BUD>*tc) const {
  int object_index = -1;
  if(objectIndexForTreeCompartment.contains(tc))
    object_index = objectIndexForTreeCompartment.value(tc);


  if(BUD* bud = dynamic_cast<BUD*>(tc)) {
    if(parameters.useBuds()) {
      SceneObject* object;
      BSPPolygonMaterial *primary;
      BSPPolygonMaterial *secondary = NULL;
      // Set the appropriate primary color for the bud
      int value = GetValue(*bud, LGAstate);
      if(value == ALIVE)
	primary = parameters.getBudAliveMaterial();
      else if(value == DEAD)
	primary = parameters.getBudDeadMaterial();
      else if(value == DORMANT)
	primary = parameters.getBudDormantMaterial();
      else if(value == FLOWER)
	primary = parameters.getBudFlowerMaterial();
      else
	primary = parameters.getMaterial();

      // Secondary color;
      value = GetValue(*bud, LGAtype);
      if(value == 0)
	secondary = parameters.getDominantMaterial();
      else if(value == 1)
	secondary = parameters.getNondominantMaterial();
      else if(value == 2)
	secondary = parameters.getShootMaterial();
      else if(value == 3)
	secondary = parameters.getShootAboveMaterial();

      object = new SceneObject(primary, secondary, object_index, 0, false);
      sceneObjects->insert(object_index, object);
      BSPPolygonSet* budi = makeBud(GetPoint(*bud), GetDirection(*bud), parameters.getBudLoDetail(),
				    parameters.getBudLaDetail(), parameters.getBudSize(), object);
      polygons->addPolygons(budi);
      delete budi;
    }
  }
  else if(TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)) {
    double radius = GetValue(*ts, LGAR);
    double length = GetValue(*ts, LGAL);
    Point point = GetPoint(*ts);
    PositionVector direction = GetDirection(*ts);
    BSPPolygonMaterial *secondary = NULL;
    int value = GetValue(*ts, LGAtype);
    if(value == 0)
      secondary = parameters.getDominantMaterial();
    else if(value == 1)
      secondary = parameters.getNondominantMaterial();
    else if(value == 2)
      secondary = parameters.getShootMaterial();
    else if(value == 3)
      secondary = parameters.getShootAboveMaterial();  
    
    SceneObject* object = new SceneObject(parameters.getMaterial(), secondary, object_index, parameters.getSegmentTexture(), false);
    sceneObjects->insert(object_index, object);
    BSPPolygonSet* cyl = makeCylinder(radius, length, Point(point.getX(), point.getY(), point.getZ()),
				      PositionVector(direction.getX(), direction.getY(), direction.getZ()),
				      true, true, object,
				      parameters.getSegmentRDetail(), parameters.getSegmentHDetail());
    polygons->addPolygons(cyl);
    delete cyl;
    //    CylinderVolume cylinder(radius, length, Point(point.getX(), point.getY(), point.getZ()),
    //			    PositionVector(direction.getX(), direction.getY(), direction.getZ()),
    //			    parameters.getCylinderRDetail());
    //    cylinders->push_back(cylinder);
    
    if(HwTreeSegment<TS,BUD,S>* hw = dynamic_cast<HwTreeSegment<TS,BUD,S>*>(ts)) {
      list<BroadLeaf<S>*>& ll = GetLeafList(*hw);
      for(typename list<BroadLeaf<S>*>::iterator i = ll.begin(); i != ll.end(); i++) {
	if(objectIndexForLeaf.contains(*i))
	  object_index = objectIndexForLeaf.value(*i);
	const Shape& s = static_cast<const Shape&>(GetShape(**i));
	Petiole p = GetPetiole(**i);
	SceneObject* p_object = new SceneObject(parameters.getPetioleMaterial(), object_index, 0, false);
	sceneObjects->insert(object_index, p_object);
	BSPPolygonSet* petiole = makePetiole(GetStartPoint(p),
					     GetEndPoint(p),
					     parameters.getPetioleDetail(),
					     parameters.getPetioleRadius(),
					     p_object);
	polygons->addPolygons(petiole);
	delete petiole;
	if(const Triangle* t = dynamic_cast<const Triangle*>(&s)) {
	  SceneObject* object;
	  if(parameters.useLeafTextures())
	    object = new SceneObject(parameters.getMaterial(), object_index,
				     parameters.getLeafTexture(), parameters.useBSP());
	  else
	    object = new SceneObject(parameters.getLeafMaterial(), object_index, 0, false);
	  sceneObjects->insert(object_index, object);
	  BSPPolygonSet* leaf = makeTriangleLeaf(t->getLeftCorner(),
						 t->getRightCorner(),
						 t->getApexCorner(),
						 parameters.useLeafTextures(),
						 object);
	  polygons->addPolygons(leaf);
	  delete leaf;
	}
	else if(const cxxadt::Ellipse* e = dynamic_cast<const cxxadt::Ellipse*>(&s)) {
	  SceneObject* object;
	  if(parameters.useLeafTextures())
	    object = new SceneObject(parameters.getMaterial(), object_index,
				     parameters.getLeafTexture(), parameters.useBSP());
	  else 
	    object = new SceneObject(parameters.getLeafMaterial(), object_index, 0, false);
	  sceneObjects->insert(object_index, object);
	  vector<Point> vertices;
	  BSPPolygonSet* leaf = makeEllipseLeaf(e, parameters.getLeafDetail(), parameters.useLeafTextures(), 
						object);
	  polygons->addPolygons(leaf);
	  delete leaf;
	}
      }
    }
    else if(CfTreeSegment<TS,BUD>* cf = dynamic_cast<CfTreeSegment<TS,BUD>*>(ts)) {
      double fmass = GetValue(*cf, LGAWf);
      if(fmass > R_EPSILON) {
	object = new SceneObject(parameters.getMaterial(), object_index,
				 parameters.getFoliageTexture(), parameters.useBSP());
	sceneObjects->insert(object_index, object);
	BSPPolygonSet* foliage = makeFoliage(radius, length, point, direction, parameters.getFoliageDetail(),
					     parameters.getSegmentRDetail(), fmass, parameters.getFoliageSpacing(), object);
	polygons->addPolygons(foliage);
	delete foliage;
      }
    }
    
  }

  return polygons;
}

template <class TS, class BUD, class S>
  BSPPolygonSet* LGMPolygonTree<TS,BUD,S>::buildTree(Tree<TS,BUD>& tree, VisualizationParameters params,
						     QHash<TreeCompartment<TS,BUD>*, int> compartmentHash,
						     QHash<BroadLeaf<S>*, int> leafHash) {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  PolygonTreeBuilder<TS,BUD,S> builder(params, compartmentHash, leafHash);  
  PropagateUp(tree, polygons, builder);
  s_objects = builder.getSceneObjects();

  return polygons;
}

template <class TS, class BUD, class S>
QMultiHash<int, SceneObject*>* LGMPolygonTree<TS,BUD,S>::getSceneObjects() {
  return s_objects;
} 

template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeCylinder(double radius, double height, Point point, PositionVector direction, bool drawBottom, bool drawTop, SceneObject* object, int r_detail, int y_detail) const  {
  double PI = 3.14159265;
  double sine, cosine, sine_next, cosine_next, y, y_next;
  BSPPolygonSet* polygons = new BSPPolygonSet();

  if(radius == 0)
    return polygons;

  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);
  //  vector<Point> vertices(3);
  //vector<Point> t_vertices(3);
  double tex_length = 1;
  //double tex_start = rand()/(double)RAND_MAX;
  
  PositionVector v1, v2, v3, v4;
  double PI2_PER_DETAIL = 2.0*PI/r_detail;
  double TEXL_PER_DETAIL = tex_length/(double)r_detail;
  sine_next = radius*sin(0*PI2_PER_DETAIL);
  cosine_next = radius*cos(0*PI2_PER_DETAIL);

  for(int i = 0; i < r_detail; i++) {
    sine = sine_next;
    cosine = cosine_next;
    sine_next = radius*sin((i+1)*PI2_PER_DETAIL);
    cosine_next = radius*cos((i+1)*PI2_PER_DETAIL);
    double temp1 = TEXL_PER_DETAIL*i;
    double temp2 = TEXL_PER_DETAIL*(i+1);

    for(int j = 0; j < y_detail; j++) {
      y = j / (double)y_detail * height;
      y_next = (j+1) / (double)y_detail * height;
      
      PositionVector v1(sine, y, cosine);
      PositionVector v2(sine, y_next, cosine);
      PositionVector v3(sine_next, y, cosine_next);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
	    
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point(temp1, y/height, 0),
					  Point(temp1, y_next/height, 0),
					  Point(temp2, y/height, 0),
					  object));
      
      v1 = PositionVector(sine_next, y, cosine_next);
      v2 = PositionVector(sine, y_next, cosine);
      v3 = PositionVector(sine_next, y_next, cosine_next);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
	    
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point(temp2, y/height, 0),
					  Point(temp1, y_next/height, 0),
					  Point(temp2, y_next/height, 0),
					  object));
    }
  
    if(drawTop) {
      v1 = PositionVector(sine, height, cosine);
      v2 = PositionVector(0, height, 0);
      v3 = PositionVector(sine_next, height, cosine_next);
      
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  object));
    }
    
    if(drawBottom) {
      v1 = PositionVector(sine, 0, cosine);
      v2 = PositionVector(sine_next, 0, cosine_next);
      v3 = PositionVector(0, 0, 0);
      
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  object));
      
    }

  }
  return polygons;
}

template <class TS, class BUD, class S>
BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeFoliage(double radius, double height, Point point, PositionVector direction,
							   int f_detail, int s_detail, double fmass, double spacing, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();
  if(f_detail == 0 || s_detail == 0)
    return polygons;

  double sine, cosine, sine_next, cosine_next;
  double y, y_next;
  double PI = 3.14159265;
  double needle_length = 11*fmass;

  LGMdouble tex_len = 0.1;
  LGMdouble tex_per_plane = height / tex_len;
  int needles_per_tex = 30;

  int needles_per_plane = static_cast<int>(tex_per_plane * needles_per_tex);
  if (needles_per_plane == 0)
    return polygons;


  int y_detail = (int)(height/spacing);
  
  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);

  Point origo(0,0,0);

  Point p1(radius*sin(0.0), radius*cos(0.0), 0);
  Point p2(radius*sin(1.0/s_detail*2*PI), radius*cos(1.0/s_detail*2*PI), 0);
  radius = PositionVector(0.5*(p1+p2)).length();

  double PI2_PER_FDETAIL = 2*PI/(double)f_detail;
  for(int j = 0; j < y_detail; j++) {
    y = j/(double)y_detail*height;
    y_next = (j+1)/(double)y_detail*height;

    for(int i = 0; i < f_detail; i++) {
      sine = radius*sin(i/PI2_PER_FDETAIL);
      cosine = radius*cos(i/PI2_PER_FDETAIL);
      sine_next = sine*(needle_length+radius)/radius;
      cosine_next = cosine*(needle_length+radius)/radius;

      PositionVector v1(sine, y, cosine);
      PositionVector v2(sine_next, y, cosine_next);
      PositionVector v3(sine, y_next, cosine);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point(1, 0, 0),
					  Point(0, 0, 0),
					  Point(1, 1, 0),
					  object));
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v3)+point,
					  Point(v2)+point,
					  Point(1, 0, 0),
					  Point(1, 1, 0),
					  Point(0, 0, 0),
					  object));

      v1 = PositionVector(sine_next, y, cosine_next);
      v2 = PositionVector(sine_next, y_next, cosine_next);
      v3 = PositionVector(sine, y_next, cosine);
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v2)+point,
					  Point(v3)+point,
					  Point(0, 0, 0),
					  Point(0, 1, 0),
					  Point(1, 1, 0),
					  object));
      
      polygons->addPolygon(new BSPPolygon(Point(v1)+point,
					  Point(v3)+point,
					  Point(v2)+point,
					  Point(0, 0, 0),
					  Point(1, 1, 0),
					  Point(0, 1, 0),
					  object));
    }
  }
  
  return polygons;


}


template <class TS, class BUD, class S>
BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makePetiole(Point sp, Point ep, int detail, double radius, SceneObject* object) const {
  
  BSPPolygonSet* polygons = makeCylinder(radius, PositionVector(sp-ep).length(), sp, PositionVector(ep-sp), false, false, object, detail, 1);

  return polygons;
}

template <class TS, class BUD, class S>
BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeTriangleLeaf(Point lc, Point rc, Point ac, bool use_tex, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();

  if(use_tex) {
    polygons->addPolygon(new BSPPolygon(lc,
					rc,
					ac+0.5*(lc-rc),
					Point(0,0,0),
					Point(1,0,0),
					Point(0,1,0),
					object));
    polygons->addPolygon(new BSPPolygon(lc,
					ac+0.5*(lc-rc),
					rc,
					Point(0,0,0),
					Point(0,1,0),
					Point(1,0,0),
					object));
    polygons->addPolygon(new BSPPolygon(rc,
					ac+0.5*(rc-lc),
					ac+0.5*(lc-rc),
					Point(1,0,0),
					Point(1,1,0),
					Point(0,1,0),
					object));
    polygons->addPolygon(new BSPPolygon(rc,
					ac+0.5*(lc-rc),
					ac+0.5*(rc-lc),
					Point(1,0,0),
					Point(0,1,0),
					Point(1,1,0),
					object));
  }
  else {
    polygons->addPolygon(new BSPPolygon(lc, rc, ac, object));
    polygons->addPolygon(new BSPPolygon(lc, ac, rc, object));
  }
  
  return polygons;

}


template <class TS, class BUD, class S>
  BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeEllipseLeaf(const cxxadt::Ellipse* ellipse, int detail, bool use_tex, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();
  if(use_tex) {
    Point p1(ellipse->getCenterPoint() +
	     Point(ellipse->getSemimajorAxis()*ellipse->x1u()) + 
	     Point(ellipse->getSemiminorAxis()*ellipse->y1u()));
    Point p2(ellipse->getCenterPoint() +
	     Point(ellipse->getSemimajorAxis()*ellipse->x1u()) - 
	     Point(ellipse->getSemiminorAxis()*ellipse->y1u()));
    Point p3(ellipse->getCenterPoint() - 
	     Point(ellipse->getSemimajorAxis()*ellipse->x1u()) + 
	     Point(ellipse->getSemiminorAxis()*ellipse->y1u()));
    Point p4(ellipse->getCenterPoint() -
	     Point(ellipse->getSemimajorAxis()*ellipse->x1u()) - 
	     Point(ellipse->getSemiminorAxis()*ellipse->y1u()));

    polygons->addPolygon(new BSPPolygon(p1, p2, p3,
					Point(1, 1, 0), Point(0, 1, 0), Point(1, 0, 0), object));
    polygons->addPolygon(new BSPPolygon(p3, p2, p4,
					Point(1, 0, 0), Point(0, 1, 0), Point(0, 0, 0), object));

    polygons->addPolygon(new BSPPolygon(p4, p2, p3,
					Point(0, 0, 0), Point(0, 1, 0), Point(1, 0, 0), object));
    polygons->addPolygon(new BSPPolygon(p2, p1, p3,
					Point(0, 1, 0), Point(1, 1, 0), Point(1, 0, 0), object));    
    return polygons;
  }
  // If textures are not used
  else {
    vector<Point> vertices;
    vertices = ellipse->getVertexVector(vertices, detail);

    int size = vertices.size();
    
    //double step = 1.0/(size/2.0 );
    polygons->addPolygon(new BSPPolygon(vertices[0], vertices[size-1], vertices[1], object));
        
    for(int i = 1; i < size/2-1; i++) {
      polygons->addPolygon(new BSPPolygon(vertices[i], vertices[size-i], vertices[size-i-1], object));
      polygons->addPolygon(new BSPPolygon(vertices[i], vertices[size-i-1], vertices[i+1], object));
    }

    polygons->addPolygon(new BSPPolygon(vertices[size/2-1], vertices[size/2+1], vertices[size/2], object));


    polygons->addPolygon(new BSPPolygon(vertices[size/2-1], vertices[size/2], vertices[size/2+1], object));    

    for(int i = size/2-2; i >= 1; i--) {
      polygons->addPolygon(new BSPPolygon(vertices[size-i-1], vertices[i], vertices[i+1],  object));          
      polygons->addPolygon(new BSPPolygon(vertices[i], vertices[size-i-1], vertices[size-i], object));
    }

    polygons->addPolygon(new BSPPolygon(vertices[1], vertices[size-1], vertices[0], object));
    return polygons;
  }
}

template<class TS, class BUD, class S>
BSPPolygonSet* PolygonTreeBuilder<TS,BUD,S>::makeBud(Point point, PositionVector direction, int la_detail, int lo_detail,
						     double scale, SceneObject* object) const {
  BSPPolygonSet* polygons = new BSPPolygonSet();
  double PI = 3.14159265;  
  int i, j;
  double y_scale = 2;
  double z_scale = 0.75;
  PositionVector dir(direction.normalize().getX()/2.0,
		     (1+direction.normalize().getY())/2.0,
		     direction.normalize().getZ()/2.0);
  if(dir.getX() == 0 && dir.getY() == 0 && dir.getZ() == 0)
    dir = PositionVector(1,0,0);
  
  Point origo(0,0,0);
  double PI2_PER_LODETAIL = 2 * PI / lo_detail;
  for (i = 0; i < la_detail; i++) {
    double lat0 = PI * (-0.5 + (double) i / la_detail);
    double z0 = sin(lat0);
    double zr0 = cos(lat0);
    
    double lat1 = PI * (-0.5 + (double) (i + 1) / la_detail);
    double z1 = sin(lat1);
    double zr1 = cos(lat1);
    for (j = 0; j < lo_detail; j++) {
      double lng1 = PI2_PER_LODETAIL * (double)j;
      double lng2 = PI2_PER_LODETAIL * (double)(j + 1);
      double x1 = cos(lng1);
      double y1 = sin(lng1);

      double x2 = cos(lng2);
      double y2 = sin(lng2);
      
      PositionVector v1(scale * (Point(0,y_scale,0) + Point(x1 * zr0, y_scale * y1 * zr0, z_scale * z0)));
      PositionVector v2(scale * (Point(0,y_scale,0) + Point(x1 * zr1, y_scale * y1 * zr1, z_scale * z1)));
      PositionVector v3(scale * (Point(0,y_scale,0) + Point(x2 * zr1, y_scale * y2 * zr1, z_scale * z1)));
      PositionVector v4(scale * (Point(0,y_scale,0) + Point(x2 * zr0, y_scale * y2 * zr0, z_scale * z0)));
      v1 = v1.rotate(origo, dir, PI);
      v2 = v2.rotate(origo, dir, PI);
      v3 = v3.rotate(origo, dir, PI);
      v4 = v4.rotate(origo, dir, PI);

      if(i != la_detail - 1) {
	polygons->addPolygon(new BSPPolygon(point + Point(v2),
					    point + Point(v3),
					    point + Point(v1),
					    object));
      }

      if(i != 0) {
      polygons->addPolygon(new BSPPolygon(point + Point(v3),
					  point + Point(v4),
					  point + Point(v1),
					  object));
      }
				       
      /*polygons->addPolygon(new BSPPolygon(point + Point(scale * x1 * zr0, scale * y1 * zr0, scale * z0),
					  point + Point(scale * x1 * zr1, scale * y1 * zr1, scale * z1),
					  point + Point(scale * x2 * zr1, scale * y2 * zr1, scale * z1),
					  object));
      polygons->addPolygon(new BSPPolygon(point + Point(scale * x2 * zr1, scale * y2 * zr1, scale * z1),
					  point + Point(scale * x2 * zr0, scale * y2 * zr0, scale * z0),
					  point + Point(scale * x1 * zr0, scale * y1 * zr0, scale * z0),
					  object));*/
    }
  }
  return polygons;
}


  
#endif
