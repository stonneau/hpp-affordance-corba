#!/usr/bin/env python
# Copyright (c) 2016 CNRS
# Author: Anna Seppala
#
# This file is part of hpp-affordance-corba.
# hpp-affordance-corba is free software: you can redistribute it
# and/or modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation, either version
# 3 of the License, or (at your option) any later version.
#
# hpp-affordance-corba is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Lesser Public License for more details.  You should have
# received a copy of the GNU Lesser General Public License along with
# hpp-affordance-corba.  If not, see
# <http://www.gnu.org/licenses/>.

from hpp.corbaserver.affordance import Client as AffClient
from hpp.corbaserver import Client as BasicClient

## Corba clients to the various servers
#
class CorbaClient:
    """
    Container for corba clients to various interfaces.
    """
    def __init__ (self):
        self.basic = BasicClient ()
        self.affordance = AffClient ()

## Load and handle a RbprmDevice robot for rbprm planning
#
#  A RbprmDevice robot is a dual representation of a robots. One robot describes the 
#  trunk of the robot, and a set of robots describe the range of motion of each limb of the robot.
class AffordanceTool (object):
    ## Constructor
    def __init__ (self):
        self.client = CorbaClient ()
        
    ## \brief Remove an obstacle from outer objects of a joint body
    #
    #  \param objectName name of the object to remove,
    #  \param jointName name of the joint owning the body,
    #  \param collision whether collision with object should be computed,
    #  \param distance whether distance to object should be computed.
		#  Also deletes affordance objects of given obstacle.
    def removeObstacleFromJoint (self, objectName, jointName, collision,
                                 distance):
        self.client.basic.obstacle.removeObstacleFromJoint \
            (objectName, jointName, collision, distance)
        return self.deleteAffordances (obstacleName)

		## Analyse all loaded objects
    def analyseAll (self):
		    return self.client.affordance.affordance.analyseAll ()

    ## Analyse one object by name
		#  \param objectName name of the object to analyse.
    def analyseObject (self, objectName):
		    return self.client.affordance.affordance.analyseObject (objectName)

    ## Get vertex points of all triangles of an affordance type. Useful for
		#  visualisation.
		#  \param affordanceType name for affordance type to be used
    def getAffordancePoints (self, affordanceType):
		    return self.client.affordance.affordance.getAffordancePoints \
				    (affordanceType)

		## Load obstacles and visualise them in viewer
		#  \param package ros package containing the urdf file
		#  \param filename filename name of the urdf file without extension
		#  \param prefix prefix added to object names in case the same file 
		#         is loaded several times 
		#  \param Viewer viewer object to load affordance objects to visualiser
		#  \param meshPackageName meshPackageName ros package containing the geometry files
    #         (collada, stl,...) if different from package
		#  \param guiOnly whether to control only gepetto-viewer-server
    def loadObstacleModel (self, package, filename, prefix, \
		  Viewer, meshPackageName=None, guiOnly=False):
        Viewer.loadObstacleModel (package, filename, prefix, \
            meshPackageName, guiOnly)
        self.analyseObject (prefix + '/base_link_0') # TODO: make global const
        return

		## Visualise found affordance surfaces
		#
		# \param affType the type of affordance to be visualised
		# \Viewer viewer object to load affordance objects to visualiser
		# \groupName name of group in the viewer that the objects will be added to
		# \colour vector of length 3 (rgb). Colours defined in the interval [0, 1]
    def visualiseAffordances (self, affType, Viewer, groupName, colour):
        objs = self.getAffordancePoints (affType)
        count = 0
        for aff in objs:
          for tri in aff:
            Viewer.client.gui.addTriangleFace('tri' + str(count), \
						     tri[0], tri[1], tri[2], [colour[0], colour[1], colour[2], 1])
            Viewer.client.gui.addToGroup('tri' + str(count), groupName)
            count += 1

        return

		## Delete affordances for given object. If no objectName provided,
		#        all affordances will be deleted.
		# \param obstacleName name of obstacle the affordances of which will
		#        be deleted.
    def deleteAffordances (self, obstacleName=""):
        return self.deleteAffordances (obstacleName)

		## Delete affordances for given object. If no objectName provided,
		#        all affordances of given type will be deleted, irrespective
		#        of object.
		# \param affordanceType type of affordance to be deleted
		# \param obstacleName name of obstacle the affordances of which will
		#        be deleted.
    def deleteAffordancesByType (self, affordanceType, obstacleName=""):
        return self.deleteAffordancesByType(affordanceType, obstacleName)
