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

#ifndef _AUTOPIPER_FRONTEND_TYPE_LOWER_H_
#define _AUTOPIPER_FRONTEND_TYPE_LOWER_H_

#include "frontend/ast.h"
#include "frontend/visitor.h"

#include <map>
#include <set>
#include <string>

namespace autopiper {
namespace frontend {

// This pass converts all aggregate-type field accesses to bitslices (for
// reads) and bitslice/concatenation read-modify-writes (for updates). After it
// runs, all dataflow is desuguared to flat signal values only.
class TypeLowerPass : public ASTVisitorContext {
    public:
        TypeLowerPass(ErrorCollector* coll)
            : ASTVisitorContext(coll), ast_(nullptr) {}

    protected:
        // Pre-hook on assignments detects <FIELD_REF> = <...> and desugars to
        // a read/modify/write. We want this to be a *pre* hook so that we
        // rewrite the LHS before the expor hook sees it.
        virtual Result ModifyASTStmtAssignPre(ASTRef<ASTStmtAssign>& node);

        // expr hook rewrites FIELD_REF ops to bitslices.
        virtual Result ModifyASTExprPost(ASTRef<ASTExpr>& node);

        virtual Result ModifyASTPre(ASTRef<AST>& node) {
            ast_ = node.get();
            return VISIT_CONTINUE;
        }

    private:
        AST* ast_;
};

}  // namesapce frontend
}  // namespace autopiper

#endif  // _AUTOPIPER_FRONTEND_TYPE_LOWER_H_
