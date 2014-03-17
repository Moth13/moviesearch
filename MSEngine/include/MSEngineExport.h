#ifndef MSENGINEEXPORT_H
#define MSENGINEEXPORT_H

#include <QtCore/qglobal.h>

#ifndef MSEngine_EXPORT
# if defined(MSEngine_MAKEDLL)
   /* We are building this library */
#  define MSEngine_EXPORT Q_DECL_EXPORT
# else
   /* We are using this library */
#  define MSEngine_EXPORT Q_DECL_IMPORT
# endif
#endif

#endif // MSENGINEEXPORT_H
