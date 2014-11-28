//   This file is part of the serpents-rpc library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2014  The serpents-rpc team (See AUTHORS file)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.

#pragma once

// Add platform specific definitions.
#include "guslib/guslib_platform.h"

#ifdef SSLSERVER_EXP
#define SSLSERVER_EXPORT_SYMBOL __declspec (dllexport)
#define SSLSERVER_EXPIMP_TEMPLATE
#else
#ifdef SSLSERVER_STANDALONE
#define SSLSERVER_EXPORT_SYMBOL 
#define SSLSERVER_EXPIMP_TEMPLATE 
#else
#define SSLSERVER_EXPORT_SYMBOL __declspec (dllimport)
#define SSLSERVER_EXPIMP_TEMPLATE extern
#endif
#endif // SSLSERVER_EXP

#ifdef SSLSERVER_EXP
#define SSLEXP_STATIC_VAR extern "C" __declspec(dllexport)
#else
#define SSLEXP_STATIC_VAR extern "C" __declspec(dllimport)
#endif

