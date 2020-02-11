# manihot-lignum

manihot-lignum is a version of the LIGNUM model specifically for modelling *Manihot esculenta* (cassava) structure and function. :seedling:

## Usage

### Lignum Workbench

First compile the Lignum Workbench app `LignumWb.app` for easy visualisation of your tree.

```
$ cd qt-workbench
$ qmake qt-opengl.pro
$ make
$ open LignumWb.app
```

Further information can be found under `help` in the Lignum Workbench toolbar.


### Compile model

Then change directory and compile the Manihot lignum model.

```
$ cd ../manihot-sf
$ qmake Manihot.pro
$ make
```

Basic command line usage **after compilation**.

`$ ./manihot -iter [number of iterations] -r [random number generator] -load [load number] -model [model number] -x [x coordinate] -y [y coordinate] -L [l-system] -xml [output xml file]`

Run ./manihot with the arguments to specify model and output resulting xml file of tree architecture.

The resulting tree can be visualised using qt-workbench.

run ` make distclean` to remove previous compilations.

## Options

- -iter: Number of L-system iterations. I.e. branching.
- -r: Randomise branching for a more "natural" look.
- -load: Optional. Additional weight from snow/ice etc.
- -model: Type of model to use.
- -x: x coordinate.
- -y: y coordinate.
- -L: Specify L system (e.g. maniot.L)
- -xml: Name of output xml file.

## Contents

- Firmament: sky implementation.
- Graphics: old implementation of visualisation.
- LEngine: L system implementation.
- XMLTree: Render xml trees.
- c++adt: Necessary mathematical functions.
- manihot-sf: main manihot structural-functional model.
- qt-workbench: qt application for visualisation
- stl-lignum: main lignum library
- stl-voxelspace: main voxel space library
