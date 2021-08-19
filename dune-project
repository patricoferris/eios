(lang dune 2.9)


(generate_opam_files true)

(package
 (name eios)
 (synopsis "iOS app with eio")
 (description "Building an iOS application with effects")
 (depends 
   eio_gcd))