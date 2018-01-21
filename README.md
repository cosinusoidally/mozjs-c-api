# mozjs-c-api
Unofficial minimal C API for the Spidermonkey JavaScript VM

## Purpose

Spidermonkey currently has a large, complicated, poorly documented, continually
evolving, C++ API (known as JSAPI). Whilst this approach to API design and
implementation may work for Mozilla, it doesn't work well for me. I would like
to be able to target a small, stable API. I would like to be able to generate a
Spidermonkey shared library that has a stable API/ABI (ie both a stable source
and binary interface) and is trivially simple to link against. The purpose of
this repo is to design and implement such an API.

## Current status

This repo currently contains an absolutely minimal viable product (MVP) C API
built on top of Spidermonkey 52 ESR.

When I say MVP I really mean it. We only have 3 functions (all return a status
code with 0 for success):

* `int mjs_init(void)` initialise the VM
* `int mjs_evaluate(const char * script)` run a script in the VM
* `int mjs_shutdown(void)`  shutdown the VM

To use the API include `mozjs-c.h` and dynamically link to libmozjs-c.so (see
`example.c` and `mk-example` for an example).

## Building

See BUILDING.txt for full instructions
