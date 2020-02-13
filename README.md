# manihot-lignum

manihot-lignum is a version of the [LIGNUM](http://www.metla.fi/metinfo/kasvu/lignum/index-en.htm) model (Perttunen et al., 1996) specifically for modelling *Manihot esculenta* (cassava) structure and function. :seedling:

### Prerequisites
Qt 4.5

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

Change directory and compile the Manihot lignum model.

```
$ cd ../manihot-sf
$ qmake Manihot.pro
$ make
```

Run ./manihot with the arguments below to specify model and resulting xml file of tree architecture.

`$ ./manihot -iter [number of iterations] -r [random number generator] -load [load number] -model [model number] -x [x coordinate] -y [y coordinate] -L [l-system] -xml [output xml file]`


### Options

- -iter: Number of L-system iterations. I.e. branching.
- -r: Randomise branching for a more "natural" look.
- -load: Optional. Additional weight from snow/ice etc.
- -model: Type of model to use.
- -x: x coordinate.
- -y: y coordinate.
- -L: Specify L system (e.g. maniot.L)
- -xml: Name of output xml file.

You can then `add tree` to the Lignum Workbench to visualise your tree! :deciduous_tree: :evergreen_tree: :deciduous_tree:

run ` make distclean` to remove previous compilations.

## Contents

- **Firmament**: sky implementation.
- **Graphics**: old implementation of visualisation.
- **LEngine**: L system implementation.
- **XMLTree**: Render xml trees.
- **c++adt**: Necessary mathematical functions.
- **manihot-sf**: main manihot structural-functional model.
- **qt-workbench**: qt application for visualisation
- **stl-lignum**: main lignum library
- **stl-voxelspace**: main voxel space library

## Author
* Hannah O'Sullivan (h.osullivan18@imperial.ac.uk)

## Acknowledgements
* Jari Perttunen: LIGNUM core model
* Risto Sievanan: LIGNUM core model
* Jon Lloyd: *Manihot* TLS data
