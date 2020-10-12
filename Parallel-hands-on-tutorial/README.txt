This file explains the content of the parallel HDF5 Tutorial.
Several examples are borrowed from 
https://xgitlab.cels.anl.gov/ATPESC-IO/hands-on/-/tree/master/hdf5

h5_ex0.c
Sequential program to write a dataset; creates SDS.h5

h5par_ex0.c
Parallel program to write a dataset; creates SDSpar.h5

h5_ex1.c
Sequential program that writes a dataset by columns (compare with h5par_ex1a.c)
Creates h5_ex1.h5 

h5par_ex1a.c
Uses 4 ranks to write a dataset (230000 x 4) by columns 
(independent I/O); creates h5par_ex1a.h5

h5par_ex1b.c
Uses 4 ranks to write a dataset (230000 x 4) by columns 
(collective I/O); creates h5par_ex1b.h5

h5par_ex1c.c
Uses 4 ranks to write a chunked dataset (230000 x 4) by columns 
(independent I/O); creates h5par_ex1c.h5

h5par_ex1d.c
Uses 4 ranks to write a chunked and compressed dataset (230000 x 4) by columns
(collective I/O); creates h5par_ex1d.h5


h5par_ex2a.c
Tries indeprendently create one group and dataset per rank (result is not what 
you'll expect); creates h5par_ex2a.h5 file.
Use ./h5dump -H h5par_ex2a.h5 to check the content without printing data.


h5par_ex2b.c
Creates one group and dataset per rank (correct result); creates h5par_ex2b.h5
file. Use ./h5dump -H h5par_ex2b.h5 to check the content without printing data.

h5par_ex2c.c
Independently opens groups and datasets and for each rank prints 
a path to the open dataset in h5par_ex2b.h5

h5par_ex2d.c
Creates datasets with early time allocation so we can write to them 
independently in the next example; creates h5par_ex2d.h5

h5par_ex2e.c
Independently opens groups and datasets and for each rank prints a path to the 
open dataset and writes to each dataset in h5par_ex2d.h5

h5par-comparison.c 
Any number of ranks can be used to create, write, and read a dataset in h5par_comp.h5
The pprgram can be compiled to use colletive metadata and raw data writes and reads.
