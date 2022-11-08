## README Translation
- [English](README.md)
- [Portuguese](README-pt.md)

# Instructions

## 1. Installing OpenFoam on your machine:

To use this repository it is necessary to install OpenFoam on your machine (Linux).

Installation on ubuntu systems can be done by following this tutorial: [ubuntu installation]: https://openfoam.org/download/8-ubuntu/

Installations on other Linux versions can be done through this tutorial: [installation]: https://openfoam.org/download/

With OpenFoam properly installed on your machine according to the tutorials above, we can proceed to install the Upwind schematics from this repository (TOPUS, FSFL, SDPUS-C1 and EPUS)

## 2. Installation of TOPUS, FSFL, SDPUS-C1 and EPUS schemas in OpenFoam:

### 2.1 Copy the necessary files from this repository to the OpenFoam installation location on your machine.

Browse the OpenFoam installation location on your machine to the path below:

Copy the folders from that repository in 'openFoamFluxLimiters/src/finiteVolume/interpolation/surfaceInterpolation/limitedSchemes/' to the same path in the OpenFoam installation location on your machine '/opt/openfoam8/src/finiteVolume/interpolation/surfaceInterpolation/limitedSchemes'.

You may need administrator permission to copy the files, if that's what you need.

Note that the path '/opt/openfoam8/...' may be different on your machine if OpenFoam is installed by means other than those mentioned in this tutorial.

### 2.2 Include the previously copied files in the OpenFoam build file

Navigate to '/opt/openfoam8/src/finiteVolume/Make/' in the OpenFoam directory on your machine

Open the 'files' file and add the following code snippet in it:

```c++
$(limitedSchemes)/TOPUS/TOPUS.C
$(limitedSchemes)/FSFL/FSFL.C
$(limitedSchemes)/SD_PUS_C1/SD_PUS_C1.C
$(limitedSchemes)/EPUS/EPUS.C
```

this code snippet must be inserted into the definition of the ```limitedSchemes``` variable, as follows:

```c
limitedSchemes = $(surfaceInterpolation)/limitedSchemes
$(limitedSchemes)/limitedSurfaceInterpolationScheme/limitedSurfaceInterpolationSchemes.C
$(limitedSchemes)/upwind/upwind.C
$(limitedSchemes)/blended/blended.C
$(limitedSchemes)/Gamma/Gamma.C
$(limitedSchemes)/SFCD/SFCD.C
$(limitedSchemes)/Minmod/Minmod.C
$(limitedSchemes)/vanLeer/vanLeer.C
$(limitedSchemes)/vanAlbada/vanAlbada.C
$(limitedSchemes)/TOPUS/TOPUS.C
$(limitedSchemes)/FSFL/FSFL.C
$(limitedSchemes)/SD_PUS_C1/SD_PUS_C1.C
$(limitedSchemes)/EPUS/EPUS.C
```

### 2.3 Compile OpenFoam to include the new flow limiters

Navigate to the OpenFoam installation location on your machine '/opt/openfoam8/src/finiteVolume' and open a terminal inside this folder

With the terminal open, run the following commands:

```
wmake
```

The build process should start

If there is a permission error, type the command

```
sudo -i
cd /opt/openfoam8/src/finiteVolume
```

Again, the path may be different depending on the version of OpenFoam on your machine, for example version 9 would have the path '/opt/openfoam9...'

If the compilation process went without errors, the compilation was successful!
