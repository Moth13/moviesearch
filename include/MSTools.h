#ifndef MSTOOLS_H
#define MSTOOLS_H

#include <QtCore>

// This file constains some tools functions/macro

#define SAFE_DELETE( p ) { delete p; p = NULL; }
#define SAFE_LIST_DELETE( lp ) { while( !lp.isEmpty() ){ SAFE_DELETE( lp.takeLast(); ) } }

#endif // MSTOOLS_H
