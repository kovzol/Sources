// emacs edit mode for this file is -*- C++ -*-
/****************************************
*  Computer Algebra System SINGULAR     *
****************************************/
/*
* ABSTRACT: interface between Singular and factory
*/


#ifndef INCL_FACTORYSING_H
#define INCL_FACTORYSING_H


#ifdef HAVE_FACTORY

#include <polys/monomials/p_polys.h>
#include <polys/monomials/ring.h>
#include <polys/simpleideals.h>
#include <misc/intvec.h>
#include <polys/matpol.h>
#include <coeffs/bigintmat.h>
//#include <polys/clapconv.h>
//#include <kernel/longtrans.h>

/// destroys f and g
poly singclap_gcd ( poly f, poly g, const ring r );


// commented out!
// poly singclap_alglcm ( poly f, poly g, const ring r );
// void singclap_algdividecontent ( napoly f, napoly g, napoly &ff, napoly &gg );

poly singclap_resultant ( poly f, poly g , poly x, const ring r);

BOOLEAN singclap_extgcd ( poly f, poly g, poly &res, poly &pa, poly &pb , const ring r);

poly singclap_pdivide ( poly f, poly g, const ring r );

void singclap_divide_content ( poly f, const ring r);

ideal singclap_factorize ( poly f, intvec ** v , int with_exps, const ring r);

ideal singclap_sqrfree ( poly f, intvec ** v , int with_exps, const ring r );

#ifdef HAVE_NTL
#if 1
matrix singntl_HNF(matrix A, const ring r);
intvec* singntl_HNF(intvec* A, const ring r);
matrix singntl_LLL(matrix A, const ring r);
intvec* singntl_LLL(intvec* A, const ring r);
#endif
#endif

BOOLEAN singclap_isSqrFree(poly f, const ring r);

#ifdef HAVE_LIBFAC
 matrix singclap_irrCharSeries ( ideal I, const ring r);
 char* singclap_neworder ( ideal I, const ring r);
#endif 

poly singclap_det( const matrix m, const ring r );
int singclap_det_i( intvec * m, const ring r );
number singclap_det_bi( bigintmat * m, const coeffs cf);

number   nChineseRemainder(number *x, number *q,int rl, const coeffs r);


#endif /* HAVE_FACTORY */


#endif /* INCL_FACTORYSING_H */

