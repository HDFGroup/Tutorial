#install.packages("BiocManager")
#BiocManager::install("rhdf5")

library(rhdf5)
h5version()

mtcars
#Column vector slice
mtcars$mpg[c(1,2,3)]
# Column slice
mtcars[c("mpg", "hp")][c(1,2,3),]
# Row slice
mtcars[c("Volvo 142E", "Porsche 914-2"),]

# About a dozen high-level fire-and-forget functions
h5createFile("hug2020_r.h5")
h5write(mtcars, file="hug2020_r.h5", "mtcars")
# Save multiple objects
A = 1:7;  B = 1:18; D = seq(0,1,by=0.1)
h5save(A, B, D, file="hug2020_r.h5")
h5dump("hug2020_r.h5")

# Support for operators to extract or replace parts of an object
# - =[= - subset HDF5 datasets (read, write)
# - =$= - read or write HDF5 objects via location (handle) + name reference
fid <- H5Fopen("hug2020_r.h5")
fid$mtcars[c(1,2,3),]
H5Fclose(fid)
# - =&= - obtain a handle for an HDF5 object
# - Help system integration
h5const("H5S_SELECT")

# Examine/control file locking behavior
file <- tempfile()
h5testFileLocking(file)

# =rhdf5= gives users the choice between (HDF5) =native= and column-oriented layout
m <- matrix(rep(1:20, each = 10), ncol = 20, byrow = FALSE)
h5write(m, file="hug2020_r.h5", "20x10 (non-native)")
h5write(m, file="hug2020_r.h5", "20x10 (native)", native = TRUE)
h5dump("hug2020_r.h5")

# *Buyer beware:* see for example [[https://bioconductor.org/packages/3.11/bioc/vignettes/rhdf5/inst/doc/practical_tips.html][rhdf5 Practical Tips]] by Mike Smith
m1 <- matrix(rep(1:20000, each = 100), ncol = 20000, byrow = FALSE)
ex_file <- tempfile(fileext = ".h5")
h5write(m1, file = ex_file, name = "counts", level = 6)
# read all columns
system.time(
  res1 <- h5read(file = ex_file, name = "counts", index = list(NULL, 1:10000))
)
# read every other column
index <- list(NULL, seq(from = 1, to = 20000, by = 2))
system.time(
  res2 <- h5read(file = ex_file, name = "counts", index = index)
)
