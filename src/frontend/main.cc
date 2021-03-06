/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "frontend/cmdline-driver.h"
#include "common/exception.h"

#include <iostream>

using namespace std;

int main(int argc, const char* const* argv) {
    autopiper::frontend::FrontendCmdlineDriver driver;
    try {
        driver.ParseArgs(argc - 1, argv + 1);
        driver.Execute();
        return 0;
    } catch (autopiper::Exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
