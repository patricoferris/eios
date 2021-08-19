effect Print : string -> unit

let print s = perform (Print s)

let main () =
  print "World";
  print "Hello"

let () =
  match main () with
   | () -> ()
   | effect (Print s) k -> continue k (); print_endline s