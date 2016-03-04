// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#include <iostream>

//#include <hpp/fcl/BVH/BVH_model.h>
//#include <hpp/fcl/shape/geometric_shapes.h>

#include <hpp/util/debug.hh>
//#include <hpp/model/collision-object.hh>
//#include <hpp/corbaserver/server.hh>
#include "affordance.impl.hh"

namespace hpp
{
  namespace corbaServer
  {
    namespace impl
    {
      namespace 
      {
        Affordance::Affordance () : problemSolver_ (0x0) {}
  
        void Affordance::setProblemSolver
        (const ProblemSolverPtr_t& problemSolver)
        {
  	  problemSolver_ = problemSolver;
        }
	
	void Affordance::testFunction ()
	{
	  std::cout << "Test successful!!" << std::endl;
	}

      }
    } // namespace impl
  } // namespace wholebodyStep
} // namespace hpp