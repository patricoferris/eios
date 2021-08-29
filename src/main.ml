open Eio.Std

external run : unit -> unit = "eios_run"

module Label = struct 
  type t
  external make : unit -> t = "eios_label"
  external set_text : t -> string -> unit = "eios_label_set_text"
end

module View = struct
  type t
  external make : unit -> t = "eios_view"
  (* Needs better types as a label is a view *)
  external add_subview : t -> Label.t -> unit = "eios_view_add_subview"
end

module Window = struct
  type t
  external make : unit -> t = "eios_window"
  external set_root_view_controller : t -> View.t -> unit = "eios_window_set_root_view_controller"
  external make_key_and_visible : t -> unit = "eios_window_make_key_and_visible"
end

module Application = struct 
  type t
  external set_window : t -> Window.t -> unit = "eios_application_set_window"
end

let did_finish_launching (fn : Application.t -> unit) = 
  Callback.register "AppDelegate.applicationDidFinishLaunching" fn

let () =
  let f app =
    let window = Window.make () in
    let view = View.make () in
    let label = Label.make () in
    let buffer = Buffer.create 20 in
    Eio_gcd.run @@ fun env ->
    Eio.Flow.copy_string "Effects and OCaml!\n" (Eio.Flow.buffer_sink buffer);
    Label.set_text label (Buffer.contents buffer);
    View.add_subview view label;
    Window.set_root_view_controller window view;
    Window.make_key_and_visible window;
    Application.set_window app window
  in
  did_finish_launching f;
  run ()