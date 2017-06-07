// Copyright (C) 2016 by Anna Seppala.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#include <hpp/util/exception.hh>
#include <hpp/util/debug.hh>
#include "hpp/corbaserver/affordance/server.hh"
#include "affordance.impl.hh"

namespace hpp
{
  namespace affordanceCorba
  {
    Server::Server (int argc, const char* argv[], bool multiThread,
		    const std::string& poaName) :
      impl_ (new corba::Server <impl::Afford>
	     (argc, argv, multiThread, poaName)) {}
    Server::~Server () { delete impl_;}
    void Server::setProblemSolverMap (hpp::corbaServer::ProblemSolverMapPtr_t psMap)
    {
      impl_->implementation ().setProblemSolverMap (psMap);
    }

    /// Start corba server
    void Server::startCorbaServer(const std::string& contextId,
				  const std::string& contextKind,
				  const std::string& objectId,
				  const std::string& objectKind)
    {
      if (impl_->startCorbaServer(contextId, contextKind, objectId, objectKind)
	  != 0) {
	HPP_THROW_EXCEPTION (hpp::Exception, "Failed to start corba server.");
      }
    }
  } // namespace affordanceCorba
} // namespace hpp
