#ifndef CFGGLOBALS_H
#define CFGGLOBALS_H


#include <string>

namespace CfgGlobals {
    static const bool           DEBUG           = true;
    static const bool           VERBOSE         = true;

    static const unsigned short int     OVERRIDE_KEYS        = 2; //0 = existing keys are replaces, 1 = existing keys are not added, 2 = existing keys are added (two keys of the same name may exist)
    static const std::string            COMMENT_STRING       = "//";
    static const std::string            CATEGORY_TAG_OPEN    = "[";
    static const std::string            CATEGORY_TAG_CLOSE   = "]";
    static const std::string            ASSIGNMENT_OPERATOR  = "=";
    static const std::string            NULL_STRING          = "";
    static const std::string            GLOBAL_CATEGORY      = "__CATGBL__";
    static const std::string            BOOL_ID              = "true";
}
#endif // CFGGLOBALS_H
