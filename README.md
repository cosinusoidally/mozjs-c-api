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
built on top of Spidermonkey 52 ESR. I'm still in the design process so the
API/ABI will likely evolve. Once I have figured out a good design I will freeze
the API/ABI.

When I say MVP I really mean it. We only have 3 functions (all return a status
code with 0 for success):

* `int mjs_init(void)` initialise the VM. Must only be called once during your
  program (I may eventually loosen this requirement to once per thread). This
  function creates and initialises a single copy of the VM in memory. The VM is
  tighly bound to the thread on which is was created, you must only call in to
  the VM from that thread for the whole duration of your program.
* `int mjs_evaluate(const char * script)` run a script in the VM. The variable
  script is the actual source code of the script (not a file name). Must only
  be called from the same thread as `mjs_init` was called.
* `int mjs_shutdown(void)`  shutdown the VM (must only be called from the same
  thread as `mjs_init` was called from)

To use the API include `mozjs-c.h` and dynamically link to libmozjs-c.so (see
`example.c` and `mk-example` for an example).

## Building

See BUILDING.txt for full instructions
