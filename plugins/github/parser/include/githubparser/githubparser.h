#ifndef CC_PARSER_GITHUBPARSER_H
#define CC_PARSER_GITHUBPARSER_H

#include <parser/abstractparser.h>
#include <parser/parsercontext.h>

namespace cc
{
namespace parser
{
  
class GithubParser : public AbstractParser
{
public:
  GithubParser(ParserContext& ctx_);
  virtual ~GithubParser();
  virtual bool parse() override;
private:
  bool accept(const std::string& path_);
};
  
} // parser
} // cc

#endif // CC_PLUGINS_PARSER_GITHUBPARSER_H
