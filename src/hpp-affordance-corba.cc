// Copyright (C) 2016 by Anna Seppala.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#include <iostream>
#include <hpp/util/debug.hh>
#include "hpp/corbaserver/server.hh"
#include <hpp/corbaserver/affordance/server.hh>
#include <hpp/corbaserver/problem-solver-map.hh>
#include <hpp/core/problem-solver.hh>
typedef hpp::affordanceCorba::Server AffordanceServer;
typedef hpp::corbaServer::Server CorbaServer;
typedef hpp::affordanceCorba::ProblemSolverPtr_t ProblemSolverPtr_t;
typedef hpp::affordanceCorba::ProblemSolver ProblemSolver;

int
main (int argc, const char* argv[])
{
  ProblemSolverPtr_t problemSolver = ProblemSolver::create ();
  CorbaServer corbaServer (problemSolver, argc,
			   const_cast<const char**> (argv), true);
  AffordanceServer affServer (argc, argv, true);
  affServer.setProblemSolverMap (corbaServer.problemSolverMap());

  try {
    corbaServer.startCorbaServer ();
    hppDout (info, "successfully started hpp-corbaserver");
  } catch (const std::exception& exc) {
    hppDout (error, "Failed to start hpp-corbaserver");
  }
  try {
    affServer.startCorbaServer ("hpp", "corbaserver",
				"affordanceCorba", "affordance");

    hppDout (info, "Successfully started corba server for affordance");
  } catch (const std::exception& exc) {
    hppDout (error, "failed to start corba server for affordance");
  }
  corbaServer.processRequest(true);
}
