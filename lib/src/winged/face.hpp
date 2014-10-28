#ifndef DILAY_WINGED_FACE
#define DILAY_WINGED_FACE

#include <glm/fwd.hpp>
#include "id.hpp"
#include "macro.hpp"

class AdjEdges;
class AdjVertices;
class AdjFaces;
class PrimTriangle;
class OctreeNode;
class WingedEdge;
class WingedVertex;
class WingedMesh;

class WingedFace {
  public:                      
    WingedFace ();
    WingedFace (const Id&, WingedEdge*);
    WingedFace (const WingedFace&)  = default;
    WingedFace (      WingedFace&&) = default;

    const Id&              id              () const { return this->_id.id (); }
    WingedEdge*            edge            () const { return this->_edge; }
    OctreeNode*            octreeNode      () const { return this->_octreeNode; }
    unsigned int           index           () const { return this->_index; }

    void                   edge            (WingedEdge*  e) { this->_edge       = e; }
    void                   octreeNode      (OctreeNode*  n) { this->_octreeNode = n; }
    void                   index           (unsigned int i) { this->_index      = i; }
    void                   writeIndices    (WingedMesh&);
    PrimTriangle           triangle        (const WingedMesh&) const;
    WingedVertex&          firstVertex     () const;
    WingedVertex&          secondVertex    () const;
    WingedVertex&          thirdVertex     () const;
    unsigned int           numEdges        () const;
    glm::vec3              normal          (const WingedMesh&) const;
    bool                   isDegenerated   (const WingedMesh&) const;

    WingedEdge*            longestEdge            (const WingedMesh&, float*) const;
    float                  longestEdgeLengthSqr   (const WingedMesh&) const;
    bool                   isTriangle             () const;
    float                  incircleRadiusSqr      (const WingedMesh& mesh) const;

    AdjEdges               adjacentEdges          (WingedEdge&) const;
    AdjEdges               adjacentEdges          ()            const;
    AdjVertices            adjacentVertices       (WingedEdge&) const;
    AdjVertices            adjacentVertices       ()            const;
    AdjFaces               adjacentFaces          (WingedEdge&) const;
    AdjFaces               adjacentFaces          ()            const;

    SAFE_REF_CONST  (WingedEdge, edge)
    SAFE_REF_CONST  (OctreeNode, octreeNode)
    SAFE_REF2_CONST (WingedEdge, longestEdge, const WingedMesh&, float*)
  private:
    const IdObject  _id;
    WingedEdge*     _edge;
    OctreeNode*     _octreeNode;
    unsigned int    _index;
};

#endif
