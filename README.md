#  Humanoid Path Planner - AFFORDANCE-CORBA module

[![Pipeline status](https://gepgitlab.laas.fr/humanoid-path-planner/hpp-affordance-corba/badges/master/pipeline.svg)](https://gepgitlab.laas.fr/humanoid-path-planner/hpp-affordance-corba/commits/master)
[![Coverage report](https://gepgitlab.laas.fr/humanoid-path-planner/hpp-affordance-corba/badges/master/coverage.svg?job=doc-coverage)](http://projects.laas.fr/gepetto/doc/humanoid-path-planner/hpp-affordance-corba/master/coverage/)

Copyright 2016-2019 LAAS-CNRS

Author: Anna Seppala

## Description
hpp-affordance-corba implements python bindings for hpp-affordance, and presents a few example files.
Please refer to this [link](https://github.com/humanoid-path-planner/hpp-affordance) for information on hpp-affordance.

## Installation

### from robotpkg apt binaries

  1. Follow "Binary packages in robotpkg/wip" instructions: http://robotpkg.openrobots.org/robotpkg-wip.html
  2  `apt install robotpkg-hpp-affordance-corba`

### from source

To install hpp-affordance-corba:

  1. install HPP
	- see https://github.com/humanoid-path-planner/hpp-doc

  2. install HPP-AFFORDANCE
	- see https://github.com/humanoid-path-planner/hpp-affordance

  3. Clone the HPP-AFFORDANCE-CORBA repository onto your local computer and update the submodule:

			git clone --recursive https://github.com/humanoid-path-planner/hpp-affordance-corba.git
			cd $HPP_AFFORDANCE_CORBA_DIR/

  4. Use CMake to install the HPP-AFFORDANCE-CORBA library. For instance:

			mkdir build
			cd build
			cmake ..
			make install

  5. Optionally, install the HPP-RBPRM and HPP-RBPRM-CORBA packages that implement an efficient acyclic contact planner,
		 and its python bindings, respectively. (Make sure you are on branch "affordance" in both repositories!)
	- see https://github.com/humanoid-path-planner/hpp-rbprm, and
		https://github.com/humanoid-path-planner/hpp-rbprm-corba

## Documentation

  Open $DEVEL_DIR/install/share/doc/hpp-affordance-corba/doxygen-html/index.html in a web browser and you
  will have access to the code documentation. If you are using ipython, the documentation of the methods implemented
  is also directly available in a python console.

## Example

To see how to use the CORBA server and the affordance functionality, please refer to the python scripts provided within the 'tests' directory of this package. These python scripts use the HyQ model found in the 'data' directory (retrieved from https://github.com/iit-DLSLab/hyq-description).

To run the test files, launch the hpp-affordance-server executable, then open a python terminal, and copy one of the test scripts (e.g. test-affordance-description.py) into the python terminal bit by bit. This allows you to see the procedure in the viewer as you go through the comments in the example script.
