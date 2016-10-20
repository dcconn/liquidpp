#pragma once

#include "Filter.hpp"

namespace liquidpp
{
namespace filters
{

struct Downcase : public Filter
{
   virtual Value operator()(Context& c, Value&& val) const override final
   {
      if (!val.isStringViewRepresentable())
         return std::move(val);

      auto sv = *val;

      std::locale loc;
      std::string res;
      res.reserve(sv.size());

      // TODO: No real UTF-8 handling (boost::locale or ICU required)
      for(auto c : sv)
         res += std::tolower(c, loc);
      return std::move(res);
   }
};

}
}