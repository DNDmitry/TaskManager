#ifndef TASKPROCESSOR_GLOBAL_H
#define TASKPROCESSOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TASKPROCESSOR_LIBRARY)
#  define TASKPROCESSORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TASKPROCESSORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TASKPROCESSOR_GLOBAL_H
