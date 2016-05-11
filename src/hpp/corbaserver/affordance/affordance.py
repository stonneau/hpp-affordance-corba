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

		## Get list of affordance types used in affordance analysis.
    def getAffordanceTypes (self):
        return self.client.affordance.affordance.getAffordanceTypes ()

    def getAffRefObstacles (self, affType):
        return self.client.affordance.affordance.getAffRefObstacles (affType)

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
        import re
        objNames = self.client.basic.obstacle.getObstacleNames(True,False)
        for name in objNames:
          splt = re.split ('/', name)
          if splt[0] == prefix :
            self.analyseObject (name)
        return

		## Visualise found affordance surfaces
		#
		# \param affType the type of affordance to be visualised
		# \Viewer viewer object to load affordance objects to visualiser
		# \groupName name of group in the viewer that the objects will be added to
		# \colour vector of length 3 (rgb). Colours defined in the interval [0, 1]
    def visualiseAllAffordances (self, affType, Viewer, colour):
        self.deleteNode (str (affType), True, Viewer)
        objs = self.getAffordancePoints (affType)
        refs = self.getAffRefObstacles (affType)
        Viewer.client.gui.createGroup (str (affType))
        for aff in objs:
          count = 0
          for tri in aff:
            Viewer.client.gui.addTriangleFace (str (affType) + '-' + \
                 str (refs[objs.index (aff)]) + '.' + \
								 str (objs.index (aff)) + '.' + str(count), \
						     tri[0], tri[1], tri[2], [colour[0], colour[1], colour[2], 1])
            Viewer.client.gui.addToGroup (str (affType) + '-' + \
						     str (refs[objs.index (aff)]) + '.' + \
								 str (objs.index (aff)) + '.' + str(count), str (affType))
            count += 1
          Viewer.client.gui.setWireFrameMode(refs[objs.index (aff)], 'WIREFRAME')
        Viewer.client.gui.addToGroup (str (affType), Viewer.sceneName)
        return

    def visualiseAffordances (self, affType, Viewer, colour, obstacleName=""):
        if obstacleName == "":
          return self.visualiseAllAffordances (affType, Viewer, colour)
        else:
          self.deleteAffordancesByTypeFromViewer (affType, Viewer, obstacleName)
          nodes = Viewer.client.gui.getNodeList ()
          if affType not in nodes: Viewer.client.gui.createGroup (str (affType))
          objs = self.getAffordancePoints (affType)
          refs = self.getAffRefObstacles (affType)
          for aff in objs:
            if refs[objs.index (aff)] == obstacleName:
              count = 0
              for tri in aff:
                Viewer.client.gui.addTriangleFace (str (affType) + '-' + \
                     str (refs[objs.index (aff)]) + '.' + \
				      			 str (objs.index (aff)) + '.' + str(count), \
				      	     tri[0], tri[1], tri[2], [colour[0], colour[1], colour[2], 1])
                Viewer.client.gui.addToGroup (str (affType) + '-' + \
				      	     str (refs[objs.index (aff)]) + '.' + \
				      			 str (objs.index (aff)) + '.' + str(count), str (affType))
                count += 1
          Viewer.client.gui.addToGroup (str (affType), Viewer.sceneName)
          Viewer.client.gui.setWireFrameMode(obstacleName, 'WIREFRAME')
        return


		## Delete affordances for given object. If no objectName provided,
		#        all affordances will be deleted.
		# \param obstacleName name of obstacle the affordances of which will
		#        be deleted.
    def deleteAffordances (self, Viewer, obstacleName=""):
        self.deleteAffordancesFromViewer (Viewer, obstacleName)
        return self.client.affordance.affordance.deleteAffordances (obstacleName)

    def deleteAffordancesFromViewer (self, Viewer, obstacleName=""):
        affs = self.getAffordanceTypes ()
        if obstacleName == "":
			  	for aff in affs:
					  self.deleteNode (aff, True, Viewer)
        else:
           import re
           for aff in affs:
             refs = self.getAffRefObstacles (aff)
             count = 0
             while count < len(refs):
               if refs[count] == obstacleName:
                 toDelete = aff + '-' + refs[count]
                 nodes = Viewer.client.gui.getNodeList()
                 for node in nodes:
                   splt = re.split ('\.', node)
                   if splt[0] == toDelete:
                     self.deleteNode (node, True, Viewer)
               count += 1
        return

		## Delete affordances for given object. If no objectName provided,
		#        all affordances of given type will be deleted, irrespective
		#        of object.
		# \param affordanceType type of affordance to be deleted
		# \param obstacleName name of obstacle the affordances of which will
		#        be deleted.
    def deleteAffordancesByType (self, affordanceType, Viewer, obstacleName=""):
        self.deleteAffordancesByTypeFromViewer (affordanceType, Viewer, obstacleName)
        return self.client.affordance.affordance.deleteAffordancesByType(affordanceType, obstacleName)

    def deleteAffordancesByTypeFromViewer (self, affordanceType, Viewer, obstacleName=""):
        if obstacleName == "":
          Viewer.client.gui.deleteNode (affordanceType, True)
        else:
           import re
           affs = self.getAffordanceTypes ()
           for aff in affs:
             if aff == affordanceType:
               refs = self.getAffRefObstacles (aff)
               count = 0
               while count < len(refs):
                 if refs[count] == obstacleName:
                   toDelete = aff + '-' + refs[count] 
                   nodes = Viewer.client.gui.getNodeList()
                   for node in nodes:
                     splt = re.split ('\.', node)
                     if splt[0] == toDelete:
                       self.deleteNode (node, True, Viewer)
                 count += 1
        return

		# Delete node from viewer
		# \param affType name of affordance node to be deleted
		# \param all TODO: boolean that determines ...?
		# \param Viewer viewer object used to execute deletion function
    def deleteNode (self, affType, all, Viewer):
        return Viewer.client.gui.deleteNode (str (affType), all)
