#pragma once

#include "Filter.hpp"

namespace liquidpp
{
namespace filters
{

struct Rstrip : public Filter
{
   virtual Value operator()(Context& c, Value&& val) const override final
   {
      if (!val.isStringViewRepresentable())
         return std::move(val);

      auto sv = *val;
      auto pos = sv.find_last_not_of(" \t\r\n");
      if (pos != std::string::npos)
         return Value::reference(sv.substr(0, pos+1));

      return Value::reference(string_view{});
   }
};

}
}