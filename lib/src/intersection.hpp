/* This file is part of Dilay
 * Copyright © 2015 Alexander Bau
 * Use and redistribute under the terms of the GNU General Public License
 */
#ifndef DILAY_INTERSECTION
#define DILAY_INTERSECTION

#include <glm/fwd.hpp>
#include "macro.hpp"

class PrimAABox;
class PrimPlane;
class PrimRay;
class PrimSphere;
class PrimTriangle;

class Intersection {
  public:
    DECLARE_BIG6_VIRTUAL (Intersection)

    void                 reset          ();
    bool                 isIntersection () const;
    const glm::vec3&     position       () const;
    const glm::vec3&     normal         () const;
    float                distance       () const;
    bool                 update         (float, const glm::vec3&, const glm::vec3&);

    static Intersection& min            (Intersection&, Intersection&);

  private:
    IMPLEMENTATION
};

namespace IntersectionUtil {
  bool intersects (const PrimSphere&, const glm::vec3&);
  bool intersects (const PrimSphere&, const PrimTriangle&);
  bool intersects (const PrimSphere&, const PrimAABox&);
  bool intersects (const PrimRay&, const PrimSphere&, float*); 
  bool intersects (const PrimRay&, const PrimPlane& , float*); 
  bool intersects (const PrimRay&, const PrimTriangle& , glm::vec3*); 
  bool intersects (const PrimRay&, const PrimAABox&); 
  bool intersects (const PrimPlane&, const PrimAABox&); 
  bool intersects (const PrimPlane&, const PrimTriangle&); 
}

#endif
