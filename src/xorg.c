#include "xorg.h"

#include "assert.h"

bool xorgContext_init(struct X11Context* context, Display* display, int screen) {
    assert(context != NULL);
    assert(display != NULL);

    context->display = display;
    context->screen = screen;

    context->configs = glXGetFBConfigs(display, screen, &context->numConfigs);
    if(context->configs == NULL) {
        printf_errf("Failed retrieving the fboconfigs");
        return false;
    }

    return true;
}

GLXFBConfig* xorgContext_selectConfig(struct X11Context* context, VisualID visualid) {
    assert(visualid != 0);

	GLXFBConfig* selected = NULL;

    int value;
    for(int i = 0; i < context->numConfigs; i++) {
        GLXFBConfig fbconfig = context->configs[i];
        XVisualInfo* visinfo = glXGetVisualFromFBConfig(context->display, fbconfig);
        if (!visinfo || visinfo->visualid != visualid)
            continue;

        // We don't want to use anything multisampled
        glXGetFBConfigAttrib(context->display, fbconfig, GLX_SAMPLES, &value);
        if (value >= 2)
            continue;

        // We need to support pixmaps
        glXGetFBConfigAttrib(context->display, fbconfig, GLX_DRAWABLE_TYPE, &value);
        if (!(value & GLX_PIXMAP_BIT))
            continue;

        // We need to be able to bind pixmaps to textures
        glXGetFBConfigAttrib(context->display, fbconfig,
                GLX_BIND_TO_TEXTURE_TARGETS_EXT,
                &value);
        if (!(value & GLX_TEXTURE_2D_BIT_EXT))
            continue;

        // We want RGBA textures
        glXGetFBConfigAttrib(context->display, fbconfig,
                GLX_BIND_TO_TEXTURE_RGBA_EXT, &value);
        if (value == false)
            continue;

        selected = &context->configs[i];
        break;
    }
    // If we ran out of fbconfigs before we found something we like.
    if(selected == NULL)
        return NULL;

    return selected;
}

void xorgContext_delete(struct X11Context* context) {
    assert(context->display != NULL);
}
