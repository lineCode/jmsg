override CFLAGS += -std=c11
override CXXFLAGS += -std=c++11

# you can add your own libs need to link.
override LDLIBS += -lpthread \
                   -lexemodel \
                   -lopencv_core \
                   -lopencv_imgproc \
                   -lpng \
                   -lgsl \
                   -lgslcblas \
                   -llua \
                   -ldl \
                   -lfss-encrypt
override LDFLAGS += "-L$(dir_self)/lib/release/bin/"

# the aux variable, used to identify the directory this Makefile in.
dir_self := $(shell dirname $(shell readlink -fe $(lastword ${MAKEFILE_LIST})))
dir_main := $(shell readlink -fe ${dir_self})

############ compile control
# output directory, all the output files will be put in it.
output_dir := ${dir_main}/output
# the main name of this program
main_name := fusion-splicer-svc
# include directories, use `:' as seperator
inc_dir_set := ${dir_main}/include ${dir_main}/../kl360-drv/include ${dir_main}/../exe-model/include
# recursive directory, will compile files in it, and in it's subdirectories.
src_recdir_set:=${dir_main}/src
# solo directory, will only compile the files under it directly, no recursive.
#src_solodir_set:=${dir_main}/src

# the default value of `output_types' is `bin'
# you can assign multi value to it.
# the selective values:
# 	bin:		*	exe program.
# 	sharedlib:	*.so	if you selected it, you must define `lib_version'
# 			simultaneously.
#	staticlib:	*.a	used to link with other module to final .so or bin.
#output_types := bin,sharedlib,staticlib
#lib_version :=
output_types := bin

############ install control
# if your output_types contain *lib, then you need it.
#header_dir := ${dir_main}/include

include ${dir_main}/scripts/Makefile.base
