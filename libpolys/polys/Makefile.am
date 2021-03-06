CXXTEMPLFLAGS	=  ## -fno-implicit-templates

DEBUGCXXFLAGS = -g -Wextra -Wall -pedantic -Wno-long-long

NODEBUGCFLAGS   = -O3 -w -fomit-frame-pointer
NODEBUGCXXFLAGS = -O3 -w -fomit-frame-pointer 
NODEBUGDEFS = -DNDEBUG -DOM_NDEBUG 

AM_CFLAGS	= ${PIPE}
AM_CXXFLAGS	= ${PIPE} ${CXXTEMPLFLAGS}

AM_CPPFLAGS	= -I${top_srcdir} -I${top_srcdir}/.. -I${top_builddir} -I${top_builddir}/.. -I${srcdir} -I${top_srcdir}/../factory/include -I${top_builddir}/../factory/include ${GMP_CFLAGS}


if ENABLE_P_PROCS_STATIC
  USE_P_PROCS_STATIC_CC = templates/p_Procs_Static.cc
  USE_P_PROCS_STATIC = -Dp_Procs_Static
else
  USE_P_PROCS_STATIC_CC =
  USE_P_PROCS_STATIC =
endif

if ENABLE_P_PROCS_DYNAMIC
  USE_P_PROCS_DYNAMIC_CC = templates/p_Procs_Dynamic.cc
else
  USE_P_PROCS_DYNAMIC_CC =
endif

if WANT_DEBUG
  LIB_G=libpolys_g.la
  MOD_G=p_Procs_FieldGeneral_g.la p_Procs_FieldIndep_g.la p_Procs_FieldQ_g.la p_Procs_FieldZp_g.la
else
  LIB_G=
  MOD_G=
endif

libpolys_LTLIBRARIES = libpolys.la ${LIB_G}
libpolysdir = $(libdir)/singular

SOURCES = \
	monomials/monomials.cc monomials/p_polys.cc monomials/ring.cc monomials/maps.cc \
	operations/pShallowCopyDelete.cc operations/p_Mult_q.cc \
	nc/sca.cc nc/summator.cc nc/ncSAFormula.cc nc/ncSACache.cc nc/ncSAMult.cc \
	pDebug.cc polys0.cc prCopy.cc prCopyMacros.h \
	kbuckets.cc sbuckets.cc weight.cc weight0.c simpleideals.cc matpol.cc \
	sparsmat.cc \
        ${USE_P_PROCS_STATIC_CC} ${USE_P_PROCS_DYNAMIC_CC} mod_raw.cc \
        ext_fields/algext.cc ext_fields/transext.cc \
	clapsing.cc clapconv.cc \
	nc/old.gring.cc PolyEnumerator.cc

LIBPOLYSHEADERS = monomials/ring.h monomials/monomials.h \
  monomials/p_polys.h monomials/maps.h PolyEnumerator.h  prCopy.h \
	nc/nc.h nc/sca.h nc/summator.h nc/ncSAFormula.h nc/ncSACache.h nc/ncSAMult.h nc/gb_hack.h \
	operations/pShallowCopyDelete.h \
	templates/p_Procs.h templates/p_MemAdd.h templates/p_MemCmp.h \
	kbuckets.h sbuckets.h simpleideals.h weight.h matpol.h \
	sparsmat.h clapsing.h clapconv.h coeffrings.h \
	ext_fields/algext.h ext_fields/transext.h mod_raw.h  

EXTRA_DIST = \
	prCopy.pl prCopyTemplate.cc \
	templates/p_Procs_Lib.cc templates/p_MemCopy.h templates/p_Numbers.h \
	templates/p_Procs_Set.h templates/p_Procs_Static.h templates/p_Procs_Dynamic.h \
	templates/p_Procs_Impl.h templates/p_Delete__T.cc templates/p_Copy__T.cc \
	templates/p_ShallowCopyDelete__T.cc templates/p_Mult_nn__T.cc \
	templates/pp_Mult_nn__T.cc templates/pp_Mult_mm__T.cc templates/p_Mult_mm__T.cc \
	templates/pp_Mult_Coeff_mm_DivSelect__T.cc templates/pp_Mult_nn__T.cc \
	templates/pp_Mult_Coeff_mm_DivSelectMult__T.cc \
	templates/pp_Mult_mm_Noether__T.cc operations/p_Mult_q.h \
	templates/p_kBucketSetLm__T.cc templates/p_Minus_mm_Mult_qq__T.cc \
	templates/p_Merge_q__T.cc templates/p_Add_q__T.cc templates/p_Neg__T.cc

P_PROCS_CPPFLAGS_COMMON = ${AM_CPPFLAGS} -DDYNAMIC_VERSION 

p_Procs_FieldGeneral_la_CPPFLAGS = -Dp_Procs_FieldGeneral ${P_PROCS_CPPFLAGS_COMMON} ${NODEBUGDEFS}
p_Procs_FieldIndep_la_CPPFLAGS = -Dp_Procs_FieldIndep ${P_PROCS_CPPFLAGS_COMMON} ${NODEBUGDEFS}
p_Procs_FieldQ_la_CPPFLAGS = -Dp_Procs_FieldQ ${P_PROCS_CPPFLAGS_COMMON} ${NODEBUGDEFS}
p_Procs_FieldZp_la_CPPFLAGS = -Dp_Procs_FieldZp ${P_PROCS_CPPFLAGS_COMMON} ${NODEBUGDEFS}

p_Procs_FieldGeneral_g_la_CPPFLAGS = -Dp_Procs_FieldGeneral ${P_PROCS_CPPFLAGS_COMMON}
p_Procs_FieldIndep_g_la_CPPFLAGS = -Dp_Procs_FieldIndep ${P_PROCS_CPPFLAGS_COMMON}
p_Procs_FieldQ_g_la_CPPFLAGS = -Dp_Procs_FieldQ ${P_PROCS_CPPFLAGS_COMMON}
p_Procs_FieldZp_g_la_CPPFLAGS = -Dp_Procs_FieldZp ${P_PROCS_CPPFLAGS_COMMON}

p_Procs_FieldGeneral_la_CXXFLAGS = ${NODEBUGCXXFLAGS}
p_Procs_FieldIndep_la_CXXFLAGS = ${NODEBUGCXXFLAGS}
p_Procs_FieldQ_la_CXXFLAGS = ${NODEBUGCXXFLAGS}
p_Procs_FieldZp_la_CXXFLAGS = ${NODEBUGCXXFLAGS}

p_Procs_FieldGeneral_g_la_CXXFLAGS = ${DEBUGCXXFLAGS}
p_Procs_FieldIndep_g_la_CXXFLAGS = ${DEBUGCXXFLAGS}
p_Procs_FieldQ_g_la_CXXFLAGS = ${DEBUGCXXFLAGS}
p_Procs_FieldZp_g_la_CXXFLAGS = ${DEBUGCXXFLAGS}

P_PROCS_MODULE_LDFLAGS = -shared -module
P_PROCS_MODULE_LDFLAGSG = -shared -module

p_Procs_FieldGeneral_la_LDFLAGS = ${P_PROCS_MODULE_LDFLAGS}
p_Procs_FieldIndep_la_LDFLAGS = ${P_PROCS_MODULE_LDFLAGS}
p_Procs_FieldQ_la_LDFLAGS = ${P_PROCS_MODULE_LDFLAGS}
p_Procs_FieldZp_la_LDFLAGS = ${P_PROCS_MODULE_LDFLAGS}

p_Procs_FieldGeneral_g_la_LDFLAGS = ${P_PROCS_MODULE_LDFLAGSG}
p_Procs_FieldIndep_g_la_LDFLAGS = ${P_PROCS_MODULE_LDFLAGSG}
p_Procs_FieldQ_g_la_LDFLAGS = ${P_PROCS_MODULE_LDFLAGSG}
p_Procs_FieldZp_g_la_LDFLAGS = ${P_PROCS_MODULE_LDFLAGSG}


P_PROCS = templates/p_Procs_Lib.cc

p_Procs_FieldGeneral_la_SOURCES = ${P_PROCS}
p_Procs_FieldIndep_la_SOURCES = ${P_PROCS}
p_Procs_FieldQ_la_SOURCES = ${P_PROCS}
p_Procs_FieldZp_la_SOURCES = ${P_PROCS}

p_Procs_FieldGeneral_g_la_SOURCES = ${P_PROCS}
p_Procs_FieldIndep_g_la_SOURCES = ${P_PROCS}
p_Procs_FieldQ_g_la_SOURCES = ${P_PROCS}
p_Procs_FieldZp_g_la_SOURCES = ${P_PROCS}


moduledir = $(bindir)
#moduledir = $(libexecdir)/singular/MOD/

if ENABLE_P_PROCS_DYNAMIC
  module_LTLIBRARIES=p_Procs_FieldGeneral.la p_Procs_FieldIndep.la p_Procs_FieldQ.la p_Procs_FieldZp.la ${MOD_G}
endif

libpolys_includedir=$(includedir)/singular/polys

nobase_libpolys_include_HEADERS = $(LIBPOLYSHEADERS)

libpolys_la_SOURCES = ${SOURCES}
libpolys_g_la_SOURCES = ${SOURCES}

EXTRA_libpolys_la_SOURCES = templates/p_Procs_Static.cc templates/p_Procs_Dynamic.cc

libpolys_g_la_CXXFLAGS = ${DEBUGCXXFLAGS}
libpolys_la_CPPFLAGS = ${NODEBUGDEFS} ${AM_CPPFLAGS}




#################################################
# autogenerated sources

BUILT_SOURCES = prCopy.inc templates/p_Procs.inc

noinst_PROGRAMS = templates/p_Procs_Generate
templates_p_Procs_Generate_SOURCES = templates/p_Procs_Generate.cc
templates_p_Procs_Generate_CFLAGS   = ${NODEBUGCFLAGS}
templates_p_Procs_Generate_CXXFLAGS = ${NODEBUGCXXFLAGS}
templates_p_Procs_Generate_CPPFLAGS = ${NODEBUGDEFS} ${USE_P_PROCS_STATIC} ${AM_CPPFLAGS}

templates_p_Procs_Generate_LDADD    = -lreporter -lmisc -lomalloc -lfindexec
templates_p_Procs_Generate_LDFLAGS  = -L${abs_builddir} -L${abs_top_builddir}/coeffs -L${abs_top_builddir}/reporter -L${top_builddir}/misc -L${abs_top_builddir}/../omalloc -L${abs_top_builddir}/../findexec

templates/p_Procs.inc: templates/p_Procs_Generate
	${builddir}/templates/p_Procs_Generate > ${builddir}/templates/p_Procs.inc

prCopy.inc: prCopy.pl
	perl ${srcdir}/prCopy.pl >  prCopy.inc

CLEANFILES = $(BUILT_SOURCES)

