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

//#include <hpp/fcl/shape/geometric_shapes.h>

#include <hpp/util/debug.hh>
//#include <Eigen/Dense>
//#include <hpp/model/collision-object.hh>
//#include <hpp/corbaserver/server.hh>

#include "hpp/affordance/affordance-extraction.hh"
#include "hpp/affordance/operations.hh"
#include <hpp/model/collision-object.hh>
#include "affordance.impl.hh"

namespace hpp
{
  namespace affordanceCorba
  {
    namespace impl
    {

        Afford::Afford () : problemSolver_ (0x0) {}

        void Afford::setProblemSolver
        (const ProblemSolverPtr_t& problemSolver)
        {
  	      problemSolver_ = problemSolver;
        }

        void Afford::testProblemSolver () throw (hpp::Error)
        {
          if (problemSolver_) {
            std::vector<boost::shared_ptr<Eigen::Matrix<double, -1, 1> > > 
							configs(problemSolver_->goalConfigs());
            std::cout << "problemSolver: goalConfig = " << std::endl;
            for (unsigned int i = 0; i < configs.size (); ++i) {
              std::cout << *(configs[i]) << std::endl;
            }
          }
        }

	      void Afford::affordanceAnalysis (const char* obstacleName) throw (hpp::Error)
	      {
          affordance::SupportOperationPtr_t support (new affordance::SupportOperation());
          affordance::LeanOperationPtr_t lean (new affordance::LeanOperation(0.1));

          affordance::OperationBases_t operations;
          operations.push_back(support);
          operations.push_back(lean);

	        try {
            affordance::SemanticsDataPtr_t aff = affordance::affordanceAnalysis
                ((problemSolver_->obstacle (obstacleName))->fcl (), operations);
 					  std::vector<std::vector<fcl::CollisionObjectPtr_t > > affObjs = 
					  affordance::getAffordanceObjects (aff);
						// add fcl::CollisionObstacles to problemSolver
						addAffObjects (operations, affObjs);
						} catch (const std::exception& exc) {
	          throw Error (exc.what ());
	        }
	      }

				void Afford::addAffObjects (const affordance::OperationBases_t& ops,
					const std::vector<affordance::CollisionObjects_t>& affObjs)
					throw (hpp::Error)
				{
					for (unsigned int opIdx = 0; opIdx < ops.size (); opIdx++)
					{
						problemSolver_->add <affordance::CollisionObjects_t> 
							(ops[opIdx]->affordance_, affObjs[opIdx]);
					}
				}
				
				hpp::floatSeqSeqSeqSeq* Afford::getAffordancePoints(char const* affordance) 
					throw (hpp::Error)
					{
						hpp::floatSeqSeqSeqSeq *affs;
						affordance::CollisionObjects_t affObjs = problemSolver_->get 
							<affordance::CollisionObjects_t> (affordance);
					  //TODO: Add error handling for non-existent aff name
						std::size_t nbAffs = affObjs.size ();
						affs = new hpp::floatSeqSeqSeqSeq ();
						affs->length ((CORBA::ULong)nbAffs);
						for (std::size_t affIdx = 0; affIdx < nbAffs; affIdx++)
						{
							affordance::BVHModelOBConst_Ptr_t model =
								affordance::GetModel (affObjs[affIdx]);
							std::size_t nbTris = model->num_tris;
							hpp::floatSeqSeqSeq tris;
							tris.length ((CORBA::ULong)nbTris);
							  for (std::size_t triIdx = 0; triIdx < nbTris; triIdx++)
								{
									hpp::floatSeqSeq triangle;
									triangle.length (3);
									for (std::size_t vertIdx= 0; vertIdx < 3; vertIdx++) {
								  fcl::Vec3f p (model->vertices [vertIdx + 3*triIdx]);
									hpp::floatSeq point;
									// point always 3D
									point.length (3); 
									for (std::size_t idx = 0; idx < 3; idx++) {
										point[(CORBA::ULong)idx] = p[idx];
									}
										triangle[(CORBA::ULong)vertIdx] = point;
									}
									tris[(CORBA::ULong)triIdx] = triangle;
								}
								(*affs)[(CORBA::ULong)affIdx] = tris;
							}
							return affs;
						}
				
    } // namespace impl
  } // namespace affordanceCorba
} // namespace hpp
