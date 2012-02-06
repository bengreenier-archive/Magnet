#ifndef CFGGLOBALS_H
#define CFGGLOBALS_H


#include <string>

namespace CfgGlobals {
    static const bool           DEBUG           = true;
    static const bool           VERBOSE         = false;

    static const std::string    COMMENT_STRING       = "//";
    static const std::string    CATEGORY_TAG_OPEN    = "[";
    static const std::string    CATEGORY_TAG_CLOSE   = "]";
    static const std::string    ASSIGNMENT_OPERATOR  = "=";
    static const std::string    NULL_STRING          = "";
    static const std::string    GLOBAL_CATEGORY      = "__CATGBL__";
}
#endif // CFGGLOBALS_H
