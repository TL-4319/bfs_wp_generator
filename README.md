# Bolder Flight System WP file generator

This is a library to generate waypoints.txt file used for persistent mission saving for use with UA's fork of Bolder Flight System's SPAARO framework.

# CMake
This library is compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

# Usage
## Required input
The code requires an input file which is a csv.txt where each row is a waypoint (X/Y/Z) in the NEU frame.

The comma separated columns are ordered as followed:

| X position | Y position | Z position |

## Execution
Generate the waypoints.txt file by issuing:

```
./gen_wp /path/to/inputfile.txt
```

