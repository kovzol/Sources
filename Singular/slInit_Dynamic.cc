/****************************************
*  Computer Algebra System SINGULAR     *
****************************************/
/***************************************************************
 *  File:    slInit_Dynamic.cc
 *  Purpose: link initialization for dynamic linking
 *  Author:  obachman (Olaf Bachmann)
 *  Created: 12/00
 *******************************************************************/

#include "config.h"
#include <kernel/mod2.h>
#include <Singular/silink.h>
#include <Singular/slInit.h>
#include <polys/mod_raw.h>

#ifdef HAVE_DL

#ifdef HAVE_DBM
#include "dbm_sl.h"

static void* dbm_so_handle = NULL;
static void* slInitDBMHandle()
{
  if (dbm_so_handle == NULL)
    dbm_so_handle = dynl_open_binary_warn("dbmsr");

  return dbm_so_handle;
}

si_link_extension slInitDBMExtension(si_link_extension s)
{
  void* handle = slInitDBMHandle();

  if (handle == NULL) return NULL;

  s->Open=(slOpenProc)dynl_sym_warn(handle, "dbOpen");
  s->Close=(slCloseProc)dynl_sym_warn(handle, "dbClose");
  s->Kill=(slKillProc)dynl_sym_warn(handle, "dbClose");
  s->Read=(slReadProc)dynl_sym_warn(handle, "dbRead1");
  s->Read2=(slRead2Proc)dynl_sym_warn(handle, "dbRead2");
  s->Write=(slWriteProc)dynl_sym_warn(handle, "dbWrite");

  if (s->Open == NULL || s->Close == NULL || s->Kill == NULL ||
      s->Read == NULL || s->Read2 == NULL)
    return NULL;

  s->Status=slStatusAscii;
  s->type="DBM";
  return s;
}

#endif
#endif

