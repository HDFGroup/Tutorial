/*  
 *  This example writes data to the HDF5 file.
 */
 
#include "hdf5.h"
#include "stdlib.h"

#define H5FILE_NAME     "SDS.h5"
#define DATASETNAME 	"IntArray" 
#define NX     8                      /* dataset dimensions */
#define NY     5 
#define RANK   2

int
main (int argc, char **argv)
{
/*
 *
 * HDF5 APIs definitions
 */ 	
    hid_t       file_id, dset_id;         /* file and dataset identifiers */
    hid_t       filespace;                /* file and memory dataspace identifiers */
    hsize_t     dimsf[] = {NX, NY};       /* dataset dimensions */
    int         *data;                    /* pointer to data buffer to write */
    hid_t	plist_id;                 /* property list identifier */
    int         i;
    herr_t      status;

 
/*
 * Initialize data buffer 
 */
    data = (int *) malloc(sizeof(int)*dimsf[0]*dimsf[1]);
    for (i=0; i < dimsf[0]*dimsf[1]; i++) {
        data[i] = i;
    }
    plist_id = H5Pcreate(H5P_FILE_ACCESS);

/*
 * Create a new file collectively and release property list identifier.
 */
    file_id = H5Fcreate(H5FILE_NAME, H5F_ACC_TRUNC, H5P_DEFAULT, plist_id);

/*
 * Create the dataset with default properties and  write it.
 */
    filespace = H5Screate_simple(RANK, dimsf, NULL); 
    dset_id = H5Dcreate(file_id, DATASETNAME, H5T_NATIVE_INT, filespace,
			H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    status = H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL,
		      H5P_DEFAULT, data);

/*
 * Close/release resources.
 */
    H5Dclose(dset_id);
    H5Sclose(filespace);
    H5Pclose(plist_id);
    H5Fclose(file_id);
 
    free(data);

    return 0;
}
