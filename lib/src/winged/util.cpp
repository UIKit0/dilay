#include <glm/glm.hpp>
#include <iostream>
#include "../util.hpp"
#include "octree.hpp"
#include "primitive/triangle.hpp"
#include "winged/edge.hpp"
#include "winged/face.hpp"
#include "winged/mesh.hpp"
#include "winged/util.hpp"
#include "winged/vertex.hpp"

void WingedUtil :: printStatistics (const WingedMesh& mesh, const WingedVertex& v) {
  std::cout   << "Vertex "               << v.index       () 
              << "\n\tposition:\t"       << v.position    (mesh)
              << "\n\tedge:\t\t"         << v.edge        ()->index ();
    std::cout << "\n\tnormal:\t\t"       << v.savedNormal (mesh);
  std::cout   << std::endl;
}

void WingedUtil :: printStatistics (const WingedEdge& e) {
  auto maybeEdgeIndex = [] (WingedEdge* edge) {
    return bool (edge) ? std::to_string (edge->index ())
                       : std::string ("NULL");
  };
  auto maybeFaceIndex = [] (WingedFace* face) {
    return bool (face) ? std::to_string (face->index ())
                       : std::string ("NULL");
  };
  auto maybeVertexIndex = [] (WingedVertex* vertex) {
    return bool (vertex) ? std::to_string (vertex->index ())
                         : std::string ("NULL");
  };

  std::cout << "Edge " << e.index () 
    << "\n\tvertex 1:\t\t"        << maybeVertexIndex (e.vertex1          ())
    <<   "\tvertex 2:\t\t"        << maybeVertexIndex (e.vertex2          ())
    << "\n\tleft face:\t\t"       << maybeFaceIndex   (e.leftFace         ())
    <<   "\tright face:\t\t"      << maybeFaceIndex   (e.rightFace        ())
    << "\n\tleft predecessor:\t"  << maybeEdgeIndex   (e.leftPredecessor  ())
    <<   "\tleft successor:\t\t"  << maybeEdgeIndex   (e.leftSuccessor    ())
    << "\n\tright predecessor:\t" << maybeEdgeIndex   (e.rightPredecessor ())
    <<   "\tright successor:\t"   << maybeEdgeIndex   (e.rightSuccessor   ())
    << std::endl;
}

void WingedUtil :: printStatistics (const WingedFace& f) {
  std::cout   << "Face "                << f.index () 
              << "\n\tedge:\t\t\t"      << f.edgeRef ().index ()
              << "\n\toctree node:\t\t" << f.octreeNode ()
              << std::endl;
}

void WingedUtil :: printStatistics (const WingedMesh& mesh, bool printAll) {
  std::cout << "Mesh:\t\t\t\t"              << mesh.index ()       << std::endl;
  std::cout << "\tNumber of vertices:\t"    << mesh.numVertices () << std::endl;
  std::cout << "\tNumber of edges:\t"       << mesh.numEdges ()    << std::endl;
  std::cout << "\tNumber of faces:\t"       << mesh.numFaces ()    << std::endl;
  std::cout << "\tNumber of indices:\t"     << mesh.numIndices ()  
            << " (" << mesh.numIndices () / 3  << ")" << std::endl;

  if (printAll) {
    mesh.forEachVertex ([&mesh] (const WingedVertex& v) { 
      WingedUtil::printStatistics (mesh,v); 
    });

    mesh.forEachEdge ([] (const WingedEdge& e) {
      WingedUtil :: printStatistics (e);
    });

    mesh.octree ().forEachFace ([] (const WingedFace& face) {
      WingedUtil :: printStatistics (face);
    });
  }
  WingedUtil::printStatistics (mesh.octree ());
}

void WingedUtil :: printStatistics (const Octree& octree) {
  OctreeStatistics oStats = octree.statistics ();
  std::cout << "Octree:"
            << "\n\tnum nodes:\t\t"           << oStats.numNodes
            << "\n\tnum faces:\t\t"           << oStats.numFaces
            << "\n\tnum degenerated faces:\t" << oStats.numDegeneratedFaces
            << "\n\tnum free face-indices:\t" << oStats.numFreeFaceIndices
            << "\n\tmax faces per node:\t"    << oStats.maxFacesPerNode
            << "\n\tmin depth:\t\t"           << oStats.minDepth
            << "\n\tmax depth:\t\t"           << oStats.maxDepth
            << "\n\tfaces per node:\t\t"      << float (oStats.numFaces) / float (oStats.numNodes) 
            << std::endl;

  for (OctreeStatistics::DepthMap::value_type& e : oStats.numNodesPerDepth) {
    std::cout << "\t" << e.second << "\tnodes at depth\t" << e.first << std::endl;
  }
  for (OctreeStatistics::DepthMap::value_type& e : oStats.numFacesPerDepth) {
    std::cout << "\t" << e.second << "\tfaces at depth\t" << e.first << std::endl;
  }
}
