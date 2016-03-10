// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_AFFORDANCE_CORBA_IMPL_HH
# define HPP_AFFORDANCE_CORBA_IMPL_HH
# include <omniORB4/CORBA.h>
# include <hpp/fcl/BVH/BVH_model.h>
# include "hpp/core/problem-solver.hh"
# include "hpp/corbaserver/affordance/fwd.hh"
# include "hpp/affordance/affordance-extraction.hh"
# include "affordance.hh"

namespace hpp
{
  namespace affordanceCorba
  {
    namespace impl
    {
      class Afford : public virtual
      POA_hpp::corbaserver::affordance::Afford
      {
      public:

	      Afford ();

	      void setProblemSolver (const ProblemSolverPtr_t& problemSolver);

	      virtual void testFunction () throw (hpp::Error);

      private:
	      core::ProblemSolverPtr_t problemSolver_;
      }; // class Afford
    } // namespace impl
  } // namespace affordanceCorba
} // namespace hpp

#endif //HPP_AFFORDANCE_CORBA_IMPL_HH
