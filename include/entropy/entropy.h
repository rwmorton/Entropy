#ifndef __entropy_h__
#define __entropy_h__

//local dependencies

//config
#include <entropy\cfg.h>

//app
#include <entropy\app\App.h>
#include <entropy\app\GLUTWrapper.h>

//spatial
#include <entropy\spatial\tree.h>

//mesh
#include <entropy\mesh\mesh.h>
#include <entropy\mesh\marchingCubes.h>

//game
#include <entropy\game\r2\entity2.h>

//util
#include <entropy\util\algo.h>
#include <entropy\util\glUtil.h>
#include <entropy\util\noise3D.h>

//sys
#include <entropy\sys\timer.h>

//math
#include <entropy\math\math.h>
#include <entropy\math\angle.h>
//points
#include <entropy\math\r2\point2.h>
#include <entropy\math\r3\point3.h>
//vectors
#include <entropy\math\r2\vector2.h>
#include <entropy\math\r3\vector3.h>
//normals
#include <entropy\math\r2\normal2.h>
#include <entropy\math\r3\normal3.h>
//matrices
#include <entropy\math\r2\matrix22.h>
#include <entropy\math\r3\matrix33.h>
#include <entropy\math\r3\matrix44.h>
//quaternion
//transforms
#include <entropy\math\r2\transform2.h>
#include <entropy\math\r3\transform3.h>
//rays
#include <entropy\math\r2\ray2.h>
#include <entropy\math\r3\ray3.h>
//lines
#include <entropy\math\r2\line2.h>
#include <entropy\math\r3\line3.h>

//color
#include <entropy\color\color.h>

//RT (raytracing system)
//core
#include <entropy\RT\core\scene.h>
#include <entropy\RT\core\DG.h>
#include <entropy\RT\core\shape.h>
#include <entropy\RT\core\camera.h>
#include <entropy\RT\core\intersection.h>
//cameras
//
//shapes
#include <entropy\RT\shapes\sphere.h>

//collision
//r2
#include <entropy\collision\r2\intersector2.h>
#include <entropy\collision\r2\contact2.h>
#include <entropy\collision\r2\intersection2.h>
#include <entropy\collision\r2\collisionObject2.h>
#include <entropy\collision\r2\shape2.h>
#include <entropy\collision\r2\circle.h>
//r3
#include <entropy\collision\r3\bbox3.h>

//physics
//r2
#include <entropy\physics\r2\dynamicObject2.h>
#include <entropy\physics\r2\particle2.h>
#include <entropy\physics\r2\rigidBody2.h>
#include <entropy\physics\r2\force2.h>
#include <entropy\physics\r2\contacts2.h>
//r3
#include <entropy\physics\r3\particle3.h>
#include <entropy\physics\r3\particleForceGenerator3.h>
#include <entropy\physics\r3\particleForceRegistry3.h>

//ai
#include <entropy\ai\steeringOutput.h>
#include <entropy\ai\vehicle.h>
#include <entropy\ai\steeringBehaviours.h>

#endif
