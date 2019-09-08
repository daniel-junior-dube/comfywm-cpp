#include <wlr/util/log.h>
#include "glapi.h"

PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT;
PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC eglCreatePlatformWindowSurfaceEXT;
PFNEGLCREATEIMAGEKHRPROC eglCreateImageKHR;
PFNEGLDESTROYIMAGEKHRPROC eglDestroyImageKHR;
PFNEGLQUERYWAYLANDBUFFERWL eglQueryWaylandBufferWL;
PFNEGLBINDWAYLANDDISPLAYWL eglBindWaylandDisplayWL;
PFNEGLUNBINDWAYLANDDISPLAYWL eglUnbindWaylandDisplayWL;
PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glEGLImageTargetTexture2DOES;
PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC eglSwapBuffersWithDamageEXT;
PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC eglSwapBuffersWithDamageKHR;
PFNEGLQUERYDMABUFFORMATSEXTPROC eglQueryDmaBufFormatsEXT;
PFNEGLQUERYDMABUFMODIFIERSEXTPROC eglQueryDmaBufModifiersEXT;
PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC eglExportDMABUFImageQueryMESA;
PFNEGLEXPORTDMABUFIMAGEMESAPROC eglExportDMABUFImageMESA;
PFNEGLDEBUGMESSAGECONTROLKHRPROC eglDebugMessageControlKHR;
PFNGLDEBUGMESSAGECALLBACKKHRPROC glDebugMessageCallbackKHR;
PFNGLDEBUGMESSAGECONTROLKHRPROC glDebugMessageControlKHR;
PFNGLPOPDEBUGGROUPKHRPROC glPopDebugGroupKHR;
PFNGLPUSHDEBUGGROUPKHRPROC glPushDebugGroupKHR;

bool load_glapi(void) {
    static bool done = false;
    if (done) {
        return true;
    }

eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
if (!eglGetPlatformDisplayEXT) {
	wlr_log(WLR_ERROR, "Unable to load eglGetPlatformDisplayEXT");
	return false;
}
eglCreatePlatformWindowSurfaceEXT = (PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC)eglGetProcAddress("eglCreatePlatformWindowSurfaceEXT");
if (!eglCreatePlatformWindowSurfaceEXT) {
	wlr_log(WLR_ERROR, "Unable to load eglCreatePlatformWindowSurfaceEXT");
	return false;
}
eglCreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
eglDestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC)eglGetProcAddress("eglDestroyImageKHR");
eglQueryWaylandBufferWL = (PFNEGLQUERYWAYLANDBUFFERWL)eglGetProcAddress("eglQueryWaylandBufferWL");
eglBindWaylandDisplayWL = (PFNEGLBINDWAYLANDDISPLAYWL)eglGetProcAddress("eglBindWaylandDisplayWL");
eglUnbindWaylandDisplayWL = (PFNEGLUNBINDWAYLANDDISPLAYWL)eglGetProcAddress("eglUnbindWaylandDisplayWL");
glEGLImageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");
eglSwapBuffersWithDamageEXT = (PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)eglGetProcAddress("eglSwapBuffersWithDamageEXT");
eglSwapBuffersWithDamageKHR = (PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC)eglGetProcAddress("eglSwapBuffersWithDamageKHR");
eglQueryDmaBufFormatsEXT = (PFNEGLQUERYDMABUFFORMATSEXTPROC)eglGetProcAddress("eglQueryDmaBufFormatsEXT");
eglQueryDmaBufModifiersEXT = (PFNEGLQUERYDMABUFMODIFIERSEXTPROC)eglGetProcAddress("eglQueryDmaBufModifiersEXT");
eglExportDMABUFImageQueryMESA = (PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC)eglGetProcAddress("eglExportDMABUFImageQueryMESA");
eglExportDMABUFImageMESA = (PFNEGLEXPORTDMABUFIMAGEMESAPROC)eglGetProcAddress("eglExportDMABUFImageMESA");
eglDebugMessageControlKHR = (PFNEGLDEBUGMESSAGECONTROLKHRPROC)eglGetProcAddress("eglDebugMessageControlKHR");
glDebugMessageCallbackKHR = (PFNGLDEBUGMESSAGECALLBACKKHRPROC)eglGetProcAddress("glDebugMessageCallbackKHR");
glDebugMessageControlKHR = (PFNGLDEBUGMESSAGECONTROLKHRPROC)eglGetProcAddress("glDebugMessageControlKHR");
glPopDebugGroupKHR = (PFNGLPOPDEBUGGROUPKHRPROC)eglGetProcAddress("glPopDebugGroupKHR");
glPushDebugGroupKHR = (PFNGLPUSHDEBUGGROUPKHRPROC)eglGetProcAddress("glPushDebugGroupKHR");

    done = true;
    return true;
}
