#include "jsapi.h"
#include "js/Initialization.h"

static JSClassOps global_ops = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    JS_GlobalObjectTraceHook
};

/* The class of the global object. */
static JSClass global_class = {
    "global",
    JSCLASS_GLOBAL_FLAGS,
    &global_ops
};

#define EXPORT_MOZJS_C extern "C" __attribute__ ((visibility ("default")))

JSContext *cx;
JS::PersistentRootedObject global;
int lineno = 1;

EXPORT_MOZJS_C int mjs_init(){
    JS_Init();
    cx = JS_NewContext(8L * 1024 * 1024);
    if (!cx)
        return 1;
    if (!JS::InitSelfHostedCode(cx))
        return 1;
    JSAutoRequest ar(cx); // In practice, you would want to exit this any
    JS::CompartmentOptions options;
    global.init(cx, JS_NewGlobalObject(cx, &global_class, nullptr, JS::FireOnNewGlobalHook, options));
    if (!global)
        return 1;
    JSAutoCompartment ac(cx, global);
    JS_InitStandardClasses(cx, global);
    return 0;
}

EXPORT_MOZJS_C int mjs_evaluate(const char * script)
{
    JSAutoRequest ar(cx); 
    JS::RootedValue rval(cx);
    JSAutoCompartment ac(cx, global);

    const char *filename = "noname";
    JS::CompileOptions opts(cx);
    opts.setFileAndLine(filename, lineno);
    bool ok = JS::Evaluate(cx, opts, script, strlen(script), &rval);
    if (!ok)
      return 1;
    JSString *str = rval.toString();
    printf("%s\n", JS_EncodeString(cx, str));
    lineno++;
    return 0;
}

EXPORT_MOZJS_C int mjs_shutdown(){
    JS_DestroyContext(cx);
    JS_ShutDown();
    return 0;
}
