#  Humanoid Path Planner - AFFORDANCE-CORBA module

Copyright 2016 LAAS-CNRS

Author: Anna Seppala

##Description
hpp-affordance-corba implements python bindings for hpp-affordance, and presents a few example files.
Please refer to this [link](https://github.com/anna-seppala/hpp-affordance) for information on hpp-affordance.

##Installation on ubuntu-14.04 64 bit with ros-indigo

To install hpp-affordance-corba:

  1. install HPP
	- see https://github.com/humanoid-path-planner/hpp-doc

  2. install HPP-AFFORDANCE
	- see https://github.com/anna-seppala/hpp-affordance

  3. Use CMake to install the library. For instance:

			mkdir $HPP_AFFORDANCE_CORBA_DIR/build
			cd $HPP_AFFORDANCE_CORBA_DIR/build
			cd cmake ..	
			make install
	
  4. Optionally, install the HPP-RBPRM and HPP-RBPRM-CORBA packages that implement an efficient acyclic contact planner,
		 and its python bindings, serpectively. (Make sure you are on branch "affordance" in both repositories!)
	- see https://github.com/anna-seppala/hpp-rbprm, and
		https://github.com/anna-seppala/hpp-rbprm-corba

##Documentation

  Open $DEVEL_DIR/install/share/doc/hpp-affordance-corba/doxygen-html/index.html in a web browser and you
  will have access to the code documentation. If you are using ipython, the documentation of the methods implemented
  is also directly available in a python console.

