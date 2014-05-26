#ifndef LIMERES_GLOBAL_H
#define LIMERES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIMERES_LIBRARY)
#  define LIMERESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIMERESSHARED_EXPORT Q_DECL_IMPORT
#endif

#ifdef Q_WS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif


#endif // LIMERES_GLOBAL_H
