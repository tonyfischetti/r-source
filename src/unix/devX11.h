/* Declarations (for devX11.c) which are not only there,
 * ------------ but also, e.g., in  system.c  [event loop]
 */

#ifdef __SYSTEM__
#define extern
#endif

#include "R_ext/eventloop.h"

extern int  (*X11DeviceDriver)(DevDesc*, char*, double, double, double, double,
			       int, int);
extern SEXP (*ptr_dataentry)(SEXP call, SEXP op, SEXP args, SEXP rho);

extern int (*GnomeDeviceDriver)(DevDesc*, char*, double, double, double);

extern int (*GTKDeviceDriver)(DevDesc*, char*, double, double, double);

extern void (*ptr_R_Suicide)(char *);
extern void (*ptr_R_ShowMessage)();
extern int  (*ptr_R_ReadConsole)(char *, unsigned char *, int, int);
extern void (*ptr_R_WriteConsole)(char *, int);
extern void (*ptr_R_ResetConsole)();
extern void (*ptr_R_FlushConsole)();
extern void (*ptr_R_ClearerrConsole)();

InputHandler *(*ptr_R_addInputHandler)(InputHandler *, int, 
				      InputHandlerProc, int);

int (*ptr_R_removeInputHandler)(InputHandler **, InputHandler *);

InputHandler *(*ptr_R_getInputHandler)(InputHandler *, int);


extern void (*ptr_R_Busy)(int);
extern void (*ptr_R_CleanUp)(int, int, int);
extern int  (*ptr_R_ShowFiles)(int, char **, char **, char *, int, char *);
extern int  (*ptr_R_ChooseFile)(int, char *, int);

#ifdef __SYSTEM__
#undef extern
#endif
int stub_X11DeviceDriver(DevDesc*, char*, double, double, double, double, 
			 int, int);
int stub_GnomeDeviceDriver(DevDesc*, char*, double, double, double);

int stub_GTKDeviceDriver(DevDesc*, char*, double, double, double);

SEXP stub_dataentry(SEXP call, SEXP op, SEXP args, SEXP rho);

