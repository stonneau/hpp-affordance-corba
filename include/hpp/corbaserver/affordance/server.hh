// Copyright (C) 2016 by Anna Seppala
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_AFFORDANCE_CORBA_SERVER_HH
# define HPP_AFFORDANCE_CORBA_SERVER_HH

# include <hpp/corba/template/server.hh>
# include <hpp/corbaserver/affordance/fwd.hh>
# include <hpp/corbaserver/affordance/config.hh>

namespace hpp
{
  namespace affordanceCorba
  {
    namespace impl
    {
      class Afford;
    } // namespace impl

    class HPP_AFFORDANCE_CORBA_DLLAPI Server
    {
    public:
      Server (int argc, const char* argv[], bool multiThread = false,
	      const std::string& poaName = "child");

      /// \brief Shutdown CORBA server
      ~Server ();
      /// Set planner that will be controlled by server
      void setProblemSolver (ProblemSolverPtr_t problemSolver);

      void startCorbaServer(const std::string& contextId,
			    const std::string& contextKind,
			    const std::string& objectId,
			    const std::string& objectKind);

    private:
      corba::Server <impl::Afford>* impl_;
      impl::Server* private_;
    };

  } // end of namespace affordanceCorba.
} // end of namespace hpp.
#endif // HPP_AFFORDANCE_CORBA_SERVER_HH
