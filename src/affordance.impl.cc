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

				// TODO: how to implement this in a more user-friendly way?
				//			 create an variable in problemSolver?
				affordance::OperationBases_t Afford::createOperations ()
				{
					affordance::SupportOperationPtr_t support (new affordance::SupportOperation());
          affordance::LeanOperationPtr_t lean (new affordance::LeanOperation(0.1));

          affordance::OperationBases_t operations;
          operations.push_back(support);
          operations.push_back(lean);
					
					return operations;
				}

	      void Afford::affordanceAnalysis (const char* obstacleName, 
					const affordance::OperationBases_t & operations) throw (hpp::Error)
	      {
	        try {
            affordance::SemanticsDataPtr_t aff = affordance::affordanceAnalysis
                ((problemSolver_->obstacle (obstacleName))->fcl (), operations);
 					  std::vector<std::vector<fcl::CollisionObjectPtr_t > > affObjs = 
					  affordance::getAffordanceObjects (aff);
						// add fcl::CollisionObstacles to problemSolver
						addAffObjects (operations, affObjs, obstacleName);
						} catch (const std::exception& exc) {
	          throw Error (exc.what ());
	        }
	      }

	      void Afford::analyseObject (const char* obstacleName) throw (hpp::Error)
	      {
					// first erase affordance information for obstacleName
					/*for (unsigned int element = 0; element < 
						problemSolver_->getAllAs<affordance::CollisionObjects_t>().size();
						element ++)*/
          affordance::OperationBases_t operations = createOperations ();
					affordanceAnalysis (obstacleName, operations);
				}

				void Afford::analyseAll () throw (hpp::Error)
				{
					// first clear all old affordances:
					problemSolver_->clear <std::vector<boost::shared_ptr<model::CollisionObject> > > ();
					affordance::OperationBases_t operations = createOperations ();
					for (std::list <boost::shared_ptr<model::CollisionObject> >::const_iterator objIt = 
						problemSolver_->collisionObstacles ().begin (); 
						objIt != problemSolver_->collisionObstacles ().end (); objIt++) 
						{
							const char* obstacleName = (*objIt)->name ().c_str ();
							affordanceAnalysis (obstacleName, operations);
						}
				}

				// delete affordances by type for given object
				void Afford::deleteAffordancesByType (const char* affordance,
					const char* obstacleName) throw (hpp::Error)
				{
					if (obstacleName == "") {
						problemSolver_->erase <std::vector<boost::shared_ptr<model::CollisionObject> > > (affordance);
					} else {
						// TODO: implement	
					}
				}

				// delete all affordances for given object
				void Afford::deleteAffordances (const char* obstacleName)
					throw (hpp::Error)
				{
					if (obstacleName == "") {
						// if no obstacleName given, delete all affs in problemSolver
						problemSolver_->clear <std::vector<boost::shared_ptr<model::CollisionObject> > > ();
					} else {
						boost::shared_ptr<hpp::model::CollisionObject> obj;
						for (std::list <boost::shared_ptr<hpp::model::CollisionObject> >::const_iterator objIt = 
						problemSolver_->collisionObstacles ().begin ();
						objIt != problemSolver_->collisionObstacles ().end (); objIt++)
						{
							if (obstacleName = (*objIt)->name ().c_str ()) {
								obj = *objIt;
							}	
						} // TODO: deal with non-existent obstacle name!

						std::list<std::string> keys =  problemSolver_->getKeys 
							<std::vector<boost::shared_ptr<hpp::model::CollisionObject> >, std::list<std::string> > ();
						for (std::list<std::string>::iterator affIdx = keys.begin ();
							affIdx != keys.end (); affIdx++) {
							std::vector<boost::shared_ptr<model::CollisionObject> > affs = problemSolver_->get 
								<std::vector<boost::shared_ptr<model::CollisionObject> > > (*affIdx);

							for (unsigned int objIdx = 0; objIdx < affs.size (); objIdx++)
							{
								if (affs[objIdx]->name () == obstacleName) {
									affs.erase(affs.begin () + objIdx);
								} else {
									objIdx++;
								}
							}
						} 
					}
				}


				void Afford::addAffObjects (const affordance::OperationBases_t& ops,
					const std::vector<affordance::CollisionObjects_t>& affObjs,
					const char* obstacleName) throw (hpp::Error)
				{
					for (unsigned int opIdx = 0; opIdx < ops.size (); opIdx++)
					{
						std::vector<boost::shared_ptr<model::CollisionObject> > objs;
						affordance::CollisionObjects_t affs = affObjs[opIdx];
						for (unsigned int objIdx = 0; objIdx < affs.size (); objIdx++) {
							boost::shared_ptr<model::CollisionObject> obj =
							model::CollisionObject::create (affs[objIdx], obstacleName);
							objs.push_back (obj);
						}
						if (problemSolver_->has 
							<std::vector<boost::shared_ptr<model::CollisionObject> > >
							(ops[opIdx]->affordance_)) {
							std::vector<boost::shared_ptr<model::CollisionObject> > 
								mapObjs = problemSolver_->get 
								<std::vector<boost::shared_ptr<model::CollisionObject> > >
								(ops[opIdx]->affordance_);
							objs.insert (objs.begin () + objs.size (), mapObjs.begin (), mapObjs.end ());
						}
						problemSolver_->add 
							<std::vector<boost::shared_ptr<model::CollisionObject> > >(ops[opIdx]->affordance_, objs);
					}
				}
				
				hpp::floatSeqSeqSeqSeq* Afford::getAffordancePoints (char const* affordance) 
					throw (hpp::Error)
					{
						hpp::floatSeqSeqSeqSeq *affs;
						std::vector<boost::shared_ptr<model::CollisionObject> > affObjs = problemSolver_->get 
							<std::vector<boost::shared_ptr<model::CollisionObject> > > (affordance);
					  //TODO: Add error handling for non-existent aff name
						std::size_t nbAffs = affObjs.size ();
						affs = new hpp::floatSeqSeqSeqSeq ();
						affs->length ((CORBA::ULong)nbAffs);
						for (std::size_t affIdx = 0; affIdx < nbAffs; affIdx++)
						{
							affordance::BVHModelOBConst_Ptr_t model =
								affordance::GetModel (affObjs[affIdx]->fcl());
							std::size_t nbTris = model->num_tris;
							hpp::floatSeqSeqSeq tris;
							tris.length ((CORBA::ULong)nbTris);
							  for (std::size_t triIdx = 0; triIdx < nbTris; triIdx++)
								{
									hpp::floatSeqSeq triangle;
									triangle.length (3);
									for (std::size_t vertIdx= 0; vertIdx < 3; vertIdx++) {
								    fcl::Vec3f p (affObjs[affIdx]->fcl ()->getRotation ()* 
											model->vertices [vertIdx + 3*triIdx] +
											affObjs[affIdx]->fcl ()->getTranslation ());
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
