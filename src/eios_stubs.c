// Stubs based on
//   brisk: https://github.com/briskml/brisk
//   voronoi: https://github.com/l4u/OCaml-iOS-voronoi

#import <UIKit/UIKit.h>
#import "eios_stubs.h"
#import <caml/alloc.h>
#import <caml/bigarray.h>
#import <caml/callback.h>
#import <caml/custom.h>
#import <caml/fail.h>
#import <caml/memory.h>
#import <caml/mlvalues.h>
#import <caml/signals.h>
#import <caml/threads.h>

void eios_run () {
  int argc = 1;
  char *argv[] = { "eios" };
  caml_release_runtime_system();
  @autoreleasepool {
    int retVal = UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
  }
}

// Borrowed from Brisk

void brisk_caml_memoize(const char *name, value **staticPointer) {
  if (*staticPointer == NULL) {
    *staticPointer = caml_named_value(name);
  }
}

void brisk_caml_call_n(value f, int argCount, value *args) {
  caml_c_thread_register();
  caml_acquire_runtime_system();
  caml_callbackN(f, argCount, args);
  caml_release_runtime_system();
}

void brisk_caml_call(value f) {
  value args[] = {Val_unit};
  brisk_caml_call_n(f, 1, args);
}

// Thrown together haphazardly just to get it to compile!

UILabel *eios_label() {
  CGRect mainScreenBounds = [[UIScreen mainScreen] bounds];
  UILabel *label = [[UILabel alloc] initWithFrame:mainScreenBounds];
  [label retain];
  return label;
}

CAMLprim value eios_label_set_text(UILabel *label, value v_string) {
  CAMLparam1(v_string);

  NSString *str = [NSString stringWithUTF8String:String_val(v_string)];

  [label setText:str];
  CAMLreturn(Val_unit);
}

UIViewController *eios_view() {
  CGRect mainScreenBounds = [[UIScreen mainScreen] bounds];
  UIViewController *viewController = [[UIViewController alloc] init];
  viewController.view.backgroundColor = [UIColor whiteColor];
  viewController.view.frame = mainScreenBounds;
  [viewController retain];
  return viewController;
}

CAMLprim value eios_view_add_subview(UIViewController *view, UIView *subview) {
  CAMLparam0();
  [view.view addSubview: subview];
  CAMLreturn(Val_unit);
}

UIWindow *eios_window() {
  UIWindow *window = [[UIWindow alloc] init];
  [window retain];
  return window;
}

CAMLprim value eios_window_make_key_and_visible(UIWindow *window) {
  CAMLparam0();
  [window makeKeyAndVisible];
  CAMLreturn(Val_unit);
}

CAMLprim value eios_window_set_root_view_controller(UIWindow *window, UIViewController *vc) {
  CAMLparam0();
  window.rootViewController = vc;
  CAMLreturn(Val_unit);
}

#define App_val(v) (*((AppDelegate **)Data_custom_val(v)))
static struct custom_operations app_ops = {
    "eios.app",
    custom_finalize_default,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default,
    custom_compare_ext_default,
    custom_fixed_length_default,
};

value eios_application_set_window(value v_app, UIWindow *window) {
  CAMLparam1(v_app);
  AppDelegate *app = App_val(v_app);
  [app setWindow:window];
  CAMLreturn(Val_unit);
}

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)__unused not{
  static value *callbackFn = NULL;
  brisk_caml_memoize("AppDelegate.applicationDidFinishLaunching",
                     &callbackFn);
  if (callbackFn != NULL) {
    caml_c_thread_register();
    caml_acquire_runtime_system();
    CAMLparam0();
    CAMLlocal1(v_app);
    v_app = caml_alloc_custom(&app_ops, sizeof(AppDelegate *), 0, 1);
    caml_register_global_root(&v_app); // Might not be necessary...
    App_val(v_app) = self;
    value args[1] = { v_app };
    caml_callbackN(*callbackFn, 1, args);
    caml_release_runtime_system();
  }
}

@end