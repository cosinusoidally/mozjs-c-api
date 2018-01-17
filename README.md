# mozjs-c-api
Unofficial minimal C API for the Spidermonkey JavaScript VM

## Purpose

Spidermonkey currently has a large, complicated, poorly documented, continually
evolving, C++ API, known as JSAPI. Whilst this approach to API design and
implementation may work for Mozilla, it doesn't work well for me. I would like
to be able to target a small, stable API. I would like to be able to generate a
Spidermonkey shared library that has a stable ABI and and is trivially simple
to link to. The purpose of this repo is to design and implement such an API.

## Current status

This repo contains an absolutely minimal viable product (MVP) C API built on
top of Spidermonkey 52 ESR.

When I say MVP I mean it. We have 3 functions (all return a status code with 0
for sucess):

`int mjs_init(void)` initialise the VM
`int mjs_evaluate(const char * script)` run a script in the VM
`int mjs_shutdown(void)`  shutdown the VM

To use the API include `mozjs-c.h` and dynamically link to libmozjs-c.so (see
`main.c` and `mk-example`).

## Building

I build the code on a Debian Wheezy i386 root filesystem. First grab dependencies:

```
apt-get build-dep firefox
```

This will install `gcc-mozilla` (we need that specific version of GCC to compile).
You will need to add it to your PATH:

```
export PATH=/usr/lib/gcc-mozilla/bin:$PATH
```

Grab the firefox-52.5.3esr source code and signatures from here:

```
https://archive.mozilla.org/pub/firefox/releases/52.5.3esr/source/firefox-52.5.3esr.source.tar.xz
https://archive.mozilla.org/pub/firefox/releases/52.5.3esr/SHA512SUMS
https://archive.mozilla.org/pub/firefox/releases/52.5.3esr/SHA512SUMS.asc
```

Extract the tarball in to the directory `/opt/ff52esr-src/` ie

```
mkdir /opt/ff52esr-src/
tar xvf $wherever/firefox-52.5.3esr.source.tar.xz
```

So you now should have your source in `/opt/ff52esr-src/firefox-52.5.3esr`

You can put the source wherever you want, but you will need to tweak my build
script if you put it anywhere other than the above location.

Next step is to build Spidermonkey:

```
cd /opt/ff52esr-src/firefox-52.5.3esr/js/src/
./configure --enable-release --enable-nspr-build --enable-stdcxx-compat --enable-ctypes
make -j 2 # or however many cores you want to use
```
I want jsctypes (this will allow me to host a load of low level code in JS
rather than having to write a bunch of C/C++), which is why I have to also
enable the use of nspr.

Once Spidermonkey has built you will need to copy out the nspr libraries into
another directory. Grab libnspr4.so, libplc4.so, and libplds4.so from
/opt/ff52esr-src/firefox-52.5.3esr/js/src/dist/bin and drop in to a convenient
location. Then add them to your `LD_LIBRARY_PATH`

We are now ready to build `libmozjs-c.so`. Go in to `mozjs-c-api` and run:

```
sh ./mk-shared
```

If all is well you should now have a `libmozjs-c.so` binary in the current directory.
Add the current dir to your `LD_LIBRARY_PATH`

Next run:

```
sh ./mk-example
```

You should now have an example program called `example`. And that's it.
