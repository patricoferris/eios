Effects on iOS
--------------

A little experiment to have multicore OCaml with effects on iOS (currently just the simulator). You could probably do this very quickly with the excellent [reason-mobile](https://github.com/EduardoRFS/reason-mobile), but I'm more familiar with opam+dune world from [my adventures with RISC-V](https://github.com/patricoferris/riscv-o-spec).

This uses the dune-workspace + cross-compiler trick (similar to what [Mirage 4](https://next.mirage.io) does, but a little more manual). This trick requires building a cross-compiling OCaml compiler and then using findlib toolchains to switch out what compiler is used for a dune workspace. The submoduled multicore compiler has the needed Makefile changes to make it cross-compiling plus scripts to build and install it. Something like the following should work:

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
make build
```

In order to not have to build a large [opam-repository overlay](https://github.com/patricoferris/opam-cross-shakti), we can use [`opam monorepo`](https://github.com/ocamllabs/opam-monorepo) to get all of the transitive dependencies (that can be built with dune) and build the application as a ... "monorepo".