open Eio.Std

let () =
  Eio_gcd.run @@ fun env ->
  Eio.Flow.copy_string "Hello, world!\n" (Eio.Stdenv.stdout env)