(lang dune 2.9)

(name eios)

(source
 (github patricoferris/eios))

(license ISC)

(authors "Patrick Ferris")

(maintainers "pf341@patricoferris.com")

(generate_opam_files true)

(package
 (name eios)
 (synopsis "iOS app with eio")
 (description "Building an iOS application with effects")
 (depends 
   eio_gcd))