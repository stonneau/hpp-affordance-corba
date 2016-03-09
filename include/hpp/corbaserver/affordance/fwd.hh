// Copyright (C) 2010 by Anna Seppala, CNRS.
//
// This file is part of the hpp-affordance-corba.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_AFFORDANCE_CORBA_FWD_HH
# define HPP_AFFORDANCE_CORBA_FWD_HH

//FIXME: should be replaced by CORBA base types forward declarations.
# include <omniORB4/CORBA.h>
# include <hpp/fcl/math/vec_3f.h>
# include <hpp/core/fwd.hh>
# include <hpp/affordance/fwd.hh>
namespace fcl {
  template <typename T> class BVHModel;
  class CollisionGeometry;
  class RSS;
  class ShapeBase;
  class Triangle;
}

namespace hpp
{
  namespace affordanceCorba
  {
    class Server;
    class Client;

    typedef core::ProblemSolver ProblemSolver;
    typedef core::ProblemSolverPtr_t ProblemSolverPtr_t;

    typedef fcl::CollisionGeometry CollisionGeometry_t;
    typedef boost::shared_ptr <CollisionGeometry_t> CollisionGeometryPtr_t;
    typedef model::Transform3f Transform3f;
    typedef fcl::BVHModel < fcl::RSS > Polyhedron_t;
    typedef boost::shared_ptr <Polyhedron_t> PolyhedronPtr_t;
    typedef fcl::ShapeBase BasicShape_t;
    typedef boost::shared_ptr <BasicShape_t> BasicShapePtr_t;

    typedef std::map <std::string, BasicShapePtr_t> ShapeMap_t;
    typedef std::map <std::string, std::vector <fcl::Triangle> > TriangleMap_t;
    typedef std::map <std::string, std::vector <fcl::Vec3f> > VertexMap_t;

//    typedef affordance::SupportOperationPtr_t SupportOperationPtr_t;
//    typedef affordance::LeanOperationPtr_t LeanOperationPtr_t;
//    typedef affordance::CollisionObjectPtr_t CollisionObjectPtr_t;
//    typedef affordance::OperationBasePtr_t OperationBasePtr_t;
//    typedef affordance::SemanticsDataPtr_t SemanticsDataPtr_t;
//    typedef affordance::AffordancePtr_t AffordancePtr_t;
//    typedef affordance::AffordanceExtractionPtr_t AffordanceExtractionPtr_t;

    typedef model::matrix_t matrix_t;
    typedef model::vector_t vector_t;
    typedef model::vector3_t vector3_t;
    typedef model::size_type size_type;
    namespace impl
    {
      using CORBA::Boolean;
      using CORBA::Double;
      using CORBA::Short;
      using CORBA::SystemException;
      using CORBA::ULong;
      using CORBA::UShort;

      class Obstacle;
      class Server;
    }
  } // end of namespace affordanceCorba.
} // end of namespace hpp.

#endif //! HPP_AFFORDANCE_CORBA_FWD_HH
