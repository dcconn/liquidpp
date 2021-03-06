#pragma once

#include "Filter.hpp"

namespace liquidpp
{
namespace filters
{

struct Lstrip
{
   Value operator()(Value&& val) const
   {
      if (!val.isStringViewRepresentable())
         return std::move(val);

      auto sv = *val;
      auto pos = sv.find_first_not_of(" \t\r\n");
      if (pos != std::string::npos)
         return sv.substr(pos).to_string();

      return Value::reference(string_view{});
   }
};

}
}