# PIPE = -pipe
# ???
#LD_DYN_FLAGS	= -ldl -rdynamic
#SFLAGS		= -fpic -DPIC
#SLDFLAGS	= -shared
#LD_LIBC	        = -lc
#STATIC_LDFLAGS	= -static

WARNCFLAGS = -Wunused-parameter
# clang has also: -Wunneeded-internal-declaration

NODEBUGCFLAGS   = -O3 -w -fomit-frame-pointer $(WARNCFLAGS)
NODEBUGCXXFLAGS = -O3 -w -fomit-frame-pointer $(WARNCFLAGS)
NODEBUGDEFS = -DNDEBUG -DOM_NDEBUG 

CXXTEMPLFLAGS =-ftrapv ## -fno-implicit-templates

AM_CPPFLAGS = -I${top_srcdir} -I${top_builddir} -I${top_srcdir}/numeric -I${top_builddir}/numeric -I${top_srcdir}/kernel -I${top_builddir}/kernel -I${top_srcdir}/libpolys -I${top_builddir}/libpolys $(GMP_CFLAGS) -I${top_srcdir}/factory/include -I${top_builddir}/factory/include $(FACTORY_CFLAGS) $(NTL_CFLAGS) $(FLINT_CFLAGS)

########################### libSingular* #########################

if WANT_DEBUG
  LIB_G=libSingular_g.la
else
  LIB_G=
endif

libSingular_LTLIBRARIES = libSingular.la ${LIB_G}
libSingulardir = $(libdir)/singular

libSingular_la_CFLAGS   = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE}  $(WARNCFLAGS)
libSingular_g_la_CFLAGS = -g -Wextra -Wall -Wno-long-long -pedantic ${PIPE}  $(WARNCFLAGS)

libSingular_la_CXXFLAGS   = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)  $(WARNCFLAGS)
libSingular_g_la_CXXFLAGS = -g -Wextra -Wall -Wno-long-long -pedantic ${PIPE} $(CXXTEMPLFLAGS)   $(WARNCFLAGS)
# -fdiagnostics-show-option 


libSingular_la_CPPFLAGS   = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG -DLIBSINGULAR
libSingular_g_la_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DLIBSINGULAR

SOURCES =    Minor.cc\
   MinorInterface.cc\
   MinorProcessor.cc\
   attrib.cc\
   bbcone.cc\
   bbfan.cc\
   bigintm.cc\
   blackbox.cc\
   calcSVD.cc\
   cntrlc.cc\
   countedref.cc\
   denom_list.cc\
   eigenval_ip.cc\
   extra.cc\
   feOpt.cc\
   fehelp.cc\
   fevoices.cc\
   fglm.cc\
   gms.cc\
   grammar.cc\
   interpolation.cc\
   iparith.cc\
   ipassign.cc\
   ipconv.cc\
   ipid.cc\
   iplib.cc\
   ipprint.cc\
   ipshell.cc\
   janet.cc\
   libparse.cc\
   linearAlgebra_ip.cc\
   lists.cc\
   maps_ip.cc\
   minpoly.cc\
   misc_ip.cc\
   links/ndbm.cc\
   newstruct.cc\
   pcv.cc\
   links/pipeLink.cc\
   scanner.cc\
   sdb.cc\
   links/s_buff.cc\
   links/silink.cc\
   links/sing_dbm.cc\
   sing_win.cc\
   slInit_Static.cc\
   links/ssiLink.cc\
   subexpr.cc\
   walk.cc\
   walk_ip.cc\
   wrapper.cc\
   fereadl.c mmstd.c claptmpl.cc

#   slInit_Dynamic.cc

libSingular_la_SOURCES   = $(SOURCES) feOpt.inc
libSingular_g_la_SOURCES = $(SOURCES) feOpt.inc

SingularHEADERS =    Cache.h \
   CacheImplementation.h \
   Minor.h \
   MinorInterface.h \
   MinorProcessor.h \
   attrib.h \
   bigintm.h \
   blackbox.h \
   cntrlc.h \
   countedref.h \
   links/dbm_sl.h \
   distrib.h \
   eigenval_ip.h \
   feOpt.h feOptTab.h fehelp.h \
   fglm.h \
   gms.h \
   grammar.h \
   interpolation.h \
   idrec.h \
   ipconv.h \
   ipid.h \
   ipprint.h \
   ipshell.h \
   janet.h \
   libparse.h \
   libsingular.h \
   linearAlgebra_ip.h\
   lists.h \
   locals.h \
   maps_ip.h \
   minpoly.h \
   misc_ip.h \
   mmalloc.h \
   omSingularConfig.h \
   links/ndbm.h \
   newstruct.h \
   pcv.h \
   links/pipeLink.h \
   pyobject_setup.h \
   run.h \
   sdb.h \
   silink.h \
   links/s_buff.h \
   links/sing_dbm.h \
   sing_win.h \
   slInit.h \
   links/ssiLink.h \
   stype.h \
   subexpr.h \
   table.h \
   tok.h \
   walk.h 

# plural_cmd.inc 
nodist_libSingular_la_SOURCES = iparith.inc
nodist_libSingular_g_la_SOURCES = iparith.inc

noinst_HEADERS = version.h


libSingular_includedir = ${includedir}/singular/Singular/
nobase_libSingular_include_HEADERS = $(SingularHEADERS)

if ENABLE_FACTORY
  USE_FACTORY = -L${top_builddir}/factory
else
  USE_FACTORY =
endif

#########################################################
# handle all the generated *.inc

noinst_PROGRAMS = gentable1 feOptGen feOptES feOptTS

gentable1_SOURCES = gentable.cc grammar.h tok.h table.h
gentable1_CFLAGS = -O3 -fomit-frame-pointer ${PIPE}
gentable1_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
gentable1_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG

feOptGen_SOURCES = feOptGen.cc feOptGen.h
feOptGen_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
feOptGen_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG

feOptES_SOURCES = feOptGen.cc feOptGen.h
feOptES_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
feOptES_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG -DESINGULAR 

feOptTS_SOURCES = feOptGen.cc feOptGen.h
feOptTS_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
feOptTS_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG -DTSINGULAR

########################### Singular* #########################

if WANT_DEBUG
  EXTRA_PROGRAMS = Singulard Singulardg libparse
else
  EXTRA_PROGRAMS = Singulard libparse
endif

# the "optional_programs" variable should be defined in the configure
# script, and listed in an AC_SUBST macro
optional_Singular_programs = 

if WANT_DEBUG
  bin_PROGRAMS = Singular Singularg ESingular TSingular $(optional_Singular_programs)
else
  bin_PROGRAMS = Singular ESingular TSingular $(optional_Singular_programs)
endif

AMLDFLAGS = -L${abs_top_builddir}/Singular -L${abs_top_builddir}/numeric -L${abs_top_builddir}/kernel -L${abs_top_builddir}/libpolys/polys  -L${top_builddir}/libpolys/coeffs -L${top_builddir}/libpolys/reporter -L${top_builddir}/libpolys/misc $(USE_FACTORY) -L${abs_top_builddir}/omalloc -L${abs_top_builddir}/findexec

Singular_CFLAGS = -O3 -fomit-frame-pointer ${PIPE}
Singularg_CFLAGS = -g ${PIPE}

Singular_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
Singularg_CXXFLAGS = -g -Wextra -Wall -Wno-long-long -pedantic ${PIPE} $(CXXTEMPLFLAGS)

nodist_Singular_SOURCES = libSingular.la
nodist_Singularg_SOURCES =  libSingular_g.la

Singular_SOURCES = tesths.cc fegetopt.c fegetopt.h utils.cc  utils.h 
Singularg_SOURCES = tesths.cc fegetopt.c fegetopt.h utils.cc  utils.h 

Singular_LDADD = libSingular.la ${abs_top_builddir}/numeric/libnumeric.la ${abs_top_builddir}/kernel/libkernel.la ${abs_top_builddir}/libpolys/polys/libpolys.la -lcoeffs -lreporter -lmisc $(FACTORY_LIBS) -lomalloc -lfindexec $(FLINT_LIBS) $(NTL_LIBS) $(GMP_LIBS) ${USEPPROCSDYNAMICLDFLAGS} ${USEPPROCSDYNAMICLD}
Singularg_LDADD = libSingular_g.la ${abs_top_builddir}/numeric/libnumeric_g.la ${abs_top_builddir}/kernel/libkernel_g.la ${abs_top_builddir}/libpolys/polys/libpolys_g.la -lcoeffs_g -lreporter_g -lmisc_g $(FACTORY_LIBS) -lomalloc_g -lfindexec_g $(FLINT_LIBS) $(NTL_LIBS) $(GMP_LIBS) ${USEPPROCSDYNAMICLDFLAGS}  ${USEPPROCSDYNAMICLD}

Singular_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG
Singularg_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H 

Singular_LDFLAGS = -static ${AMLDFLAGS}
Singularg_LDFLAGS = -static ${AMLDFLAGS}


Singulard_CFLAGS = -O3 -fomit-frame-pointer ${PIPE}
Singulardg_CFLAGS = -g ${PIPE}

Singulard_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
Singulardg_CXXFLAGS = -g -Wextra -Wall -Wno-long-long -pedantic ${PIPE} $(CXXTEMPLFLAGS)

Singulard_SOURCES = tesths.cc fegetopt.c fegetopt.h utils.cc  utils.h 
nodist_Singulard_SOURCES = libSingular.la

Singulardg_SOURCES = tesths.cc fegetopt.c fegetopt.h utils.cc  utils.h 
nodist_Singulardg_SOURCES =  libSingular_g.la

Singulard_LDADD = libSingular.la -lnumeric -lkernel -lpolys -lcoeffs -lreporter -lmisc $(FACTORY_LIBS) -lomalloc -lfindexec $(FLINT_LIBS) $(NTL_LIBS) $(GMP_LIBS) ${USEPPROCSDYNAMICLDFLAGS} ${USEPPROCSDYNAMICLD}
Singulardg_LDADD = libSingular_g.la -lnumeric_g -lkernel_g -lpolys_g -lcoeffs_g -lreporter_g -lmisc_g $(FACTORY_LIBS) -lomalloc_g -lfindexec_g $(FLINT_LIBS) $(NTL_LIBS) $(GMP_LIBS) ${USEPPROCSDYNAMICLDFLAGS}  ${USEPPROCSDYNAMICLD}

Singulard_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG
Singulardg_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H 

Singulard_LDFLAGS = ${AMLDFLAGS}
Singulardg_LDFLAGS = ${AMLDFLAGS}


#### ESingular 

ESingular_CFLAGS = -O3 -fomit-frame-pointer ${PIPE}
ESingular_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
ESingular_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG -DESINGULAR -DPROTO 
ESingular_LDFLAGS = -static ${AMLDFLAGS}
ESingular_LDADD =   -lreporter -lmisc -lomalloc -lfindexec 

ESingular_SOURCES = emacs.cc fegetopt.c fegetopt.h feOptES.inc feOpt.cc

#### same for TSingular 

TSingular_CFLAGS = -O3 -fomit-frame-pointer ${PIPE}
TSingular_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
TSingular_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG -DTSINGULAR -DPROTO 
TSingular_LDFLAGS = -static ${AMLDFLAGS}
TSingular_LDADD =   -lreporter -lmisc -lomalloc -lfindexec 

TSingular_SOURCES = emacs.cc fegetopt.c fegetopt.h feOptTS.inc feOpt.cc
# utils.cc utils.h


#### libparse 
libparse_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG -DSTANDALONE_PARSER
libparse_CFLAGS = -O3 -fomit-frame-pointer ${PIPE}
libparse_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
  
libparse_SOURCES = libparse.cc fegetopt.c fegetopt.h utils.cc  utils.h
# nodist_libparse_SOURCES = libSingular.la
 
# # libSingular.la -lnumeric 
libparse_LDADD = -lomalloc
libparse_LDFLAGS = -static ${AMLDFLAGS}
# TODO for libparse:
# multiple definition of `category_out': libparse.cc v.s. utils.cc
# undefined reference to `iiInitSingularProcinfo(procinfo*, char const*, char const*, int, long, int)'

#########################################################
# the Singular library (*.lib files)

include ${srcdir}/singular-libs

singularlibrarydir = ${datadir}/singular
singularlibrary = $(SLIB0:%=LIB/%) $(SLIB1:%=LIB/%) $(PLIBS:%=LIB/%)
nobase_dist_singularlibrary_DATA = LIB/all.lib LIB/tst.lib LIB/help.cnf ${singularlibrary}
EXTRA_DIST = make_alllib.sh LIB/all.lib.tmpl singular-libs LIB/help.cnf

# ${nobase_dist_singularlibrary_DATA}

LIB/all.lib: ${srcdir}/make_alllib.sh ${srcdir}/LIB/all.lib.tmpl ${singularlibrary}
	$(MKDIR_P) LIB
	${srcdir}/make_alllib.sh ${srcdir}/LIB/all.lib.tmpl ${SLIB0} ${PLIBS}

# [ -d ${builddir}/LIB ] || ( $(MKDIR_P) LIB ; cp ${srcdir}/LIB/*.lib ${builddir}/LIB/ )

########################### TEST #########################

TESTS_ENVIRONMENT = SINGULARPATH='${abs_top_builddir}/Singular/LIB:${abs_top_srcdir}/Singular/LIB:${abs_top_builddir}/libpolys/polys/.libs:${abs_top_builddir}/factory/gftables'
TESTS_ENVIRONMENT += SINGULAR_ROOT_DIR='${abs_top_builddir}' 

if WANT_DEBUG
TESTS=test-s-g test-s-r test-d-g test-d-r
else
TESTS=test-s-r test-d-r
endif
check_PROGRAMS=$(TESTS)

# Static versions

test_s_r_CFLAGS = -O3 -fomit-frame-pointer ${PIPE}
test_s_g_CFLAGS = ${PIPE}

test_s_r_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
test_s_g_CXXFLAGS = -g -Wextra -Wall -Wno-long-long -pedantic ${PIPE} $(CXXTEMPLFLAGS)

test_s_r_SOURCES = test.cc
test_s_g_SOURCES = test.cc

test_s_r_LDADD = libSingular.la -lnumeric -lkernel -lpolys -lcoeffs -lreporter -lmisc $(FACTORY_LIBS) -lomalloc -lfindexec $(FLINT_LIBS) $(NTL_LIBS) $(GMP_LIBS) ${USEPPROCSDYNAMICLDFLAGS} ${USEPPROCSDYNAMICLD}
test_s_g_LDADD = libSingular_g.la -lnumeric_g -lkernel_g -lpolys_g -lcoeffs_g -lreporter_g -lmisc_g $(FACTORY_LIBS) -lomalloc_g -lfindexec_g $(FLINT_LIBS) $(NTL_LIBS) $(GMP_LIBS) ${USEPPROCSDYNAMICLDFLAGS}  ${USEPPROCSDYNAMICLD}

test_s_r_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG
test_s_g_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H 

test_s_r_LDFLAGS = -static ${AMLDFLAGS}
test_s_g_LDFLAGS = -static ${AMLDFLAGS}


# Dynamic versions

test_d_r_CFLAGS = -O3 -fomit-frame-pointer ${PIPE}
test_d_g_CFLAGS = ${PIPE}

test_d_r_CXXFLAGS = -O3 -fomit-frame-pointer -Wextra -Wall -Wno-long-long ${PIPE} $(CXXTEMPLFLAGS)
test_d_g_CXXFLAGS = -g -Wextra -Wall -Wno-long-long -pedantic ${PIPE} $(CXXTEMPLFLAGS)

test_d_r_SOURCES = test.cc
test_d_g_SOURCES = test.cc

test_d_r_LDADD = libSingular.la -lnumeric -lkernel -lpolys -lcoeffs -lreporter -lmisc $(FACTORY_LIBS) -lomalloc -lfindexec $(FLINT_LIBS) $(NTL_LIBS) $(GMP_LIBS) ${USEPPROCSDYNAMICLDFLAGS} ${USEPPROCSDYNAMICLD}
test_d_g_LDADD = libSingular_g.la -lnumeric_g -lkernel_g -lpolys_g -lcoeffs_g -lreporter_g -lmisc_g $(FACTORY_LIBS) -lomalloc_g -lfindexec_g $(FLINT_LIBS) $(NTL_LIBS) $(GMP_LIBS) ${USEPPROCSDYNAMICLDFLAGS}  ${USEPPROCSDYNAMICLD}

test_d_r_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H -DNDEBUG -DOM_NDEBUG
test_d_g_CPPFLAGS = ${AM_CPPFLAGS} -DHAVE_CONFIG_H 

test_d_r_LDFLAGS = ${AMLDFLAGS}
test_d_g_LDFLAGS = ${AMLDFLAGS}

#########################################################

# These files are built first
BUILT_SOURCES = feOpt.inc feOptTS.inc feOptES.inc iparith.inc LIB/all.lib plural_cmd.inc \
                gftables MOD

CLEANFILES = $(BUILT_SOURCES) $(EXTRA_PROGRAMS)

feOpt.inc: feOptGen
	${abs_builddir}/feOptGen

feOptES.inc: feOptES
	${abs_builddir}/feOptES

feOptTS.inc: feOptTS
	${abs_builddir}/feOptTS

plural_cmd.inc iparith.inc: gentable1
	${abs_builddir}/gentable1

# # fake rule to fix parallel make http://www.gnu.org/s/hello/manual/automake/Multiple-Outputs.html
# plural_cmd.inc: iparith.inc


gftables: ${abs_top_srcdir}/factory/gftables
	ln -snf ${abs_top_srcdir}/factory/gftables ${abs_builddir}/gftables

MOD: ${abs_top_builddir}/libpolys/polys/.libs
	ln -snf ${abs_top_builddir}/libpolys/polys/.libs/ ${abs_builddir}/MOD
