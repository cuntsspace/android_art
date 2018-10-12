/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Art Offset file dependencies
#define DEFINE_INCLUDE_DEPENDENCIES
#include "offsets_all.def"

// We use "asm volatile" to generate text that will stand out in the
// compiler generated intermediate assembly file (eg. ">>FOO 42 0<<").
// We emit all values as 64-bit integers (which we will printed as text).
// We also store a flag which specifies whether the constant is negative.
// Note that "asm volatile" must be inside a method to please the compiler.
#define DEFINE_EXPR(NAME, TYPE, EXPR) \
void AsmDefineHelperFor_##NAME() { \
  asm volatile("\n.ascii \">>" #NAME " %0 %1<<\"" \
  :: "i" (static_cast<int64_t>(EXPR)), "i" (EXPR < 0 ? 1 : 0)); \
}
#include "offsets_all.def"