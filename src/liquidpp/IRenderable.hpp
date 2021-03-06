#pragma once

#include <string>
#include <vector>

#include <boost/variant/recursive_variant.hpp>

namespace liquidpp
{
   class Context;

   struct IRenderable
   {
      virtual ~IRenderable()
      {}
       
      virtual void render(Context& context, std::string& out) const = 0;
   };
}
