Effects on iOS
--------------

*Very WIP & Experimental*

### Overview

A little experiment to have multicore OCaml with effects on iOS (currently just the simulator). In particular the GCD backend for [eio](https://github.com/ocaml-multicore/eio). You could probably do this very quickly with the excellent [reason-mobile](https://github.com/EduardoRFS/reason-mobile), but I'm more familiar with opam+dune world from [my adventures with RISC-V](https://github.com/patricoferris/riscv-o-spec).

This uses the dune-workspace + cross-compiler trick (similar to what [Mirage 4](https://next.mirage.io) does, but a little more manual). This trick requires building a cross-compiling OCaml compiler and then using `ocamlfind` toolchains to switch out what compiler is used for a dune workspace. The submoduled multicore compiler has the required Makefile changes to make it cross-compiling plus scripts to build and install it. Something like the following should work:

```sh
git clone https://github.com/patricoferris/eios
git submodule update --init
opam update
opam switch create 4.12.0+domains+effects --repositories=multicore=git+https://github.com/ocaml-multicore/multicore-opam.git,default
eval $(opam env)
cd ocaml-multicore
# Check the SDK/iOS versions are good in the build script
./build.sh
./install.sh
cd ..
```

In order to not have to build a large [opam-repository overlay](https://github.com/patricoferris/opam-cross-shakti), we can use [`opam monorepo`](https://github.com/ocamllabs/opam-monorepo) to get all of the transitive dependencies (that can be built with dune) and build the application as a ... "monorepo".

[`opam monorepo` unfortunately doesn't keep patches](https://github.com/ocamllabs/opam-monorepo/issues/113) from opam repositories, which are used quite a bit in the multicore opam-repository. The `vendor` directory contains sources for those things and we add filesystem pins to let `opam monorepo lock` know about them.

There's still bits of `Unix` floating about which I'm not sure needs to be removed or not... at any rate, after doing a `opam monorepo pull` you will need to edit `duniverse/eio/lib_ctf/dune` to include `unix` as a library...

You should be able to get things going with:

```sh
# Boots a specific simulator (for me it is iOS 8, change the id for something else)
make boot
open -a Simulator.app
# Installs the very basic app on the device
make install
```

### Future Plans

Right now effects are not being put to great use. Just getting to the point of cross-compiling and running on a simulator and using `eio` the the [gcd](https://github.com/patricoferris/ocaml-dispatch) backend took a bit of effort. But now that's mostly done, so the future ideas are:

 - Can effects be used to write a cleaner RunLoop ?
 - Could you write some kind of stateful component library with effects a bit like React.js ?
 - `Eio_gcd` needs more work to add the network stack (see bindings to [Network.Framework](https://github.com/patricoferris/ocaml-network)), once in place it can be used to do some network calls.