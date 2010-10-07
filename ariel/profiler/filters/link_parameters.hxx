//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

// include by including add_node.hxx
#if !defined(ARIEL_PROFILER_LINK_PARAMETERS_HXX) \
    && defined(ARIEL_PROFILER_ADD_NODE_HXX)
#define ARIEL_PROFILER_LINK_PARAMETERS_HXX

namespace ariel {
namespace profiler {

template<class ASTNode>
struct link_parameters;

template<>
struct link_parameters<clang::ClassTemplateSpecializationDecl> {
  typedef clang::ClassTemplateSpecializationDecl target;

  typedef void result;

  ARIEL_3ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    ir::context::iterator,
    boost::add_pointer<target>::type
  );

  ARIEL_3ARY_CALL(ariel_ctx, root, x) {
    clang::TemplateArgumentList const& args = x->getTemplateArgs();

    for (unsigned i = 0, end = args.size(); i < end; ++i) {
      clang::TemplateArgument const& arg = args[i];

      switch (arg.getKind()) {
        case clang::TemplateArgument::Type: {
          clang::QualType qual = arg.getAsType();
         
          clang::Type* type = qual.getTypePtr();

          if (!type) break;
 
          ARIEL_IF_NOT_DYN_CAST(clang::RecordType, rec, type) {
            ir::make_link<ir::PARAMETRIC>::call(
              root, add_node<clang::Type>::call(ariel_ctx, type)
            );
            break;
          }

          ARIEL_IF_NOT_DYN_CAST(target, data, rec->getDecl()) {
            ir::make_link<ir::PARAMETRIC>::call(
              root, add_node<clang::RecordType>::call(ariel_ctx, rec)
            );
            break;
          }
          
          ir::make_link<ir::PARAMETRIC>::call(
            root, add_node<target>::call(ariel_ctx, data)
          );
        } break;
        case clang::TemplateArgument::Integral: {
          llvm::APSInt const* data = arg.getAsIntegral();

          if (!data) break;

          ir::make_link<ir::PARAMETRIC>::call(
            root, add_node<llvm::APSInt>::call(ariel_ctx, data)
          );
        } break;
        default: break; 
      }
    }
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_LINK_PARAMETERS_HXX
