#include "For.hpp"

#include <regex>

#include "../Context.hpp"

namespace liquidpp {
For::For(Tag&& tag)
   : Block(std::move(tag)) {
   std::regex rex{" *([^ ]+) +in +([^ ]+) *"};
   std::smatch match;
   if (!std::regex_match(value, match, rex))
      throw std::invalid_argument("Malformed 'for' tag ('" + value + "')!");

   loopVariable = match[1].str();
   rangeVariable = match[2].str();
}

void For::render(Context& context, std::string& res) const {
   auto val = context.get(rangeVariable);
   if (val || val == ValueTag::Object) {
      renderElement(context, res, val, rangeVariable);
      return;
   }

   if (val != ValueTag::Range)
      return;

   size_t idx = 0;
   while (true) {
      std::string idxPath = rangeVariable + '[' + boost::lexical_cast<std::string>(idx++) + ']';
      if (!renderElement(context, res, context.get(idxPath), idxPath))
         break;
   }
}

bool For::renderElement(Context& context, std::string& res, const Value& currentVal, string_view idxPath) const {
   Context loopVarContext{context};

   if (currentVal)
      loopVarContext.set(loopVariable, *currentVal);
   else if (currentVal != ValueTag::OutOfRange)
      loopVarContext.setReference(loopVariable, idxPath);
   else
      return false;

   for (auto&& node : body.nodeList)
      renderNode(loopVarContext, node, res);

   return true;
}

}