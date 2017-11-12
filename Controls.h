#ifndef CONTROLS_H
#define CONTROLS_H

#define DLL_FILE_NAME	"Wouter.Controls.dll"

#ifdef CONTROLS_EXPORTS
#define CONTROLS_DLL __declspec(dllexport)
#else
#define CONTROLS_DLL
#endif

#endif