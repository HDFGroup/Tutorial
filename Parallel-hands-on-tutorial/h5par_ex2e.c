/* HDF5 Dataset example, independent open and write */

/* System header files */
#include <assert.h>

/* HDF5 header file */
#include "hdf5.h"

/* Predefined names and sizes */
#define FILENAME "h5par_ex2d.h5"
#define DATASETNAME "Dataset"
#define RANK    2
#define DIM0    10
#define DIM1    4       /* Should be same as MPI rank */
#define NAME_LENGTH 17

int main(int argc, char *argv[])
{
    hid_t file_id;              /* File ID */
    hid_t fapl_id;		/* File access property list */
    hid_t group_id;		/* Group ID */
    hid_t dset_id;		/* Dataset ID */
    hid_t file_space_id;	/* File dataspace ID */
    hsize_t file_dims[RANK];   	/* Dataset dimemsion sizes */
    char groupname[16];         /* Namne of group */
    int mpi_size, mpi_rank;	/* MPI variables */
    herr_t ret;         	/* Generic return value */
    ssize_t ret_size;
    char name[NAME_LENGTH];
    double write_buf[DIM0*DIM1];
    int i;

    /* Initialize MPI */
    MPI_Init(&argc, &argv);

    /* Gather information about MPI comm size and my rank */
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);


    /* Iniialize buffer of dataset to write */
    /* (in a real application, this would be your science data) */
    /* <SKIPPED> */

    /* Create an HDF5 file access property list */
    fapl_id = H5Pcreate (H5P_FILE_ACCESS);
    assert(fapl_id > 0);

    /* Set file access property list to use the MPI-IO file driver */
    ret = H5Pset_fapl_mpio(fapl_id, MPI_COMM_WORLD, MPI_INFO_NULL);
    assert(ret >= 0);

    /* Open the file collectively */
    file_id = H5Fopen(FILENAME, H5F_ACC_RDWR, fapl_id);
    assert(file_id > 0);

    /* Release file access property list */
    ret = H5Pclose(fapl_id);
    assert(ret >= 0);


    /* Open  one group per rank, independently */
    sprintf(groupname, "Group_%d", mpi_rank);
    group_id = H5Gopen(file_id, groupname, H5P_DEFAULT);
    assert(group_id > 0);


    /* Open the dataset independently */
    dset_id = H5Dopen(group_id, DATASETNAME, H5P_DEFAULT);
    assert(dset_id > 0);

    /* Get dataset path for each rank */
    ret_size = H5Iget_name(dset_id, name, NAME_LENGTH);
    assert(ret_size >= 0);
    printf("my rank = %d and my name is %s \n", mpi_rank, name);
    
    /* Write data independently */
    for (i=0; i < DIM0*DIM1; i++) write_buf[i] = (double)mpi_rank;
    ret = H5Dwrite(dset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, write_buf);
    assert(ret >= 0);


    /* Close dataset */
    ret = H5Dclose(dset_id);
    assert(ret >= 0);

    /* Close group collectively */
    ret = H5Gclose(group_id);
    assert(ret >= 0);

    /* Close the file collectively */
    ret = H5Fclose(file_id);
    assert(ret >= 0);

    /* MPI_Finalize must be called AFTER any HDF5 call which may use MPI calls */
    MPI_Finalize();

    return(0);
}

