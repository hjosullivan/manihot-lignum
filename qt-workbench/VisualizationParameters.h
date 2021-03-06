#ifndef VISUALIZATIONPARAMETERS_H
#define VISUALIZATIONPARAMETERS_H

#include <iostream>
#include <BSPPolygonMaterial.h>

using namespace std;

class VisualizationParameters {
 public:
  VisualizationParameters(int segment_r_detail, int segment_h_detail,
			  int leaf_detail,
			  int segment_tex,
			  int leaf_tex,
			  int foliage_tex,
			  BSPPolygonMaterial* material,
			  BSPPolygonMaterial* leafMat,
			  BSPPolygonMaterial* petioleMaterial);
  VisualizationParameters();
  ~VisualizationParameters();
  
  void                  setSegmentTextureFile(string texture);
  void                  setLeafTextureFile(string texture);
  void                  setFoliageTextureFile(string texture);

  string                getSegmentTextureFile() const;
  string                getLeafTextureFile() const;
  string                getFoliageTextureFile() const;

  void                  setSegmentRDetail(int detail);
  void                  setSegmentHDetail(int detail);
  void                  setLeafDetail(int detail);
  void                  setBudLoDetail(int detail);
  void                  setBudLaDetail(int detail);
  void                  setBudSize(double size);
  void                  setFoliageDetail(int detail);
  void                  setFoliageSpacing(double spacing);
  void                  setPetioleDetail(int detail);
  void                  setPetioleRadius(double radius);

  int                   getSegmentRDetail() const ;
  int                   getSegmentHDetail() const ;
  int                   getLeafDetail() const;
  int                   getBudLoDetail() const;
  int                   getBudLaDetail() const;
  double                getBudSize() const;
  int                   getFoliageDetail() const;
  double                getFoliageSpacing() const;
  int                   getPetioleDetail() const;
  double                getPetioleRadius() const;

  void                  setLeafTexture(int texture);
  void                  setFoliageTexture(int texture);
  void                  setSegmentTexture(int texture);
  int                   getSegmentTexture() const ;
  int                   getLeafTexture() const;
  int                   getFoliageTexture() const;

  BSPPolygonMaterial*   getMaterial() const ;
  BSPPolygonMaterial*   getLeafMaterial() const;
  BSPPolygonMaterial*   getPetioleMaterial() const;
  BSPPolygonMaterial*   getBudAliveMaterial() const;
  BSPPolygonMaterial*   getBudDeadMaterial() const;
  BSPPolygonMaterial*   getBudDormantMaterial() const;
  BSPPolygonMaterial*   getBudFlowerMaterial() const;
  BSPPolygonMaterial*   getDominantMaterial() const;
  BSPPolygonMaterial*   getNondominantMaterial() const;
  BSPPolygonMaterial*   getShootMaterial() const;
  BSPPolygonMaterial*   getShootAboveMaterial() const;

  void                  setMaterial(BSPPolygonMaterial* material);
  void                  setLeafMaterial(BSPPolygonMaterial* material);
  void                  setPetioleMaterial(BSPPolygonMaterial* material);
  void                  setBudAliveMaterial(BSPPolygonMaterial* material);
  void                  setBudDeadMaterial(BSPPolygonMaterial* material);
  void                  setBudDormantMaterial(BSPPolygonMaterial* material);
  void                  setBudFlowerMaterial(BSPPolygonMaterial* material);
  void                  setDominantMaterial(BSPPolygonMaterial* material);
  void                  setNondominantMaterial(BSPPolygonMaterial* material);
  void                  setShootMaterial(BSPPolygonMaterial* material);
  void                  setShootAboveMaterial(BSPPolygonMaterial* material);

  void                  setBSPUsage(bool useBSP);
  void                  setLeafTextureUsage(bool useLeafTextures);
  void                  setLeafUsage(bool useLeaves);
  void                  setWireframeUsage(bool useWireframe);
  void                  setLightingUsage(bool useLighting);
  void                  setTexturingUsage(bool useTexturing);
  void                  setBudUsage(bool useBuds);

  bool                  useBSP() const;
  bool                  useLeafTextures() const;
  bool                  useLeaves() const;
  bool                  useWireframe() const;
  bool                  useLighting() const;
  bool                  useTexturing() const;
  bool                  useBuds() const;

 private:
  string segment_texture_file;
  string leaf_texture_file;
  string foliage_texture_file;
  int segment_r_detail;
  int segment_h_detail;
  int leaf_detail;
  int bud_lo_detail;
  int bud_la_detail;
  double bud_size;
  int foliage_detail;
  double foliage_spacing;
  int petiole_detail;
  double petiole_radius;
  int segment_tex;
  int leaf_tex;
  int foliage_tex;
  BSPPolygonMaterial* material;
  BSPPolygonMaterial* leafMaterial;
  BSPPolygonMaterial* petioleMaterial;
  BSPPolygonMaterial* budAliveMaterial;
  BSPPolygonMaterial* budDeadMaterial;
  BSPPolygonMaterial* budDormantMaterial;
  BSPPolygonMaterial* budFlowerMaterial;
  BSPPolygonMaterial* dominantMaterial;
  BSPPolygonMaterial* nondominantMaterial;
  BSPPolygonMaterial* shootMaterial;
  BSPPolygonMaterial* shootAboveMaterial;
  bool use_BSP;
  bool use_leaftex;
  bool use_leaves;
  bool use_buds;
  bool use_wireframe;
  bool use_lighting;
  bool use_texturing;

};

#endif
