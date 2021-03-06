// Copyright (c) 2019 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_COMMON_GIN_CONVERTERS_NATIVE_WINDOW_CONVERTER_H_
#define SHELL_COMMON_GIN_CONVERTERS_NATIVE_WINDOW_CONVERTER_H_

#include "gin/converter.h"
#include "shell/browser/api/atom_api_top_level_window.h"

namespace gin {

template <>
struct Converter<electron::NativeWindow*> {
  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     electron::NativeWindow** out) {
    // null would be tranfered to NULL.
    if (val->IsNull()) {
      *out = NULL;
      return true;
    }

    electron::api::TopLevelWindow* window;
    // TODO(deermichel): remove mate:: after dropping mate
    if (!mate::Converter<electron::api::TopLevelWindow*>::FromV8(isolate, val,
                                                                 &window))
      return false;
    *out = window->window();
    return true;
  }
};

}  // namespace gin

#endif  // SHELL_COMMON_GIN_CONVERTERS_NATIVE_WINDOW_CONVERTER_H_
